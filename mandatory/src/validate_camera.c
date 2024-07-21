/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_camera.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:20:59 by hiono             #+#    #+#             */
/*   Updated: 2024/07/17 15:21:16 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_bool	is_valid_camera(const char *line)
{
	int	index;
	int	result;

	index = ft_strlen("C");
	result = validate_coordinate(&line[index]);
	if (!result)
		return (err("Invalid coordinate for camera view of point"));
	index += result;
	result = validate_normalized_vector(&line[index]);
	if (!result)
		return (err("Invalid normalized vector for camera orientation"));
	index += result;
	result = validate_double_value(&line[index], 0, 180);
	if (!result)
		return (err("Invalid double for camera field of view"));
	index += result;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for camera"));
	return (TRUE);
}
