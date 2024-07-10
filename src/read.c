/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:41:39 by hiono             #+#    #+#             */
/*   Updated: 2024/07/10 17:27:59 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	read_double(const char *line, double *data)
{
	int		index;
	int		index_dot;
	double	value;
	int		sign;

	index = 0;
	value = 0;
	sign = 1;
	while (line[index] == ' ')
		index++;
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

int	read_rgb(const char *rgb, t_color *color)
{
	int		index;
	int		itr;
	double	value;

	index = 0;
	itr = 0;
	while (rgb[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (rgb[index] == ',')
			index++;
		value = 0;
		index += read_double(&rgb[index], &value);
		if (itr == 0)
			color->r = (double) value / 255.0;
		else if (itr == 1)
			color->g = (double) value / 255.0;
		else if (itr == 2)
			color->b = (double) value / 255.0;
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
	while (coordinate[index] == ' ')
		index++;
	while (itr < 3)
	{
		if (coordinate[index] == ',')
			index++;
		if (itr == 0)
			index += read_double(&coordinate[index], &data->x);
		else if (itr == 1)
			index += read_double(&coordinate[index], &data->y);
		else if (itr == 2)
			index += read_double(&coordinate[index], &data->z);
		itr++;
	}
	return (index);
}

int	input_light_ambient(const char *line, t_light_ambient *light_ambient)
{
	int	index;

	index = ft_strlen("A");
	index += read_double(&line[index], &light_ambient->ratio);
	index += read_rgb(&line[index], &light_ambient->color);
	return (EXIT_SUCCESS);
}

int	input_camera(const char *line, t_camera *camera, t_program *program)
{
	t_vector		up;
	int				index;
	double			half_view_x;
	double			half_view_y;

	index = ft_strlen("C");
	index += read_coordinate(&line[index], &camera->position);
	index += read_coordinate(&line[index], &camera->direction);
	index += read_double(&line[index], &camera->fov);
	set_vector_components(&up, 0.0, 0.0, 1.0);
	camera->right_axis = normalise(cross(camera->direction, up));
	camera->up_axis = normalise(cross(camera->right_axis, camera->direction));
	half_view_x = tan(camera->fov * M_PI / 180.0 / 2.0);
	half_view_y = half_view_x * ((double)(program->viewport->window_height - 1))
		/ ((double)(program->viewport->window_width - 1));
	program->viewport->pixel_dx = scalar_product(camera->right_axis,
			(2.0 * half_view_x)
			/ ((double)(program->viewport->window_width - 1)));
	program->viewport->pixel_dy = scalar_product(camera->up_axis,
			(2.0 * half_view_y)
			/ ((double)(program->viewport->window_height - 1)));
	program->viewport->pixel_start = add(subtract(camera->direction,
				scalar_product(camera->right_axis, half_view_x)),
			scalar_product(camera->up_axis, half_view_y));
	return (EXIT_SUCCESS);
}

int	input_light(const char *line, t_light **lights, int light_index)
{
	t_light	*light;
	int		index;

	lights[light_index] = malloc(sizeof(t_light));
	light = lights[light_index];
	if (!light)
		return (EXIT_FAILURE);
	index = ft_strlen("L");
	index += read_coordinate(&line[index], &light->position);
	index += read_double(&line[index], &light->brightness);
	light->color = set_color(255, 255, 255);
	return (EXIT_SUCCESS);
}

int	input_sphere(const char *line, t_object **objects, int object_index)
{
	int			index;

	objects[object_index] = malloc(sizeof(t_object));
	if (!objects[object_index])
		return (EXIT_FAILURE);
	objects[object_index]->type = SPHERE;
	objects[object_index]->object = malloc(sizeof(t_sphere));
	if (!objects[object_index]->object)
		return (EXIT_FAILURE);
	index = ft_strlen("sp");
	index += read_coordinate(&line[index],
			&((t_sphere *) objects[object_index]->object)->position);
	index += read_double(&line[index],
			&((t_sphere *) objects[object_index]->object)->diameter);
	index += read_rgb(&line[index],
			&((t_sphere *) objects[object_index]->object)->color);
	return (EXIT_SUCCESS);
}

int	input_plane(const char *line, t_object **objects, int object_index)
{
	int	index;

	objects[object_index] = malloc(sizeof(t_object));
	if (!objects[object_index])
		return (EXIT_FAILURE);
	objects[object_index]->type = PLANE;
	objects[object_index]->object = malloc(sizeof(t_plane));
	if (!objects[object_index]->object)
		return (EXIT_FAILURE);
	index = ft_strlen("pl");
	index += read_coordinate(&line[index], &((t_plane *) objects[object_index]->object)->position);
	index += read_coordinate(&line[index], &((t_plane *) objects[object_index]->object)->normal);
	index += read_rgb(&line[index], &((t_plane *) objects[object_index]->object)->color);
	return (EXIT_SUCCESS);
}

int	input_cylinder(const char *line, t_object **objects, int object_index)
{
	int	index;

	objects[object_index] = malloc(sizeof(t_object));
	if (!objects[object_index])
		return (EXIT_FAILURE);
	objects[object_index]->type = CYLINDER;
	objects[object_index]->object = malloc(sizeof(t_cylinder));
	if (!objects[object_index]->object)
		return (EXIT_FAILURE);
	index = ft_strlen("cy");
	index += read_coordinate(&line[index], &((t_cylinder *) objects[object_index]->object)->position);
	index += read_coordinate(&line[index], &((t_cylinder *) objects[object_index]->object)->rotation);
	index += read_double(&line[index], &((t_cylinder *) objects[object_index]->object)->diameter);
	index += read_double(&line[index], &((t_cylinder *) objects[object_index]->object)->height);
	index += read_rgb(&line[index], &((t_cylinder *) objects[object_index]->object)->color);
	return (EXIT_SUCCESS);
}

int	read_content(const char *line, t_program *program, int *object_index, int *light_index)
{
	if (!ft_strncmp(line, "A ", 2))
		return (input_light_ambient(line, &program->ambient));
	else if (!ft_strncmp(line, "C ", 2))
		return (input_camera(line, &program->viewport->camera, program));
	else if (!ft_strncmp(line, "L ", 2))
		return (input_light(line, program->lights, (*light_index)++));
	else if (!ft_strncmp(line, "sp ", 3))
		return (input_sphere(line, program->objects, (*object_index)++));
	else if (!ft_strncmp(line, "pl ", 3))
		return (input_plane(line, program->objects, (*object_index)++));
	else if (!ft_strncmp(line, "cy ", 3))
		return (input_cylinder(line, program->objects, (*object_index)++));
	return (EXIT_FAILURE);
}

// TODO:the number of objects should taken from file
int	init_program(t_program *program)
{
	program->lights = ft_calloc(5, sizeof(t_light *));
	if (!program->lights)
		return (EXIT_FAILURE);
	program->objects = ft_calloc(5, sizeof(t_object *));
	if (!program->objects)
	{
		free(program->lights);
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

	object_index = 0;
	light_index = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Failed to open file", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	// TODO:validate and get number of objects
	if (init_program(program))
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line)
	{
		read_content(line, program, &object_index, &light_index);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (EXIT_SUCCESS);
}
