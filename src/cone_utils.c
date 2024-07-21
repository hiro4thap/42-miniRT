/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:45:21 by hiono             #+#    #+#             */
/*   Updated: 2024/07/21 17:18:55 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	find_grad(t_cone *cone, t_vector origin, double a, double b)
{
	double		c;

	cone->axis = normalise(cone->axis);
	c = dot(vector_in_direction(cone->position, origin),
			vector_in_direction(cone->position, origin))
		- pow(cone->diameter / cone->height, 2)
		* pow(dot(vector_in_direction(cone->position, origin), cone->axis), 2)
		- pow(dot(vector_in_direction(cone->position, origin), cone->axis), 2);
	return (pow(b, 2) - a * c);
}

double	find_height(t_cone *cone, t_vector origin, t_vector line,
		double distance)
{
	t_vector	incident_point;

	incident_point = add(origin, scalar_product(line, distance));
	return (dot(incident_point, cone->axis));
}

double	to_cn_top_cap_intersection(t_cone *cone, t_vector origin, t_vector line)
{
	t_bool	is_intersect_top;
	double	to_top;

	to_top = dot(cone->axis,
			subtract(add(cone->position,
					scalar_product(cone->axis, cone->height / 2)),
				origin))
		/ dot(cone->axis, line);
	is_intersect_top = magnitude(subtract(
				add(origin, scalar_product(line, to_top)),
				add(cone->position,
					scalar_product(cone->axis, cone->height / 2))))
		<= cone->diameter / 2;
	if (!is_intersect_top)
		return (-1);
	return (to_top);
}

double	to_cn_buttom_cap_intersection(t_cone *cone, t_vector origin,
		t_vector line)
{
	t_bool	is_intersect_buttom;
	double	to_buttom;

	to_buttom = dot(cone->axis,
			subtract(subtract(cone->position,
					scalar_product(cone->axis, cone->height / 2)),
				origin))
		/ dot(cone->axis, line);
	is_intersect_buttom = magnitude(subtract(
				add(origin, scalar_product(line, to_buttom)),
				subtract(cone->position,
					scalar_product(cone->axis, cone->height / 2))))
		<= cone->diameter / 2;
	if (!is_intersect_buttom)
		return (-1);
	return (to_buttom);
}
