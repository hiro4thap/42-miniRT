/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:27:28 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/10 16:37:48 by hiono            ###   ########.fr       */
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

/// @brief Retrieves the color from the provided object, after identifying the
/// appropriate cast type.
/// @param object The object to retrieve a color from.
/// @return Pointer to color of object.
t_color	*get_color(t_object *object)
{
	if (object->type == SPHERE)
		return (&((t_sphere *) object->object)->color);
	if (object->type == CYLINDER)
		return (&((t_cylinder *) object->object)->color);
	if (object->type == PLANE)
		return (&((t_cylinder *) object->object)->color);
	return (NULL);
}

void	generate_pixel(t_data *image, int i, int j, t_program *program)
{
	t_vector		pixel;
	t_color			pixel_color;
	t_incident_ray	ray;
	int				o;
	double			distance;
	double			min_distance;

	pixel = subtract(subtract(add(program->viewport->pixel_start,
				scalar_product(program->viewport->pixel_dx, i)),
			scalar_product(program->viewport->pixel_dy, j)),
		program->viewport->camera.position);
	ray.ray = normalise(pixel);
	distance = -1;
	min_distance = -1;
	o = 0;
	while (program->objects[o] != NULL)
	{
		distance = to_intersection(program->objects[o],
				program->viewport->camera.position, ray.ray);
		if (0 < distance && (min_distance == -1 || distance < min_distance))
		{
			min_distance = distance;
			ray.incident_point = scalar_product(ray.ray, distance);
			ray.surface_normal = find_normal(program->objects[o],
				ray.incident_point, ray.ray);
			ray.object_color = *get_color(program->objects[o]);
		}
		o += 1;
	}
	if (0 < min_distance)
	{
		pixel_color = color_multiply(ray.object_color,
			get_light(&ray, &program->ambient, program->lights));
		set_pixel(image, i, j, pixel_color);
	}
}

void	generate_image(t_data *image, t_program *program)
{
	int	i;
	int	j;

	//get_objects(program);
	//load_lights(program);
	//init_camera(program);
	read_file("test.rt", program);
	j = 0;
	while (j < program->viewport->window_height)
	{
		i = 0;
		while (i < program->viewport->window_width)
		{
			generate_pixel(image, i, j, program);
			i += 1;
		}
		j += 1;
	}
}
