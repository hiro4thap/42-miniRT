/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:50:27 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/21 22:31:22 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	*delete_objects(t_object **objects)
{
	t_object	**object;

	ft_printf("Deleting all objects...\n");
	object = objects;
	while (*object)
	{
		ft_printf("-> Deleting object of type %d... ", (*object)->type);
		free((*object)->object);
		free(*object);
		ft_printf("Done!\n");
		object += 1;
	}
	free(objects);
	ft_printf("All objects deleted!\n");
	return (NULL);
}

static t_light	**delete_lights(t_light **lights)
{
	t_light	**light;

	ft_printf("Deleting all lights...\n");
	light = lights;
	while (*light)
	{
		ft_printf("-> Light deleted.\n");
		free(*light);
		light += 1;
	}
	free(lights);
	ft_printf("All lights deleted!\n");
	return (NULL);
}

int	cleanup(t_program *program, int exit_status)
{
	ft_printf("Closing...\n");
	if (program->lights)
		program->lights = delete_lights(program->lights);
	if (program->objects)
		program->objects = delete_objects(program->objects);
	ft_printf("Destroying window... ");
	mlx_destroy_window(program->mlx_pointer, program->window);
	ft_printf("Done!\n");
	if (ON_LINUX)
	{
		ft_printf("Destroying display... ");
		mlx_destroy_display(program->mlx_pointer);
		ft_printf("Done!\n");
	}
	free(program->mlx_pointer);
	ft_printf("Succesfully closed.\n");
	exit(exit_status);
	return (exit_status);
}
