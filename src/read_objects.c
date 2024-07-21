/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:32:17 by hiono             #+#    #+#             */
/*   Updated: 2024/07/21 14:56:00 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	read_sphere(const char *line, t_object **objects, int object_index)
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

int	read_plane(const char *line, t_object **objects, int object_index)
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
	index += read_coordinate(&line[index],
			&((t_plane *) objects[object_index]->object)->position);
	index += read_coordinate(&line[index],
			&((t_plane *) objects[object_index]->object)->normal);
	index += read_rgb(&line[index],
			&((t_plane *) objects[object_index]->object)->color);
	return (EXIT_SUCCESS);
}

int	read_cylinder(const char *line, t_object **objects, int object_index)
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
	index += read_coordinate(&line[index],
			&((t_cylinder *) objects[object_index]->object)->position);
	index += read_coordinate(&line[index],
			&((t_cylinder *) objects[object_index]->object)->rotation);
	index += read_double(&line[index],
			&((t_cylinder *) objects[object_index]->object)->diameter);
	index += read_double(&line[index],
			&((t_cylinder *) objects[object_index]->object)->height);
	index += read_rgb(&line[index],
			&((t_cylinder *) objects[object_index]->object)->color);
	return (EXIT_SUCCESS);
}

int	read_cone(const char *line, t_object **objects, int object_index)
{
	int	index;

	objects[object_index] = malloc(sizeof(t_object));
	if (!objects[object_index])
		return (EXIT_FAILURE);
	objects[object_index]->type = CONE;
	objects[object_index]->object = malloc(sizeof(t_cone));
	if (!objects[object_index])
		return (EXIT_FAILURE);
	index = ft_strlen("cn");
	index += read_coordinate(&line[index],
			&((t_cone *) objects[object_index]->object)->position);
	index += read_coordinate(&line[index],
			&((t_cone *) objects[object_index]->object)->axis);
	index += read_double(&line[index],
			&((t_cone *) objects[object_index]->object)->diameter);
	index += read_double(&line[index],
			&((t_cone *) objects[object_index]->object)->height);
	index += read_rgb(&line[index],
			&((t_cone *) objects[object_index]->object)->color);
	return (EXIT_SUCCESS);
}
