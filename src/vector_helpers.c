/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:23:29 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/03 16:55:45 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vector.h"

/// @brief This may need an error tolerance.
/// @param a 
/// @param b 
/// @return 
t_bool	equal(t_vector a, t_vector b)
{
	if ((a.x == b.x)
		&& (a.y == b.y)
		&& (a.z == b.z))
		return (TRUE);
	return (FALSE);
}

t_vector	normalise(t_vector a)
{
	const double	norm = magnitude(a);
	t_vector		result;

	set_vector_components(&result, a.x / norm, a.y / norm, a.z / norm);
	return (result);
}

double	magnitude(t_vector a)
{
	return (sqrt(dot(a, a)));
}

double	angle_between(t_vector a, t_vector b)
{
	return (acos(dot(a, b) / (magnitude(a) * magnitude(b))));
}

t_vector	vector_in_direction(t_vector from, t_vector to)
{
	return (subtract(to, from));
}
