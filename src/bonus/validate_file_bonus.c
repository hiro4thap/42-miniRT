/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 11:59:10 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 16:12:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/miniRT_bonus.h"

t_bool	err(char *message)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	return (FALSE);
}

static t_bool	is_valid_line(const char *line, t_counts *counts)
{
	if (!ft_strncmp(line, "A ", 2) && is_valid_light_ambient(line))
	{
		counts->count_ambient_light++;
		return (TRUE);
	}
	else if (!ft_strncmp(line, "C ", 2) && is_valid_camera(line))
	{
		counts->count_camera++;
		return (TRUE);
	}
	else if (!ft_strncmp(line, "L ", 2) && is_valid_light(line))
	{
		counts->count_lights++;
		return (TRUE);
	}
	else if ((!ft_strncmp(line, "sp ", 3) && is_valid_sphere(line))
		|| (!ft_strncmp(line, "pl ", 3) && is_valid_plane(line))
		|| (!ft_strncmp(line, "cy ", 3) && is_valid_cylinder(line))
		|| (!ft_strncmp(line, "cn ", 3) && is_valid_cone(line)))
	{
		counts->count_objects++;
		return (TRUE);
	}
	return (err("File includes a invalid line"));
}

static t_bool	validate_counts(const t_counts *counts)
{
	if (counts->count_ambient_light != 0 && counts->count_ambient_light != 1)
		return (err("Number of ambient light should be 0 or 1"));
	if (counts->count_camera != 1)
		return (err("Number of camera should be 1"));
	return (TRUE);
}

static int	fail_to_open_file(char *file)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd("Failed to open file :", STDERR_FILENO);
	ft_putendl_fd(file, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	validate_file(char *file, t_counts *counts)
{
	int		fd;
	char	*line;

	if (ft_strlen(file) < 3 || ft_strncmp(".rt", &file[ft_strlen(file) - 3], 4))
	{
		err("Invalid file name. File's extension should be .rt");
		return (EXIT_FAILURE);
	}
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (fail_to_open_file(file));
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", 2) && !is_valid_line(line, counts))
		{
			free(line);
			return (EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (close(fd) == -1 || !validate_counts(counts))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
