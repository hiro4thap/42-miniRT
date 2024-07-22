/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_objects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:22:03 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 15:23:59 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	validate_flags(const char *line, char *object_type)
{
	int	index;

	index = 0;
	if (!validate_flag(&line[index]))
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putstr_fd("Invalid flag for ", STDERR_FILENO);
		ft_putstr_fd(object_type, STDERR_FILENO);
		ft_putendl_fd(" material", STDERR_FILENO);
		return (0);
	}
	index += validate_flag(&line[index]);
	if (!validate_flag(&line[index]))
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putstr_fd("Invalid flag for ", STDERR_FILENO);
		ft_putstr_fd(object_type, STDERR_FILENO);
		ft_putendl_fd(" bump map", STDERR_FILENO);
		return (0);
	}
	index += validate_flag(&line[index]);
	return (index);
}

t_bool	is_valid_sphere(const char *line)
{
	int	index;

	index = ft_strlen("sp");
	if (!validate_coordinate(&line[index]))
		return (err("Invalid coordinate for sphere center"));
	index += validate_coordinate(&line[index]);
	if (!validate_udouble(&line[index]))
		return (err("Invalid double for sphere diameter"));
	index += validate_udouble(&line[index]);
	if (!validate_rgb(&line[index]))
		return (err("Invalid rgb for sphere color"));
	index += validate_rgb(&line[index]);
	if (!validate_flags(&line[index], "sphere"))
		return (0);
	index += validate_flags(&line[index], "sphere");
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for sphere"));
	return (TRUE);
}

t_bool	is_valid_plane(const char *line)
{
	int	index;

	index = ft_strlen("pl");
	if (!validate_coordinate(&line[index]))
		return (err("Invalid coordinate for plane point"));
	index += validate_coordinate(&line[index]);
	if (!validate_normalized_vector(&line[index]))
		return (err("Invalid normalized vector for plane normal vector"));
	index += validate_normalized_vector(&line[index]);
	if (!validate_rgb(&line[index]))
		return (err("Invalid rgb for plane color"));
	index += validate_rgb(&line[index]);
	if (!validate_flags(&line[index], "plane"))
		return (0);
	index += validate_flags(&line[index], "plane");
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
	if (!validate_normalized_vector(&line[index]))
		return (err("Invalid normalized vector for cylinder axis"));
	index += validate_normalized_vector(&line[index]);
	if (!validate_udouble(&line[index]))
		return (err("Invalid double for cylinder diameter"));
	index += validate_udouble(&line[index]);
	if (!validate_udouble(&line[index]))
		return (err("Invalid double for cylinder height"));
	index += validate_udouble(&line[index]);
	if (!validate_rgb(&line[index]))
		return (err("Invalid rgb for cylinder color"));
	index += validate_rgb(&line[index]);
	if (!validate_flags(&line[index], "cylinder"))
		return (0);
	index += validate_flags(&line[index], "cylinder");
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for cylinder"));
	return (TRUE);
}

t_bool	is_valid_cone(const char *line)
{
	int	index;

	index = ft_strlen("cn");
	if (!validate_coordinate(&line[index]))
		return (err("Invalid coordinate for cone point"));
	index += validate_coordinate(&line[index]);
	if (!validate_normalized_vector(&line[index]))
		return (err("Invalid normalized vector for cone axis"));
	index += validate_normalized_vector(&line[index]);
	if (!validate_udouble(&line[index]))
		return (err("Invalid double for cone diameter"));
	index += validate_udouble(&line[index]);
	if (!validate_udouble(&line[index]))
		return (err("Invalid double for cone height"));
	index += validate_udouble(&line[index]);
	if (!validate_coordinate(&line[index]))
		return (err("Invalid rgb for cone color"));
	index += validate_coordinate(&line[index]);
	if (!validate_flags(&line[index], "cone"))
		return (0);
	index += validate_flags(&line[index], "cone");
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for cone"));
	return (TRUE);
}
