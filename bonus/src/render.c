/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:27:28 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 11:07:31 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/// @brief Retrieves the color from the provided object, after identifying the
/// appropriate cast type.
/// @param object The object to retrieve a color from.
/// @return Pointer to color of object.
static t_color	*get_color(t_object *object, t_incident_ray *ray)
{
	if (object->texture_type == TEX_CHECKERBOARD)
		uv_checkerboard(uvmap(ray->incident_point, object), 4);
	else if (object->texture_type == TEX_TEXTURE)
		uv_texture(uvmap(ray->incident_point, object), &(object->texture));
	if (object->type == SPHERE)
		return (&((t_sphere *) object->object)->color);
	if (object->type == PLANE)
		return (&((t_plane *) object->object)->color);
	if (object->type == CYLINDER)
		return (&((t_cylinder *) object->object)->color);
	if (object->type == CONE)
		return (&((t_cone *) object->object)->color);
	return (NULL);
}

static double	get_closest_object(t_incident_ray *ray,	t_program *program)
{
	double	min_distance;
	double	distance;
	int		o;

	min_distance = -1;
	distance = -1;
	o = 0;
	while (program->objects[o] != NULL)
	{
		distance = to_intersection(program->objects[o],
				program->viewport.camera.position, ray->ray);
		if (0 < distance && (min_distance == -1 || distance < min_distance))
		{
			min_distance = distance;
			ray->incident_point = add(program->viewport.camera.position,
					scalar_product(ray->ray, distance));
			ray->surface_normal = find_normal(program->objects[o],
					ray->incident_point, ray->ray);
			ray->object_color = *get_color(program->objects[o], ray);
		}
		o += 1;
	}
	return (min_distance);
}

static void	generate_pixel(t_data *image, int i, int j, t_program *program)
{
	t_vector		pixel;
	t_color			pixel_color;
	t_incident_ray	ray;
	double			min_distance;

	pixel = subtract(add(program->viewport.pixel_start,
				scalar_product(program->viewport.pixel_dx, i)),
			scalar_product(program->viewport.pixel_dy, j));
	ray.ray = normalise(pixel);
	min_distance = get_closest_object(&ray, program);
	if (0 < min_distance)
	{
		pixel_color = color_multiply(ray.object_color, get_light(&ray,
					&program->ambient, program->lights, program->objects));
		set_pixel(image, i, j, pixel_color);
	}
}

static void	generate_image(t_data *image, t_program *program)
{
	int	i;
	int	j;

	j = 0;
	while (j < program->viewport.window_height)
	{
		i = 0;
		while (i < program->viewport.window_width)
		{
			generate_pixel(image, i, j, program);
			i += 1;
		}
		j += 1;
	}
}

int	render_frame(t_program *program)
{
	t_data	image;

	image.img = mlx_new_image(program->mlx_pointer,
			program->viewport.window_width, program->viewport.window_height);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	generate_image(&image, program);
	mlx_put_image_to_window(program->mlx_pointer, program->window,
		image.img, 0, 0);
	mlx_destroy_image(program->mlx_pointer, image.img);
	return (EXIT_SUCCESS);
}
