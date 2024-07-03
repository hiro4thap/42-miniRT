/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:45:45 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/03 15:00:00 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/color.h"

int	get_red(t_color *color)
{
	return (color->r * 255);
}

int	get_green(t_color *color)
{
	return (color->g * 255);
}

int	get_blue(t_color *color)
{
	return (color->b * 255);
}

t_color	set_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	result;

	result.r = (double) r / 255.0;
	result.g = (double) g / 255.0;
	result.b = (double) b / 255.0;
	return (result);
}

t_color	mix(t_color color_a, double a_ratio, t_color color_b, double b_ratio)
{
	t_color	result;

	result.r = (color_a.r * a_ratio) * (color_b.r * b_ratio);
	result.g = (color_a.g * a_ratio) * (color_b.g * b_ratio);
	result.b = (color_a.b * a_ratio) * (color_b.b * b_ratio);
	return (result);
}
