/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 13:45:45 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:12:37 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/color_bonus.h"

/// @brief Get the red channel from given color.
/// @param color The color to get property of.
/// @return Returns red channel of color in [0, 255].
unsigned char	get_red(t_color *color)
{
	if (color->r > 1)
		return (255);
	if (color->r < 0)
		return (0);
	return (color->r * 255);
}

/// @brief Get the green channel from given color.
/// @param color The color to get property of.
/// @return Returns green channel of color in [0, 255].
unsigned char	get_green(t_color *color)
{
	if (color->g > 1)
		return (255);
	if (color->g < 0)
		return (0);
	return (color->g * 255);
}

/// @brief Get the blue channel from given color.
/// @param color The color to get property of.
/// @return Returns blue channel of color in [0, 255].
unsigned char	get_blue(t_color *color)
{
	if (color->b > 1)
		return (255);
	if (color->b < 0)
		return (0);
	return (color->b * 255);
}

/// @brief Returns a color with the RGB channels set.
/// @param r The red channel in [0,255].
/// @param g The green channel in [0,255].
/// @param b The blue channel in [0,255].
/// @return The color with the set RGB channels.
t_color	set_color(unsigned char r, unsigned char g, unsigned char b)
{
	t_color	result;

	result.r = (double) r / 255.0;
	result.g = (double) g / 255.0;
	result.b = (double) b / 255.0;
	return (result);
}
