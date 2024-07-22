/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_lights_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:38:26 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 16:12:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/miniRT_bonus.h"

int	read_light_ambient(const char *line, t_light_ambient *light_ambient)
{
	int	index;

	index = ft_strlen("A");
	index += read_double(&line[index], &light_ambient->ratio);
	index += read_rgb(&line[index], &light_ambient->color);
	return (EXIT_SUCCESS);
}

int	read_light(const char *line, t_light **lights, int light_index)
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
	index += read_rgb(&line[index], &light->color);
	return (EXIT_SUCCESS);
}
