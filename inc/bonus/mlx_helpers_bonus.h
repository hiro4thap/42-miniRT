/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 10:44:45 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:23:47 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HELPERS_BONUS_H
# define MLX_HELPERS_BONUS_H

# include "objects_bonus.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_viewport
{
	int			window_width;
	int			window_height;
	t_camera	camera;
	t_vector	pixel_dx;
	t_vector	pixel_dy;
	t_vector	pixel_start;
}	t_viewport;

typedef struct s_program
{
	void			*mlx_pointer;
	void			*window;
	t_viewport		viewport;
	t_object		**objects;
	t_light			**lights;
	t_light_ambient	ambient;
}	t_program;

t_color	get_pixel(t_data *data, int x, int y);

#endif
