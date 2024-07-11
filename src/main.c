/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:10 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/11 14:43:42 by hiono            ###   ########.fr       */
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

// TODO:the number of objects should taken from file
static int	init_program(t_program *program)
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
	if (init_program(&program))
		return (EXIT_FAILURE);
	render_frame(&program);
	ft_printf("Rendered\n");
	mlx_loop(program.mlx_pointer);
	mlx_destroy_window(program.mlx_pointer, program.window);
	free(program.mlx_pointer);
	return (EXIT_SUCCESS);
}
