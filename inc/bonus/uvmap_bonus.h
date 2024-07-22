/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvmap_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 08:56:06 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:23:10 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UVMAP_BONUS_H
# define UVMAP_BONUS_H

# ifndef __linux__
#  include "../lib/libmlx/mlx.h"
# else
#  include "../lib/libmlx_Linux/mlx.h"
# endif
# include "../lib/libft/inc/libft.h"

# include "matrix_bonus.h"
# include "vector_bonus.h"
# include "objects_bonus.h"
# include "color_bonus.h"
# include "mlx_helpers_bonus.h"

typedef struct s_uvpoint
{
	double		u;
	double		v;
	t_matrix	basis;
}	t_uvpoint;

t_uvpoint	uvmap(t_vector coordnates, t_object *object);

t_color		uv_checkerboard(t_uvpoint point, int scale);
t_vector	uv_bumpmap(t_uvpoint point, t_texture *bump_map);

#endif
