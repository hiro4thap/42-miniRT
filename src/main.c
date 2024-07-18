/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/18 13:42:59 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

#include <math.h>

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

static int	setup_window(t_program *program)
{
	program->viewport.window_width = 640;
	program->viewport.window_height = 480;
	program->mlx_pointer = mlx_init();
	program->window = mlx_new_window(program->mlx_pointer,
			program->viewport.window_width,
			program->viewport.window_height,
			"miniRT");
	mlx_key_hook(program->window, &input, program);
	mlx_hook(program->window, EVENT_DESTROY_NOTIFY, 0, &exit_program, program);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	t_program	program;

	if (argc != 2)
	{
		ft_putendl_fd("Invalid arguments. Follow the usage", STDERR_FILENO);
		ft_putendl_fd("./miniRT [filename]", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_memset(&program, 0, sizeof(t_program));
	setup_window(&program);
	if (init_program(&program, argv[1]) == EXIT_FAILURE)
		cleanup(&program, EXIT_FAILURE);
	if (read_file(argv[1], &program) == EXIT_FAILURE)
		cleanup(&program, EXIT_FAILURE);
	render_frame(&program);
	ft_printf("Rendered\n");
	mlx_loop(program.mlx_pointer);
	return (EXIT_SUCCESS);
}
