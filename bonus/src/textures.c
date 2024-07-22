/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:37:24 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 11:11:33 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/uvmap.h"

t_color	uv_checkerboard(t_uvpoint point, int scale)
{
	t_color		result;
	double		ratio;
	t_uvpoint	reduced_coord;

	ratio = 1.0 / (double) scale;
	reduced_coord.u = fmod(point.u, ratio) * scale;
	reduced_coord.v = fmod(point.v, ratio) * scale;
	if ((reduced_coord.u < 0.5 && reduced_coord.v < 0.5)
		|| (reduced_coord.u >= 0.5 && reduced_coord.v >= 0.5))
		result = set_color(0, 0, 0);
	else
		result = set_color(255, 255, 255);
	return (result);
}

// Get vector from change in pixels pointing up from the plane. 
t_vector	uv_bumpmap(t_uvpoint point, t_texture *bump_map)
{
	t_color		sample[4];
	t_vector	result;
	t_vector	du;
	t_vector	dv;

	sample[0] = get_pixel(bump_map->texture,
			((int)(point.u * bump_map->width) + 1) % bump_map->width,
			point.v * bump_map->height);
	sample[1] = get_pixel(bump_map->texture,
			((int)(point.u * bump_map->width) - 1) % bump_map->width,
			point.v * bump_map->height);
	sample[2] = get_pixel(bump_map->texture,
			point.u * bump_map->width,
			((int)(point.v * bump_map->height) + 1) % bump_map->height);
	sample[3] = get_pixel(bump_map->texture,
			point.u * bump_map->width,
			((int)(point.v * bump_map->height) - 1) % bump_map->height);
	du = vector_init(1, 0,
			0.05 * (get_red(&sample[0]) - get_red(&sample[1])) / 2.0);
	dv = vector_init(0, 1,
			0.05 * (get_red(&sample[2]) - get_red(&sample[3])) / 2.0);
	result = normalise(cross(du, dv));
	return (result);
}
