/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:26:24 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/miniRT_bonus.h"

#include <math.h>

static int	init_program(t_program *program, char *file)
{
	t_counts	counts;

	counts.count_ambient_light = 0;
	counts.count_camera = 0;
	counts.count_objects = 0;
	counts.count_lights = 0;
	if (validate_file(file, &counts))
		return (EXIT_FAILURE);
	program->lights = ft_calloc(counts.count_lights + 1, sizeof(t_light *));
	if (!program->lights)
		return (EXIT_FAILURE);
	program->objects = ft_calloc(counts.count_objects + 1, sizeof(t_object *));
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

static int	load_images(t_program *program)
{
	t_object	**objects;
	int			o;
	t_texture	*image;

	o = 0;
	objects = program->objects;
	while (objects[o] != NULL)
	{
		if (objects[o]->has_bump_map)
		{
			image = &objects[o]->bump_map;
			image->texture = mlx_xpm_file_to_image(
					program->mlx_pointer, "img/heightmap.xpm",
					&image->width, &image->height);
			if (image->texture == NULL)
				return (EXIT_FAILURE);
			image->texture->addr = mlx_get_data_addr(
					image->texture,
					&image->texture->bits_per_pixel,
					&image->texture->line_length,
					&image->texture->endian);
		}
		o += 1;
	}
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
	if (load_images(&program) == EXIT_FAILURE)
	{
		ft_printf("Image Load Failed.\n");
		cleanup(&program, EXIT_FAILURE);
	}
	render_frame(&program);
	ft_printf("Rendered\n");
	mlx_loop(program.mlx_pointer);
	return (EXIT_SUCCESS);
}
