/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:44:00 by hiono             #+#    #+#             */
/*   Updated: 2024/07/06 17:25:00 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// if no intersection, return value is -1
double	to_sphere_intersection(t_sphere *sphere, t_vector origin, t_vector line)
{
	double	grad;
	double	distance;

	line = normalise(line);
	grad = pow(dot(line, subtract(origin, sphere->position)), 2.0)
		- pow(magnitude(subtract(origin, sphere->position)), 2.0)
		+ pow((sphere->diameter / 2.0), 2.0);
	if (grad < 0)
		return (-1);
	distance = -dot(line, subtract(origin, sphere->position)) - sqrt(grad);
	if (distance < 0)
		return (-1);
	return (distance);
}

t_vector	sphere_normal(t_sphere *sphere, t_vector incident_point)
{
	return (normalise(vector_in_direction(sphere->position, incident_point)));
}
