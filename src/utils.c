/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:21:07 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/03 15:00:09 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	get_pixel_color(t_color col)
{
	int	color;

	color = get_blue(&col)
		+ (get_green(&col) << 8)
		+ (get_red(&col) << 16);
	return (color);
}

void	set_pixel(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = get_pixel_color(color);
}
