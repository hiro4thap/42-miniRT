/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:10:29 by hiono             #+#    #+#             */
/*   Updated: 2024/07/03 17:26:48 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// if no intersection or line inside plane, return value is -1
double	to_plane_intersection(t_plane plane, t_vector origin, t_vector line)
{
	double	distance;

	line = normalise(line);
	if (dot(line, plane.normal) == 0)
		return (-1);
	distance = dot(subtract(plane.position, origin), plane.normal)
		/ dot(line, plane.normal);
	if (distance < 0)
		return (-1);
	return (distance);
}
