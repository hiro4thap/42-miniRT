/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:27:28 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/05 17:36:34 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	render_frame(t_program *program)
{
	t_data	image;

	image.img = mlx_new_image(program->mlx_pointer,
			program->viewport->window_width, program->viewport->window_height);
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
	set_vector_components(&cam->direction, 0.0, 1.0, 0.0);
	set_vector_components(&up, 0.0, 0.0, 1.0);
	cam->direction = normalise(cam->direction);
	cam->right_axis = normalise(cross(cam->direction, up));
	cam->up_axis = normalise(cross(cam->right_axis, cam->direction));
	half_view_x = tan(cam->fov * rad_conversion / 2.0);
	half_view_y = half_view_x * ((double)(viewport->window_height - 1))
		/ ((double)(viewport->window_width - 1));
	printf("%lf\n", half_view_y);
	viewport->pixel_dx = scalar_product(cam->right_axis,
			(2.0 * half_view_x) / ((double)(viewport->window_width - 1)));
	viewport->pixel_dy = scalar_product(cam->up_axis,
			(2.0 * half_view_y) / ((double)(viewport->window_height - 1)));
	viewport->pixel_start = add(subtract(cam->direction,
				scalar_product(cam->right_axis, half_view_x)),
			scalar_product(cam->up_axis, half_view_y));
}

/// @brief Initialises object array.
/// @return Object array pointer.
static t_object	**get_objects(void)
{
	const int	num_of_objects = 2;
	t_object	**objects;

	objects = malloc(sizeof(t_object *) * (num_of_objects + 1));
	if (!objects)
		return (NULL);
	objects[0] = malloc(sizeof(t_object));
	if (!objects[0])
		return (NULL);
	objects[0]->type = SPHERE;
	objects[0]->object = malloc(sizeof(t_sphere));
	if (!objects[0]->object)
		return (NULL);
	((t_sphere *) objects[0]->object)->color = set_color(255, 0, 255);
	((t_sphere *) objects[0]->object)->diameter = 1;
	set_vector_components(&((t_sphere *) objects[0]->object)->position,
		2.0, 3.0, -1.0);
	objects[1] = NULL;
	objects[2] = NULL;
	return (objects);
}

/// @brief Retrieves the color from the provided object, after identifying the
/// appropriate cast type.
/// @param object The object to retrieve a color from.
/// @return Pointer to color of object.
t_color	*get_color(t_object *object)
{
	if (object->type == SPHERE)
		return (&((t_sphere *) object->object)->color);
	return (NULL);
}

void	generate_image(t_data *image, t_program *program)
{
	t_vector		pixel;
	t_incident_ray	ray;
	int				i;
	int				j;
	int				o;
	t_light_ambient	ambient;
	t_light			light;
	t_color			pixel_color;
	t_object		**objects;

	objects = get_objects();
	light.color = set_color(255, 255, 255);
	light.brightness = 0.8;
	set_vector_components(&light.position, -1.0, 2.0, 2.0);
	ambient.color = set_color(185, 15, 225);
	ambient.ratio = 0.2;
	init_camera(program->viewport);
	j = 0;
	while (j < program->viewport->window_height)
	{
		i = 0;
		while (i < program->viewport->window_width)
		{
			pixel = subtract(add(program->viewport->pixel_start,
						scalar_product(program->viewport->pixel_dx, i)),
					scalar_product(program->viewport->pixel_dy, j));
			ray.ray = normalise(pixel);
			o = 0;
			while (objects[o] != NULL)
			{
				if (get_intersection(objects[o],
						&program->viewport->camera, &ray))
				{
					pixel_color = color_multiply(*get_color(objects[o]),
							get_light(&ray, &ambient, &light));
					set_pixel(image, i, j, pixel_color);
				}
				o += 1;
			}
			i += 1;
		}
		j += 1;
	}
}
