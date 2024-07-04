/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:50:53 by hiono             #+#    #+#             */
/*   Updated: 2024/07/03 19:48:01 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

double	to_cylinder_intersection(t_cylinder cylinder, t_vector origin,
		t_vector line)
{
	double	grad;
	double	distance;
	double	height;

	line = normalise(line);
	cylinder.rotation = normalise(cylinder.rotation);
	grad = dot(cross(line, cylinder.rotation), cross(line, cylinder.rotation))
		* pow(cylinder.diameter / 2, 2)
		- pow(dot(subtract(cylinder.position, origin),
				cross(line, cylinder.rotation)), 2);
	if (grad < 0)
		return (-1);
	distance = (dot(cross(line, cylinder.rotation),
				cross(subtract(cylinder.position, origin), cylinder.rotation))
			- sqrt(grad))
		/ dot(cross(line, cylinder.rotation), cross(line, cylinder.rotation));
	if (distance < 0)
		return (-1);
	height = dot(cylinder.rotation, subtract(scalar_product(line, distance),
				subtract(cylinder.position, origin)));
	if (cylinder.height / 2 < fabs(height))
		return (-1);
	return (distance);
}
