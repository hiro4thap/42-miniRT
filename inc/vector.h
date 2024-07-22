/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:25:34 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 09:16:22 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>
# include <stdio.h>

# include "definitions.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

// vector.c
void		set_vector(t_vector *vector, t_vector const ref);
void		set_vector_components(t_vector *vector,
				double x, double y, double z);
void		print_vector(t_vector a);

// vector_operations.c
t_vector	scalar_product(t_vector a, double n);
t_vector	add(t_vector a, t_vector b);
t_vector	subtract(t_vector a, t_vector b);
t_vector	multiply(t_vector a, t_vector b);
t_vector	cross(t_vector a, t_vector b);
double		dot(t_vector a, t_vector b);

// vector_helpers.c
t_bool		equal(t_vector a, t_vector b);
t_vector	normalise(t_vector a);
double		magnitude(t_vector a);
double		angle_between(t_vector a, t_vector b);
t_vector	vector_in_direction(t_vector from, t_vector to);

#endif