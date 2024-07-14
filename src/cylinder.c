/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:50:53 by hiono             #+#    #+#             */
/*   Updated: 2024/07/14 16:01:15 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// -2 if they never intersect
// -1 if they intersect outside caps
static double	to_cylinder_seam_intersection(t_cylinder *cylinder,
		t_vector origin, t_vector line)
{
	double	grad;
	double	to_seam;
	double	height;
	double	to_seam_alt;
	double	height_alt;

	cylinder->rotation = normalise(cylinder->rotation);
	grad = dot(cross(line, cylinder->rotation), cross(line, cylinder->rotation))
		* pow(cylinder->diameter / 2, 2)
		- pow(dot(subtract(cylinder->position, origin),
				cross(line, cylinder->rotation)), 2);
	if (grad < 0)
		return (-2);
	to_seam = (dot(cross(line, cylinder->rotation),
				cross(subtract(cylinder->position, origin), cylinder->rotation))
			- sqrt(grad))
		/ dot(cross(line, cylinder->rotation), cross(line, cylinder->rotation));
	height = dot(cylinder->rotation, subtract(scalar_product(line, to_seam),
				subtract(cylinder->position, origin)));
	if (fabs(height) < cylinder->height / 2)
		return (to_seam);
	to_seam_alt = (dot(cross(line, cylinder->rotation),
				cross(subtract(cylinder->position, origin), cylinder->rotation))
			+ sqrt(grad))
		/ dot(cross(line, cylinder->rotation), cross(line, cylinder->rotation));
	height_alt = dot(cylinder->rotation, subtract(scalar_product(line, to_seam_alt),
				subtract(cylinder->position, origin)));
	if (fabs(height_alt) < cylinder->height / 2)
		return (to_seam_alt);
	return (-1);
}

static double	to_cylinder_cap_intersection(t_cylinder *cylinder,
		t_vector origin, t_vector line)
{
	double	to_top;
	t_bool	is_intersect_top;
	double	to_buttom;
	t_bool	is_intersect_buttom;

	if (dot(line, cylinder->rotation) == 0)
		return (-1);
	to_top = dot(cylinder->rotation,
			subtract(add(cylinder->position, scalar_product(cylinder->rotation, cylinder->height / 2)),
		origin))
	/ dot(cylinder->rotation, line);
	is_intersect_top = magnitude(subtract(add(origin, scalar_product(line, to_top)),
				add(cylinder->position,
			scalar_product(cylinder->rotation, cylinder->height / 2)))) <= cylinder->diameter / 2;
	to_buttom = dot(cylinder->rotation,
			subtract(subtract(cylinder->position, scalar_product(cylinder->rotation, cylinder->height / 2)),
		origin))
	/ dot(cylinder->rotation, line);
	is_intersect_buttom = magnitude(subtract(add(origin, scalar_product(line, to_top)),
				subtract(cylinder->position,
			scalar_product(cylinder->rotation, cylinder->height / 2)))) <= cylinder->diameter / 2;
	if (!is_intersect_top && !is_intersect_buttom)
		return (-1);
	else if (is_intersect_top)
		return (to_top);
	else if (is_intersect_buttom)
		return (to_buttom);
	return (min(to_top, to_buttom));
}

double	to_cylinder_intersection(t_cylinder *cylinder, t_vector origin,
		t_vector line)
{
	double	to_seam;
	double	to_cap;

	line = normalise(line);
	to_seam = to_cylinder_seam_intersection(cylinder, origin, line);
	to_cap = to_cylinder_cap_intersection(cylinder, origin, line);
	if (to_seam == -2)
		return (-1);
	else if (to_seam == -1)
		return (to_cap);
	else if (to_cap == -1)
		return (to_seam);
	else
		return (min(to_seam, to_cap));
}

t_vector	cylinder_normal(t_cylinder *cylinder, t_vector incident_point)
{
	double		height;
	t_vector	axis_to_seam;

	height = dot(normalise(cylinder->rotation),
			vector_in_direction(cylinder->position, incident_point));
	if (fabs(height - cylinder->height / 2) < 1e-10)
		return (normalise(cylinder->rotation));
	else if (fabs(height + cylinder->height / 2) < 1e-10)
		return (scalar_product(normalise(cylinder->rotation), -1));
	axis_to_seam = vector_in_direction(add(cylinder->position,
				scalar_product(normalise(cylinder->rotation), height)),
			incident_point);
	return (normalise(axis_to_seam));
}
