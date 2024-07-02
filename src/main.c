/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/02 23:24:22 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

#include <math.h>
#include <stdio.h>

t_bool	sphere_intersection(t_sphere sphere, t_vector line)
{
	t_vector	o;
	double		grad;

	set_vector_components(&o, 0, 0, 0);
	grad = pow(dot(line, subtract(o, sphere.position)), 2.0);
	grad -= pow(magnitude(subtract(o, sphere.position)), 2.0)
		- pow((sphere.diameter / 2.0), 2.0);
	if (grad >= 0)
		return (TRUE);
	return (FALSE);
}

int	main(int argc, char *argv[])
{
	t_program	program;
	t_viewport	viewport;

	(void) argc;
	(void) argv;
	program.mlx_pointer = mlx_init();
	program.window = mlx_new_window(program.mlx_pointer, 640, 480, "miniRT");
	viewport.window_height = 480;
	viewport.window_width = 640;
	program.viewport = &viewport;
	render_frame(&program);
	mlx_loop(program.mlx_pointer);
	mlx_destroy_window(program.mlx_pointer, program.window);
	free(program.mlx_pointer);
	return (EXIT_SUCCESS);
}
