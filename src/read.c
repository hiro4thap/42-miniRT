/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:41:39 by hiono             #+#    #+#             */
/*   Updated: 2024/07/04 19:15:31 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

typedef struct s_objects
{
	t_light_ambient	*light_ambient;
	t_camera		*camera;
	t_light			*light;
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
}		t_objects;


int	read_RGB(const char *rgb, t_color *color)
{
	int	i;
	int	value;

	i = 0;
	while (i < 3)
	{
		if (*rgb == ',')
			rgb++;
		value = 0;
		while (ft_isdigit(*rgb))
		{
			value = 10 * value + *rgb - '0';
			rgb++;
		}
		if (i == 0)
			color->r = value;
		else if (i == 1)
			color->g = value;
		else if (i == 2)
			color->b = value;
		i++;
	}
	return (EXIT_SUCCESS);
}

// TODO:implement functions
int	input_light_ambient(const char *line, t_light_ambient *light_ambient);
int	input_camera(const char *line, t_camera *camera);
int	input_light(const char *line, t_light *light);
int	input_sphere(const char *line, t_sphere *sphere);
int	input_plane(const char *line, t_plane *plane);
int	input_cylinder(const char *line, t_cylinder *cylinder);

int	read_content(const char *line, t_objects *objects)
{
	if (!ft_strncmp(line, "A ", 2))
		input_light_ambient(line, objects->light_ambient);
	else if (!ft_strncmp(line, "C ", 2))
		input_camera(line, objects->camera);
	else if (!ft_strncmp(line, "L ", 2))
		input_light(line, objects->light);
	else if (!ft_strncmp(line, "sp ", 3))
		input_sphere(line, objects->sphere);
	else if (!ft_strncmp(line, "pl ", 3))
		input_plane(line, objects->plane);
	else if (!ft_strncmp(line, "cy ", 3))
		input_cylinder(line, objects->cylinder);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	read_file(char *file, t_objects *objects)
{
	int		fd;
	char	*line;

	fd = open(file);
	if (fd < 0)
	{
		printf("Failed to open file\n");
		retrun (EXIT_FAILURE);
	}
	line = get_next_line(fd);
	while (line)
	{
		read_content(line, objects);	
		free(line);
		line = get_next_line(fd);
	}
	return (EXIT_SUCCESS);
}
