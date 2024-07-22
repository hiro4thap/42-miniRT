/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 22:37:24 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/21 22:39:30 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/uvmap.h"

t_color	uv_checkerboard(t_uvpoint point, int scale)
{
	t_color		result;
	double		ratio;
	t_uvpoint	reduced_coord;

	ratio = 1.0 / (double) scale;
	reduced_coord.u = fmod(point.u, ratio) * scale;
	reduced_coord.v = fmod(point.v, ratio) * scale;
	if ((reduced_coord.u < 0.5 && reduced_coord.v < 0.5)
		|| (reduced_coord.u >= 0.5 && reduced_coord.v >= 0.5))
		result = set_color(0, 0, 0);
	else
		result = set_color(255, 255, 255);
	return (result);
}

// extern t_program	program;
// extern int			texture_height;
// extern int			texture_width;
// extern t_data		texture;
// // Get vector from change in pixels pointing up from the plane. 
// // 
// t_vector uv_bumpmap(t_uvpoint point)
// {
// 	// t_data		image;
// 	// int			width;
// 	// int			height;
// 	t_color		sample[4];
// 	t_vector	result;
// 	t_vector	du;
// 	t_vector	dv;

// 	//ft_printf("Here\n");
// 	// image.img = mlx_xpm_file_to_image(program.mlx_pointer, "img/heightmap.xpm", &width, &height);
// 	// image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
// 	// 		&image.line_length, &image.endian);
// 	sample[0] = get_pixel(&texture, ((int) (point.u * texture_width) + 1) % texture_width, point.v * texture_height);
// 	sample[1] = get_pixel(&texture, ((int) (point.u * texture_width) - 1) % texture_width, point.v * texture_height);
// 	sample[2] = get_pixel(&texture, point.u * texture_width, ((int) (point.v * texture_height) + 1) % texture_height);
// 	sample[3] = get_pixel(&texture, point.u * texture_width, ((int) (point.v * texture_height) - 1) % texture_height);
	
// 	set_vector_components(&du, 1, 0, 0.05 * (get_red(&sample[0]) - get_red(&sample[1])) / 2.0);
// 	set_vector_components(&dv, 0, 1, 0.05 * (get_red(&sample[2]) - get_red(&sample[3])) / 2.0);
// 	result = normalise(cross(du, dv));
// 	//mlx_destroy_image(program.mlx_pointer, texture.img);
// 	return (result);
// }

// #include <stdio.h>
// extern t_data	texture;
// extern int		texture_width;
// extern int		texture_height;
// t_color uv_texture(t_uvpoint point)
// {
// 	t_color		sample;

// 	sample = get_pixel(&texture, point.u * texture_width, point.v * texture_height);
// 	return (sample);
// }
