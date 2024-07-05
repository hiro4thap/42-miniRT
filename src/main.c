/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/05 17:33:40 by jhughes          ###   ########.fr       */
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
t_bool	sphere_intersection(t_sphere *sphere, t_camera *camera,
	t_incident_ray *ray)
{
	double		grad;
	double		distance;
	double		alt_distance;
	t_vector	cam_sphere_dif;

	cam_sphere_dif = subtract(camera->position, sphere->position);
	grad = pow(dot(ray->ray, cam_sphere_dif), 2.0)
		- (pow(magnitude(cam_sphere_dif), 2.0)
			- pow((sphere->diameter / 2.0), 2.0));
	if (grad < 0)
		return (FALSE);
	distance = -(dot(ray->ray, cam_sphere_dif));
	alt_distance = distance + sqrt(grad);
	distance -= sqrt(grad);
	distance = min(max(distance, 0), max(alt_distance, 0));
	if (distance <= 0)
		return (FALSE);
	ray->incident_point = add(camera->position,
			scalar_product(ray->ray, distance));
	ray->surface_normal = normalise(
			vector_in_direction(sphere->position, ray->incident_point));
	return (TRUE);
}

/// @brief Provided an object, calls the appropriate intersection function and
/// returns the value. 
/// @param o An object containing a void pointer and an enum type.
/// @param camera The camera attached to the viewport.
/// @param ray The ray from the camera origin through a pixel to the object.
/// @return TRUE if ray intersects the object, with point of intersection and
/// normal set in the ray object. FALSE otherwise.
t_bool	get_intersection(t_object *o, t_camera *camera, t_incident_ray *ray)
{
	if (o->type == SPHERE)
		return (sphere_intersection((t_sphere *) o->object, camera, ray));
	return (FALSE);
}

int	main(int argc, char *argv[])
{
	t_program	program;
	t_viewport	viewport;

	(void) argc;
	(void) argv;
	viewport.window_width = 640;
	viewport.window_height = 480;
	program.mlx_pointer = mlx_init();
	program.window = mlx_new_window(program.mlx_pointer, viewport.window_width,
			viewport.window_height, "miniRT");
	program.viewport = &viewport;
	mlx_key_hook(program.window, &input, &program);
	mlx_hook(program.window, EVENT_DESTROY_NOTIFY, 0, &exit_program, &program);
	render_frame(&program);
	ft_printf("Rendered\n");
	mlx_loop(program.mlx_pointer);
	mlx_destroy_window(program.mlx_pointer, program.window);
	free(program.mlx_pointer);
	return (EXIT_SUCCESS);
}
