/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:41:39 by hiono             #+#    #+#             */
/*   Updated: 2024/07/05 18:01:19 by hiono            ###   ########.fr       */
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

int	read_double(const char *line, double *data)
{
	int		index;
	int		index_dot;
	double	value;
	int		sign;

	index = 0;
	value = 0;
	sign = 1;
	if (line[index] == '-')
	{
		index++;
		sign = -1;
	}
	while (ft_isdigit(line[index]))
		value = 10 * value + line[index++] - '0';
	if (line[index] == '.')
	{
		index_dot = index;
		while (ft_isdigit(line[++index]))
			value += (line[index] - '0') * pow(10, index_dot - index);
	}
	*data = sign * value;
	return (index);
}

int	read_RGB(const char *rgb, t_color *color)
{
	int		index;
	int		itr;
	double	value;

	index = 0;
	itr = 0;
	while (itr < 3)
	{
		if (rgb[index] == ',')
			index++;
		value = 0;
		index += read_double(rgb, &value);
		if (itr == 0)
			color->r = value;
		else if (itr == 1)
			color->g = value;
		else if (itr == 2)
			color->b = value;
		itr++;
	}
	return (index);
}

int	read_coordinate(const char *coordinate, t_vector *data)
{
	int	index;
	int	itr;

	index = 0;
	itr = 0;
	while (itr < 3)
	{
		if (coordinate[index] == ',')
			index++;
		if (itr == 0)
			index += read_double(&coordinate[index], &data->x);
		else if (itr == 1)
			index += read_double(&coordinate[index], &data->y);
		else if (itr == 2)
			index += read_double(&coordinate[index], &data->y);
		itr++;
	}
	return (index);
}

// TODO:implement functions
int	input_light_ambient(const char *line, t_light_ambient *light_ambient)
{
	int	index;

	index = 1;
	while (line[index] == ' ')
		index++;
	index += read_double(&line[index], &light_ambient->ratio);
	while (line[index] == ' ')
		index++;
	index += read_RGB(&line[index], &light_ambient->color);
	return (EXIT_SUCCESS);
}

int	input_camera(const char *line, t_camera *camera)
{
	int	index;

	index = 1;
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &camera->position);
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &camera->orientation);
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &camera->direction);
	return (EXIT_SUCCESS);
}

int	input_light(const char *line, t_light *light)
{
	int	index;

	index = 1;
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &light->position);
	while (line[index] == ' ')
		index++;
	index += read_double(&line[index], &light->brightness);
	return (EXIT_SUCCESS);
}

int	input_sphere(const char *line, t_sphere *sphere)
{
	int	index;

	index = 2;
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &sphere->position);
	while (line[index] == ' ')
		index++;
	index += read_double(&line[index], &sphere->diameter);
	while (line[index] == ' ')
		index++;
	index += read_RGB(&line[index], &sphere->color);
	return (EXIT_SUCCESS);
}

int	input_plane(const char *line, t_plane *plane)
{
	int	index;

	index = 2;
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &plane->position);
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &plane->normal);
	while (line[index] == ' ')
		index++;
	index += read_RGB(&line[index], &plane->color);
	return (EXIT_SUCCESS);
}

int	input_cylinder(const char *line, t_cylinder *cylinder)
{
	int	index;

	index = 2;
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &cylinder->position);
	while (line[index] == ' ')
		index++;
	index += read_coordinate(&line[index], &cylinder->rotation);
	while (line[index] == ' ')
		index++;
	index += read_double(&line[index], &cylinder->diameter);
	while (line[index] == ' ')
		index++;
	index += read_double(&line[index], &cylinder->height);
	while (line[index] == ' ')
		index++;
	index += read_RGB(&line[index], &cylinder->color);
	return (EXIT_SUCCESS);
}

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
