/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/17 17:28:59 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

#include <math.h>

/// @brief Provided an object, calls the appropriate intersection function and
/// returns the distance to the objects. 
/// @param o An object containing a void pointer and an enum type.
/// @param origin The origin of ray.
/// @param ray The ray from origin through a pixel to the object.
/// @return distance to the object if ray intersects the object,
/// with point of intersection and normal set in the ray object. -1 otherwise.
double	to_intersection(t_object *o, t_vector origin, t_vector ray)
{
	if (o->type == SPHERE)
		return (to_sphere_intersection((t_sphere *) o->object, origin, ray));
	else if (o->type == PLANE)
		return (to_plane_intersection((t_plane *) o->object, origin, ray));
	else if (o->type == CYLINDER)
		return (
			to_cylinder_intersection((t_cylinder *) o->object, origin, ray));
	return (-1);
}

t_vector	find_normal(t_object *o, t_vector incident_point, t_vector ray)
{
	if (o->type == SPHERE)
		return (sphere_normal((t_sphere *) o->object, incident_point));
	else if (o->type == PLANE)
		return (plane_normal((t_plane *) o->object, ray));
	else
		return (cylinder_normal((t_cylinder *) o->object, incident_point));
}

static int	init_program(t_program *program, char *file)
{
	int	count_objects;
	int	count_lights;

	count_objects = 0;
	count_lights = 0;
	if (validate(file, &count_objects, &count_lights))
		return (EXIT_FAILURE);
	program->lights = ft_calloc(count_lights + 1, sizeof(t_light *));
	if (!program->lights)
		return (EXIT_FAILURE);
	program->objects = ft_calloc(count_objects + 1, sizeof(t_object *));
	if (!program->objects)
	{
		free(program->lights);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_program	program;
	t_viewport	viewport;

	if (argc != 2)
	{
		ft_putendl_fd("Invalid arguments. Follow the usage", STDERR_FILENO);
		ft_putendl_fd("./miniRT [filename]", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	viewport.window_width = 640;
	viewport.window_height = 480;
	program.mlx_pointer = mlx_init();
	program.window = mlx_new_window(program.mlx_pointer, viewport.window_width,
			viewport.window_height, "miniRT");
	program.viewport = &viewport;
	mlx_key_hook(program.window, &input, &program);
	mlx_hook(program.window, EVENT_DESTROY_NOTIFY, 0, &exit_program, &program);
	if (init_program(&program, argv[1]))
		return (EXIT_FAILURE);
	read_file(argv[1], &program);
	render_frame(&program);
	ft_printf("Rendered\n");
	mlx_loop(program.mlx_pointer);
	return (EXIT_SUCCESS);
}
