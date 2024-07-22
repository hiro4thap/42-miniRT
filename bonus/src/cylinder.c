/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:50:53 by hiono             #+#    #+#             */
/*   Updated: 2024/07/21 12:15:11 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// -2 if they never intersect
// -1 if they intersect outside caps
static double	to_cylinder_seam_intersection(t_cylinder *cylinder,
		t_vector origin, t_vector line)
{
	double	grad;
	double	to_front_seam;
	double	to_rear_seam;

	cylinder->rotation = normalise(cylinder->rotation);
	grad = dot(cross(line, cylinder->rotation), cross(line, cylinder->rotation))
		* pow(cylinder->diameter / 2, 2)
		- pow(dot(subtract(cylinder->position, origin),
				cross(line, cylinder->rotation)), 2);
	if (grad < 0)
		return (-2);
	to_front_seam = to_cy_front_seam_intersection(cylinder, origin, line, grad);
	if (to_front_seam != -1)
		return (to_front_seam);
	to_rear_seam = to_cy_rear_seam_intersection(cylinder, origin, line, grad);
	if (to_rear_seam != -1)
		return (to_rear_seam);
	return (-1);
}

static double	to_cylinder_cap_intersection(t_cylinder *cylinder,
		t_vector origin, t_vector line)
{
	double	to_top;
	double	to_buttom;

	if (dot(line, cylinder->rotation) == 0)
		return (-1);
	to_top = to_cy_top_cap_intersection(cylinder, origin, line);
	to_buttom = to_cy_buttom_cap_intersection(cylinder, origin, line);
	if (to_top == -1 && to_buttom == -1)
		return (-1);
	else if (to_buttom == -1)
		return (to_top);
	else if (to_top == -1)
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
