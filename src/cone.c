/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:10:24 by hiono             #+#    #+#             */
/*   Updated: 2024/07/21 17:18:02 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static double	to_cone_seam_intersection(t_cone *cone, t_vector origin,
		t_vector line)
{
	double	a;
	double	b;
	double	grad;
	double	to_front_seam;
	double	to_rear_seam;

	cone->axis = normalise(cone->axis);
	a = dot(line, line) - pow(cone->diameter / cone->height, 2)
		* pow(dot(line, cone->axis), 2)
		- pow(dot(line, cone->axis), 2);
	b = dot(line, vector_in_direction(cone->position, origin))
		- pow(cone->diameter / cone->height, 2) * dot(line, cone->axis)
		* dot(vector_in_direction(cone->position, origin), cone->axis)
		- dot(line, cone->axis)
		* dot(vector_in_direction(cone->position, origin), cone->axis);
	grad = find_grad(cone, origin, a, b);
	if (grad < 0)
		return (-2);
	to_front_seam = (-b - sqrt(grad)) / a;
	if (fabs(find_height(cone, origin, line, to_front_seam)) < cone->height / 2)
		return (to_front_seam);
	to_rear_seam = (-b + sqrt(grad)) / a;
	if (fabs(find_height(cone, origin, line, to_rear_seam)) < cone->height / 2)
		return (to_rear_seam);
	return (-1);
}

static double	to_cone_cap_intersection(t_cone *cone, t_vector origin,
		t_vector line)
{
	double	to_top;
	double	to_buttom;

	if (dot(line, cone->axis) == 0)
		return (-1);
	to_top = to_cn_top_cap_intersection(cone, origin, line);
	to_buttom = to_cn_buttom_cap_intersection(cone, origin, line);
	if (to_top == -1 && to_buttom == -1)
		return (-1);
	else if (to_buttom == -1)
		return (to_top);
	else if (to_top == -1)
		return (to_buttom);
	return (min(to_top, to_buttom));
}

double	to_cone_intersection(t_cone *cone, t_vector origin, t_vector line)
{
	double	to_seam;
	double	to_cap;

	line = normalise(line);
	to_seam = to_cone_seam_intersection(cone, origin, line);
	to_cap = to_cone_cap_intersection(cone, origin, line);
	if (to_seam == -2)
		return (-1);
	else if (to_seam == -1)
		return (to_cap);
	else if (to_cap == -1)
		return (to_seam);
	else
		return (min(to_seam, to_cap));
}

t_vector	cone_normal(t_cone *cone, t_vector incident_point)
{
	double		height;
	t_vector	point_on_axis;

	height = dot(normalise(cone->axis),
			vector_in_direction(cone->position, incident_point));
	if (fabs(height - cone->height / 2) < 1e-10)
		return (normalise(cone->axis));
	else if (fabs(height + cone->height / 2) < 1e-10)
		return (scalar_product(normalise(cone->axis), -1));
	if (0
		< dot(vector_in_direction(cone->position, incident_point), cone->axis))
		point_on_axis = scalar_product(cone->axis,
				magnitude(vector_in_direction(cone->position, incident_point))
				* sqrt(1 + pow(cone->diameter / 2 / cone->height, 2)));
	else
		point_on_axis = scalar_product(cone->axis,
				-magnitude(vector_in_direction(cone->position, incident_point))
				* sqrt(1 + pow(cone->diameter / 2 / cone->height, 2)));
	return (normalise(vector_in_direction(point_on_axis, incident_point)));
}
