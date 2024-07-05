/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:27:28 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/05 12:24:45 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	render_frame(t_program *program)
{
	t_data	image;

	image.img = mlx_new_image(program->mlx_pointer, 640, 480);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	generate_image(&image, program);
	mlx_put_image_to_window(program->mlx_pointer, program->window,
		image.img, 0, 0);
	mlx_destroy_image(program->mlx_pointer, image.img);
	return (EXIT_SUCCESS);
}

void	init_camera(t_viewport *viewport)
{
	t_camera		*cam;
	t_vector		up;
	double			half_view_x;
	double			half_view_y;
	const double	rad_conversion = M_PI / 180.0;

	cam = &viewport->camera;
	cam->fov = 90.0;
	set_vector_components(&cam->position, 0.0, 0.0, 0.0);
	set_vector_components(&cam->direction, 0.0, 0.0, 1.0);
	set_vector_components(&up, 0.0, 1.0, 0.0);
	cam->right_axis = normalise(cross(cam->direction, up));
	cam->up_axis = normalise(cross(cam->right_axis, cam->direction));
	half_view_x = tan(cam->fov * rad_conversion / 2.0);
	half_view_y = half_view_x * ((double)(viewport->window_height - 1))
		/ ((double)(viewport->window_width - 1));
	viewport->pixel_dx = scalar_product(cam->right_axis,
			(2.0 * half_view_x) / ((double)(viewport->window_width - 1)));
	viewport->pixel_dy = scalar_product(cam->up_axis,
			(2.0 * half_view_y) / ((double)(viewport->window_height - 1)));
	viewport->pixel_max = subtract(subtract(cam->direction,
				scalar_product(cam->right_axis, half_view_x)),
			scalar_product(cam->up_axis, half_view_y));
}

static void	init_sphere(t_sphere *sphere)
{
	set_vector_components(&sphere->position, 1.0, 0.0, 4.0);
	sphere->color = set_color(255, 255, 10);
	sphere->diameter = 2.0;
}

void	generate_image(t_data *image, t_program *program)
{
	t_vector		pixel;
	t_incident_ray	ray;
	t_sphere		sphere;
	int				i;
	int				j;
	t_light_ambient	ambient;
	t_light			light;
	t_color			pixel_color;
	t_object		object;

	object.type = SPHERE;
	object.object = &sphere;
	light.color = set_color(255, 255, 255);
	light.brightness = 0.8;
	set_vector_components(&light.position, 2.0, 5.0, 4.0);
	ambient.color = set_color(185, 15, 225);
	ambient.ratio = 0.2;
	init_sphere(&sphere);
	init_camera(program->viewport);
	j = 0;
	while (j < program->viewport->window_height)
	{
		i = 0;
		while (i < program->viewport->window_width)
		{
			pixel = add(add(program->viewport->pixel_max,
						scalar_product(program->viewport->pixel_dx, i)),
					scalar_product(program->viewport->pixel_dy, j));
			ray.ray = normalise(pixel);
			if (get_intersection(&object, &program->viewport->camera, &ray))
			{
				pixel_color = color_multiply(sphere.color,
						get_light(&ray, &ambient, &light));
				set_pixel(image, i, j, pixel_color);
			}
			i += 1;
		}
		j += 1;
	}
}
