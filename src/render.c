/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:27:28 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/05 23:23:36 by jhughes          ###   ########.fr       */
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

	pixel = subtract(add(program->viewport->pixel_start,
				scalar_product(program->viewport->pixel_dx, i)),
			scalar_product(program->viewport->pixel_dy, j));
	ray.ray = normalise(pixel);
	o = 0;
	while (program->objects[o] != NULL)
	{
		if (get_intersection(program->objects[o],
				&program->viewport->camera, &ray))
		{
			pixel_color = color_multiply(
					*get_color(program->objects[o]),
					get_light(&ray, &program->ambient, program->lights));
			set_pixel(image, i, j, pixel_color);
		}
		o += 1;
	}
}

void	generate_image(t_data *image, t_program *program)
{
	int	i;
	int	j;

	get_objects(program);
	load_lights(program);
	init_camera(program);
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
