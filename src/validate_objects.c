/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:22:03 by hiono             #+#    #+#             */
/*   Updated: 2024/07/18 16:45:40 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_bool	is_valid_sphere(const char *line)
{
	int	index;
	int	result;

	index = ft_strlen("sp");
	result = validate_coordinate(&line[index]);
	if (!result)
		return (err("Invalid coordinate for sphere center"));
	index += result;
	result = validate_udouble(&line[index]);
	if (!result)
		return (err("Invalid double for sphere diameter"));
	index += result;
	result = validate_rgb(&line[index]);
	if (!result)
		return (err("Invalid rgb for sphere color"));
	index += result;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for sphere"));
	return (TRUE);
}

t_bool	is_valid_plane(const char *line)
{
	int	index;
	int	result;

	index = ft_strlen("pl");
	result = validate_coordinate(&line[index]);
	if (!result)
		return (err("Invalid coordinate for plane point"));
	index += result;
	result = validate_normalized_vector(&line[index]);
	if (!result)
		return (err("Invalid normalized vector for plane normal vector"));
	index += result;
	result = validate_rgb(&line[index]);
	if (!result)
		return (err("Invalid rgb for plane color"));
	index += result;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for plane"));
	return (TRUE);
}

t_bool	is_valid_cylinder(const char *line)
{
	int	index;

	index = ft_strlen("cy");
	if (!validate_coordinate(&line[index]))
		return (err("Invalid coordinate for cylinder center"));
	index += validate_coordinate(&line[index]);
	if (!validate_coordinate(&line[index]))
		return (err("Invalid normalized vector for cylinder axis"));
	index += validate_coordinate(&line[index]);
	if (!validate_coordinate(&line[index]))
		return (err("Invalid double for cylinder diameter"));
	index += validate_coordinate(&line[index]);
	if (!validate_coordinate(&line[index]))
		return (err("Invalid double for cylinder height"));
	index += validate_coordinate(&line[index]);
	if (!validate_coordinate(&line[index]))
		return (err("Invalid rgb for cylinder color"));
	index += validate_coordinate(&line[index]);
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for cylinder"));
	return (TRUE);
}
