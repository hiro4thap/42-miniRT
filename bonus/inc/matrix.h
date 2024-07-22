/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 14:17:51 by jeremy            #+#    #+#             */
/*   Updated: 2024/07/22 09:46:01 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"

typedef struct s_matrix
{
	t_vector	row[3];
	t_vector	col[3];
}	t_matrix;

void		mat3_update(t_matrix *m);
t_matrix	mat3_init(double value);
t_matrix	mat3_init_col(t_vector a, t_vector b, t_vector c);
t_matrix	mat3_init_row(t_vector a, t_vector b, t_vector c);
t_matrix	mat3_identity(void);

t_matrix	mat3_set(t_matrix m, int row, int column, double value);
t_matrix	mat3_add(t_matrix a, t_matrix b);
t_matrix	mat3_sub(t_matrix a, t_matrix b);
void		mat3_print(t_matrix m, char *s);

t_matrix	mat3_matrix_multiply(t_matrix a, t_matrix b);
t_vector	mat3_vector_multiply(t_matrix m, t_vector v);
t_matrix	mat3_transpose(t_matrix m);

#endif