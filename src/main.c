/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/03 18:03:34 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

#include <math.h>

/// @brief Checks if ray intersects with sphere, and populates ray with point
/// of intersection and surface normal if so.
/// @param sphere The sphere to test.
/// @param camera The camera attached to the viewport.
/// @param ray The ray from the camera origin through a pixel to the object.
/// @return True if ray intersects with object, False otherwise.
t_bool	sphere_intersection(t_sphere sphere, t_camera camera,
	t_incident_ray *ray)
{
	double	grad;
	double	distance;

	grad = pow(
			dot(ray->ray, subtract(camera.position, sphere.position)), 2.0)
		- (pow(magnitude(subtract(camera.position, sphere.position)), 2.0)
			- pow((sphere.diameter / 2.0), 2.0));
	if (grad < 0)
		return (FALSE);
	distance = -(dot(ray->ray, subtract(camera.position, sphere.position)))
		+ grad;
	ray->incident_point = add(camera.position,
			scalar_product(ray->ray, distance));
	ray->surface_normal = normalise(
			vector_in_direction(sphere.position, ray->incident_point));
	return (TRUE);
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
	ft_printf("Rendered\n");
	mlx_loop(program.mlx_pointer);
	mlx_destroy_window(program.mlx_pointer, program.window);
	free(program.mlx_pointer);
	return (EXIT_SUCCESS);
}
