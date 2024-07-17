/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:00:13 by hiono             #+#    #+#             */
/*   Updated: 2024/07/17 17:04:16 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	to_front_seam_intersection(t_cylinder *cylinder, t_vector origin,
		t_vector line, double grad)
{
	double	to_seam;
	double	height;

	to_seam = (dot(cross(line, cylinder->rotation),
				cross(subtract(cylinder->position, origin), cylinder->rotation))
			- sqrt(grad))
		/ dot(cross(line, cylinder->rotation), cross(line, cylinder->rotation));
	height = dot(cylinder->rotation, subtract(scalar_product(line, to_seam),
				subtract(cylinder->position, origin)));
	if (fabs(height) < cylinder->height / 2)
		return (to_seam);
	return (-1);
}

double	to_rear_seam_intersection(t_cylinder *cylinder, t_vector origin,
		t_vector line, double grad)
{
	double	to_seam;
	double	height;

	to_seam = (dot(cross(line, cylinder->rotation),
				cross(subtract(cylinder->position, origin), cylinder->rotation))
			+ sqrt(grad))
		/ dot(cross(line, cylinder->rotation), cross(line, cylinder->rotation));
	height = dot(cylinder->rotation, subtract(scalar_product(line, to_seam),
				subtract(cylinder->position, origin)));
	if (fabs(height) < cylinder->height / 2)
		return (to_seam);
	return (-1);
}

double	to_top_cap_intersection(t_cylinder *cylinder, t_vector origin,
		t_vector line)
{
	t_bool	is_intersect_top;
	double	to_top;

	to_top = dot(cylinder->rotation,
			subtract(add(cylinder->position,
					scalar_product(cylinder->rotation, cylinder->height / 2)),
				origin))
		/ dot(cylinder->rotation, line);
	is_intersect_top = magnitude(subtract(
				add(origin, scalar_product(line, to_top)),
				add(cylinder->position,
					scalar_product(cylinder->rotation, cylinder->height / 2))))
		<= cylinder->diameter / 2;
	if (!is_intersect_top)
		return (-1);
	return (to_top);
}

double	to_buttom_cap_intersection(t_cylinder *cylinder, t_vector origin,
		t_vector line)
{
	t_bool	is_intersect_buttom;
	double	to_buttom;

	to_buttom = dot(cylinder->rotation,
			subtract(subtract(cylinder->position,
					scalar_product(cylinder->rotation, cylinder->height / 2)),
				origin))
		/ dot(cylinder->rotation, line);
	is_intersect_buttom = magnitude(subtract(
				add(origin, scalar_product(line, to_buttom)),
				subtract(cylinder->position,
					scalar_product(cylinder->rotation, cylinder->height / 2))))
		<= cylinder->diameter / 2;
	if (!is_intersect_buttom)
		return (-1);
	return (to_buttom);
}
