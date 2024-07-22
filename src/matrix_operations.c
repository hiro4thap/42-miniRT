/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:27:15 by jeremy            #+#    #+#             */
/*   Updated: 2024/07/21 22:41:19 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrix.h"

t_matrix	mat3_matrix_multiply(t_matrix a, t_matrix b)
{
	t_matrix	result;

	result.col[0] = mat3_vector_multiply(a, b.col[0]);
	result.col[1] = mat3_vector_multiply(a, b.col[1]);
	result.col[2] = mat3_vector_multiply(a, b.col[2]);
	mat3_update(&result);
	return (result);
}

/// @brief Calculates M x v.
/// @param m A 3x3 matrix.
/// @param v A vector (3x1 column matrix).
/// @return Result as a column vector (3x1 matrix), 
t_vector	mat3_vector_multiply(t_matrix m, t_vector v)
{
	t_vector	result;

	result.x = dot(m.row[0], v);
	result.y = dot(m.row[1], v);
	result.z = dot(m.row[2], v);
	return (result);
}

t_matrix	mat3_transpose(t_matrix m)
{
	t_matrix	result;

	result.col[0] = m.row[0];
	result.col[1] = m.row[1];
	result.col[2] = m.row[2];
	mat3_update(&result);
	return (result);
}
