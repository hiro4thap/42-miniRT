/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:23:51 by jhughes           #+#    #+#             */
/*   Updated: 2024/04/22 14:13:31 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>

# ifndef __linux__
#  include "../lib/libmlx/mlx.h"
# else
#  include "../lib/libmlx_Linux/mlx.h"
# endif
# include "../lib/libft/inc/libft.h"

# include "definitions.h"
# include "vector.h"
# include "objects.h"
# include "color.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;


typedef struct s_program
{
	void	*mlx_pointer;
	void	*window;
}	t_program;


#endif
