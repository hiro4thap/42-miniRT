/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:53:43 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:12:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/color_bonus.h"

/// @brief Returns a proportion of a color.
/// @param color The color with RGB channels in [0,1].
/// @param ratio The proportion of color to return in [0,1].
/// @return The required proportion of the color.
t_color	color_proportion(t_color color, double ratio)
{
	color.r *= ratio;
	color.g *= ratio;
	color.b *= ratio;
	return (color);
}

/// @brief Adds the RGB components of the two colors.
/// @param color_a 
/// @param color_b 
/// @return The result of the color addition. RGB channels may exceed [0,1].
t_color	color_add(t_color color_a, t_color color_b)
{
	t_color	result;

	result.r = color_a.r + color_b.r;
	result.g = color_a.g + color_b.g;
	result.b = color_a.b + color_b.b;
	return (result);
}

/// @brief Multiply the RGB components of the two colors.
/// @param color_a 
/// @param color_b 
/// @return Result of multiplication. RGB channels will be in [0,1] if input
/// colors are in [0,1].
t_color	color_multiply(t_color color_a, t_color color_b)
{
	t_color	result;

	result.r = color_a.r * color_b.r;
	result.g = color_a.g * color_b.g;
	result.b = color_a.b * color_b.b;
	return (result);
}
