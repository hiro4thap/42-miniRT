/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:59:10 by hiono             #+#    #+#             */
/*   Updated: 2024/07/13 14:23:56 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_bool	err(char *message)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (FALSE);
}

int	validate_double(const char *number)
{
	int		index;

	index = 0;
	while (number[index] == ' ')
		index++;
	if (number[index] == '-')
		index++;
	if (!ft_isdigit(number[index]))
		return (0);
	while (ft_isdigit(number[index]))
		index++;
	if (number[index] == '.')
	{
		index++;
		if (!ft_isdigit(number[index]))
			return (0);
		while (ft_isdigit(number[index]))
			index++;
	}
	return (index);
}

int	validate_udouble(const char *number)
{
	int		index;
	double	value;

	if (!validate_double(number))
		return (0);
	index = read_double(number, &value);
	if (value < 0)
		return (0);
	return (index);
}

int	validate_double_value(const char *number, double min, double max)
{
	int		index;
	double	value;

	if (!validate_double(number))
		return (0);
	index = read_double(number, &value);
	if (value < min || max < value)
		return (0);
	return (index);
}

int	validate_rgb(const char *rgb)
{
	int	index;
	int	itr;
	int	temp;

	index = 0;
	itr = 0;
	while (rgb[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (rgb[index] == ',')
			index++;
		temp = validate_double_value(&rgb[index], 0, 255);
		if (!temp)
			return (0);
		index += temp;
		itr++;
	}
	return (index);
}

int	validate_coordinate(const char *coordinate)
{
	int	index;
	int	itr;
	int	temp;

	index = 0;
	itr = 0;
	while (coordinate[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (coordinate[index] == ',')
			index++;
		temp = validate_double(&coordinate[index]);
		if (!temp)
			return (0);
		index += temp;
		itr++;
	}
	return (index);
}

int	validate_normalized_vector(const char *normalized_vector)
{
	int	index;
	int	itr;
	int	temp;

	index = 0;
	itr = 0;
	while (normalized_vector[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (normalized_vector[index] == ',')
			index++;
		temp = validate_double_value(&normalized_vector[index], -1, 1);
		if (!temp)
			return (0);
		index += temp;
		itr++;
	}
	return (index);
}

t_bool	is_valid_light_ambient(const char *line)
{
	int	index;
	int	temp;

	index = ft_strlen("A");
	temp = validate_double_value(&line[index], 0.0, 1.0);
	if (!temp)
		return (err("Invalid double for ambient light ratio"));
	index += temp;
	temp = validate_rgb(&line[index]);
	if (!temp)
		return (err("Invalid rgb for ambient light color"));
	index += temp;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for ambient light"));
	return (TRUE);
}

t_bool	is_valid_camera(const char *line)
{
	int	index;
	int	temp;

	index = ft_strlen("C");
	temp = validate_coordinate(&line[index]);
	if (!temp)
		return (err("Invalid coordinate for camera view of point"));
	index += temp;
	temp += validate_normalized_vector(&line[index]);
	if (!temp)
		return (err("Invalid normalized vector for camera orientation"));
	index += temp;
	temp += validate_double_value(&line[index], 0, 180);
	if (!temp)
		return (err("Invalid double for camera field of view"));
	index += temp;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for camera"));
	return (TRUE);
}

t_bool	is_valid_light(const char *line)
{
	int	index;
	int	temp;

	index = ft_strlen("L");
	temp = validate_coordinate(&line[index]);
	if (!temp)
		return (err("Invalid coordinate for light position"));
	index += temp;
	temp = validate_double_value(&line[index], 0.0, 1.0);
	if (!temp)
		return (err("Invallid double for light brightness"));
	index += temp;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for light"));
	return (TRUE);
}

t_bool	is_valid_sphere(const char *line)
{
	int	index;
	int	temp;

	index = ft_strlen("sp");
	temp = validate_coordinate(&line[index]);
	if (!temp)
		return (err("Invalid coordinate for sphere center"));
	index += temp;
	temp = validate_udouble(&line[index]);
	if (!temp)
		return (err("Invalid double for sphere diameter"));
	index += temp;
	temp = validate_rgb(&line[index]);
	if (!temp)
		return (err("Invalid rgb for sphere color"));
	index += temp;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for sphere"));
	return (TRUE);
}

t_bool	is_valid_plane(const char *line)
{
	int	index;
	int	temp;

	index = ft_strlen("pl");
	temp = validate_coordinate(&line[index]);
	if (!temp)
		return (err("Invalid coordinate for plane point"));
	index += temp;
	temp = validate_normalized_vector(&line[index]);
	if (!temp)
		return (err("Invalid normalized vector for plane normal vector"));
	index += temp;
	temp = validate_rgb(&line[index]);
	if (!temp)
		return (err("Invalid rgb for plane color"));
	index += temp;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for plane"));
	return (TRUE);
}

t_bool	is_valid_cylinder(const char *line)
{
	int	index;
	int	temp;

	index = ft_strlen("cy");
	temp = validate_coordinate(&line[index]);
	if (!temp)
		return (err("Invalid coordinate for cylinder center"));
	index += temp;
	temp = validate_normalized_vector(&line[index]);
	if (!temp)
		return (err("Invalid normalized vector for cylinder axis"));
	index += temp;
	temp = validate_udouble(&line[index]);
	if (!temp)
		return (err("Invalid double for cylinder diameter"));
	index += temp;
	temp = validate_udouble(&line[index]);
	if (!temp)
		return (err("Invalid double for cylinder height"));
	index += temp;
	temp = validate_rgb(&line[index]);
	if (!temp)
		return (err("Invalid rgb for cylinder color"));
	index += temp;
	if (line[index] != '\n' && line[index] != '\0')
		return (err("Excessive information for cylinder"));
	return (TRUE);
}

t_bool	is_valid_line(const char *line, int *count_ambient_light, int *count_camera, int *count_objects, int *count_lights)
{
	if (!ft_strncmp(line, "A ", 2) && is_valid_light_ambient(line))
	{
		(*count_ambient_light)++;
		return (TRUE);
	}
	else if (!ft_strncmp(line, "C ", 2) && is_valid_camera(line))
	{
		(*count_camera)++;
		return (TRUE);
	}
	else if (!ft_strncmp(line, "L ", 2) && is_valid_light(line))
	{
		(*count_lights)++;
		return (TRUE);
	}
	else if ((!ft_strncmp(line, "sp ", 3) && is_valid_sphere(line))
		|| (!ft_strncmp(line, "pl ", 3) && is_valid_plane(line))
		|| (!ft_strncmp(line, "cy ", 3) && is_valid_cylinder(line)))
	{
		(*count_objects)++;
		return (TRUE);
	}
	return (err("File includes a invalid line"));
}

t_bool	validate_counts(int count_ambient_light, int count_camera)
{
	if (count_ambient_light != 0 && count_ambient_light != 1)
		return (err("Number of ambient light should be 0 or 1"));
	if (count_camera != 1)
		return (err("Number of camera should be 1"));
	return (TRUE);
}

int	validate(char *file, int *count_objects, int *count_lights)
{
	int		fd;
	char	*line;
	int		count_ambient_light;
	int		count_camera;

	count_ambient_light = 0;
	count_camera = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error", STDERR_FILENO);
		ft_putstr_fd("Failed to open file :", STDERR_FILENO);
		ft_putendl_fd(file, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", 2) && !is_valid_line(line, &count_ambient_light, &count_camera, count_objects, count_lights))
		{
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	validate_counts(count_ambient_light, count_camera);
	close(fd);
	return (EXIT_SUCCESS);
}
