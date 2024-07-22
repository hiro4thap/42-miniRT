/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:58:02 by jeremy            #+#    #+#             */
/*   Updated: 2024/07/21 22:42:32 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/matrix.h"

t_matrix	mat3_set(t_matrix m, int row, int column, double value)
{
	if (row == 0)
		m.col[column].x = value;
	else if (row == 1)
		m.col[column].y = value;
	else if (row == 2)
		m.col[column].z = value;
	mat3_update(&m);
	return (m);
}

t_matrix	mat3_add(t_matrix a, t_matrix b)
{
	t_matrix	result;

	result.col[0] = add(a.col[0], b.col[0]);
	result.col[1] = add(a.col[1], b.col[1]);
	result.col[2] = add(a.col[2], b.col[2]);
	mat3_update(&result);
	return (result);
}

t_matrix	mat3_sub(t_matrix a, t_matrix b)
{
	t_matrix	result;

	result.col[0] = subtract(a.col[0], b.col[0]);
	result.col[1] = subtract(a.col[1], b.col[1]);
	result.col[2] = subtract(a.col[2], b.col[2]);
	mat3_update(&result);
	return (result);
}

void	mat3_print(t_matrix m, char *s)
{
	printf("Matrix: %s\n", s);
	printf("{%3.2lf  %3.2lf  %3.2lf}\n", m.row[0].x, m.row[0].y, m.row[0].z);
	printf("{%3.2lf  %3.2lf  %3.2lf}\n", m.row[1].x, m.row[1].y, m.row[1].z);
	printf("{%3.2lf  %3.2lf  %3.2lf}\n", m.row[2].x, m.row[2].y, m.row[2].z);
	printf("\n");
}
