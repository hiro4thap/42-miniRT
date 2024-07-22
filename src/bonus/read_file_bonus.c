/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:41:39 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 16:12:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/miniRT_bonus.h"

static int	read_content(const char *line, t_program *program,
	int *object_index, int *light_index)
{
	if (!ft_strncmp(line, "A ", 2))
		return (read_light_ambient(line, &program->ambient));
	else if (!ft_strncmp(line, "C ", 2))
		return (read_camera(line, &program->viewport.camera, program));
	else if (!ft_strncmp(line, "L ", 2))
		return (read_light(line, program->lights, (*light_index)++));
	else if (!ft_strncmp(line, "sp ", 3))
		return (read_sphere(line, program->objects, (*object_index)++));
	else if (!ft_strncmp(line, "pl ", 3))
		return (read_plane(line, program->objects, (*object_index)++));
	else if (!ft_strncmp(line, "cy ", 3))
		return (read_cylinder(line, program->objects, (*object_index)++));
	else if (!ft_strncmp(line, "cn ", 3))
		return (read_cone(line, program->objects, (*object_index)++));
	return (EXIT_FAILURE);
}

static int	open_file(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd("Failed to open file :", STDERR_FILENO);
		ft_putendl_fd(file, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	read_file(char *file, t_program *program)
{
	int		fd;
	char	*line;
	int		object_index;
	int		light_index;
	int		result;

	object_index = 0;
	light_index = 0;
	if (open_file(file, &fd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "\n", 2))
			result = read_content(line, program, &object_index, &light_index);
		free(line);
		if (result == EXIT_FAILURE)
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	return (result);
}
