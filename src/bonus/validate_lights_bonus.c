/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_lights_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:21:34 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 16:12:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/miniRT_bonus.h"

t_bool	is_valid_light_ambient(const char *line)
{
	int	index;
	int	result;

	index = ft_strlen("A");
	result = validate_double_value(&line[index], 0.0, 1.0);
	if (!result)
		return (err("Invalid double for ambient light ratio"));
	index += result;
	result = validate_rgb(&line[index]);
	if (!result)
		return (err("Invalid rgb for ambient light color"));
	index += result;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for ambient light"));
	return (TRUE);
}

t_bool	is_valid_light(const char *line)
{
	int	index;
	int	result;

	index = ft_strlen("L");
	result = validate_coordinate(&line[index]);
	if (!result)
		return (err("Invalid coordinate for light position"));
	index += result;
	result = validate_double_value(&line[index], 0.0, 1.0);
	if (!result)
		return (err("Invallid double for light brightness"));
	index += result;
	result = validate_rgb(&line[index]);
	if (!result)
		return (err("Invallid rgb for light color"));
	index += result;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for light"));
	return (TRUE);
}
