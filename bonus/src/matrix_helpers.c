/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:26:52 by jeremy            #+#    #+#             */
/*   Updated: 2024/07/21 22:42:16 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrix.h"

/// @brief Updates the row property of matrix to be consistent with changes to
/// the column property.
/// @param m 
void	mat3_update(t_matrix *m)
{
	m->row[0].x = m->col[0].x;
	m->row[0].y = m->col[1].x;
	m->row[0].z = m->col[2].x;
	m->row[1].x = m->col[0].y;
	m->row[1].y = m->col[1].y;
	m->row[1].z = m->col[2].y;
	m->row[2].x = m->col[0].z;
	m->row[2].y = m->col[1].z;
	m->row[2].z = m->col[2].z;
}

t_matrix	mat3_init(double value)
{
	t_matrix	result;

	result.col[0].x = value;
	result.col[0].y = value;
	result.col[0].z = value;
	result.col[1].x = value;
	result.col[1].y = value;
	result.col[1].z = value;
	result.col[2].x = value;
	result.col[2].y = value;
	result.col[2].z = value;
	mat3_update(&result);
	return (result);
}

t_matrix	mat3_init_col(t_vector a, t_vector b, t_vector c)
{
	t_matrix	result;

	set_vector(&result.col[0], a);
	set_vector(&result.col[1], b);
	set_vector(&result.col[2], c);
	mat3_update(&result);
	return (result);
}

t_matrix	mat3_init_row(t_vector a, t_vector b, t_vector c)
{
	t_matrix	result;

	set_vector_components(&result.col[0], a.x, b.x, c.x);
	set_vector_components(&result.col[1], a.y, b.y, c.y);
	set_vector_components(&result.col[2], a.z, b.z, c.z);
	mat3_update(&result);
	return (result);
}

t_matrix	mat3_identity(void)
{
	t_matrix	result;

	result.col[0].x = 1.0;
	result.col[0].y = 0.0;
	result.col[0].z = 0.0;
	result.col[1].x = 0.0;
	result.col[1].y = 1.0;
	result.col[1].z = 0.0;
	result.col[2].x = 0.0;
	result.col[2].y = 0.0;
	result.col[2].z = 1.0;
	mat3_update(&result);
	return (result);
}
