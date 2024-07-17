/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:59:10 by hiono             #+#    #+#             */
/*   Updated: 2024/07/17 16:00:55 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_bool	err(char *message)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (FALSE);
}

static t_bool	is_valid_line(const char *line, int *count_ambient_light,
		int *count_camera, int *count_objects, int *count_lights)
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

static t_bool	validate_counts(int count_ambient_light, int count_camera)
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
