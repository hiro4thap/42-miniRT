/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:23:47 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/21 20:06:27 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/vector.h"

t_vector	vector_init(double x, double y, double z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

void	set_vector(t_vector *vector, t_vector const ref)
{
	vector->x = ref.x;
	vector->y = ref.y;
	vector->z = ref.z;
}

void	set_vector_components(t_vector *vector, double x, double y, double z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

void	print_vector(t_vector a)
{
	printf("(%lf, %lf, %lf)", a.x, a.y, a.z);
}
