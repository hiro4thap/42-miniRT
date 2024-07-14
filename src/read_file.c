/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:41:39 by hiono             #+#    #+#             */
/*   Updated: 2024/07/14 15:52:16 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	read_content(const char *line, t_program *program,
		int *object_index, int *light_index)
{
	if (!ft_strncmp(line, "A ", 2))
		return (read_light_ambient(line, &program->ambient));
	else if (!ft_strncmp(line, "C ", 2))
		return (read_camera(line, &program->viewport->camera, program));
	else if (!ft_strncmp(line, "L ", 2))
		return (read_light(line, program->lights, (*light_index)++));
	else if (!ft_strncmp(line, "sp ", 3))
		return (read_sphere(line, program->objects, (*object_index)++));
	else if (!ft_strncmp(line, "pl ", 3))
		return (read_plane(line, program->objects, (*object_index)++));
	else if (!ft_strncmp(line, "cy ", 3))
		return (read_cylinder(line, program->objects, (*object_index)++));
	return (EXIT_FAILURE);
}

int	read_file(char *file, t_program *program)
{
	int		fd;
	char	*line;
	int		object_index;
	int		light_index;

	object_index = 0;
	light_index = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Failed to open file :", STDERR_FILENO);
		ft_putendl_fd(file, STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		// TODO:handle the case of failure malloc (free memories as well)
		if (ft_strncmp(line, "\n", 2))
			read_content(line, program, &object_index, &light_index);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
