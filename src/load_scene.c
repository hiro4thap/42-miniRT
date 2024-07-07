/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:55:49 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/07 17:33:52 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

void	load_lights(t_program *program)
{
	t_light		**scene_lights;
	const int	num_of_lights = 3;

	program->ambient.color = set_color(255, 255, 255);
	program->ambient.ratio = 0.1;
	scene_lights = malloc(sizeof(t_light *) * (num_of_lights + 1));
	if (!scene_lights)
		return ;
	scene_lights[0] = malloc(sizeof(t_light));
	scene_lights[0]->brightness = 1.0;
	scene_lights[0]->color = set_color(255, 0, 0);
	set_vector_components(&scene_lights[0]->position, -1.732, 2.0, -1.0);
	scene_lights[1] = malloc(sizeof(t_light));
	scene_lights[1]->brightness = 1.0;
	scene_lights[1]->color = set_color(0, 255, 0);
	set_vector_components(&scene_lights[1]->position, 1.732, 2.0, -1.0);
	scene_lights[2] = malloc(sizeof(t_light));
	scene_lights[2]->brightness = 1.0;
	scene_lights[2]->color = set_color(0, 0, 255);
	set_vector_components(&scene_lights[2]->position, 0.0, 2.0, 2.0);
	scene_lights[3] = NULL;
	program->lights = scene_lights;
}

/// @brief Initialises object array.
/// @return Object array pointer.
void	get_objects(t_program *program)
{
	const int	num_of_objects = 4;
	t_object	**objects;

	objects = malloc(sizeof(t_object *) * (num_of_objects + 1));
	if (!objects)
		return ;
	objects[0] = malloc(sizeof(t_object));
	if (!objects[0])
		return ;
	objects[0]->type = SPHERE;
	objects[0]->object = malloc(sizeof(t_sphere));
	if (!objects[0]->object)
		return ;
	((t_sphere *) objects[0]->object)->color = set_color(255, 255, 255);
	((t_sphere *) objects[0]->object)->diameter = 3;
	set_vector_components(&((t_sphere *) objects[0]->object)->position,
		0.0, 6.0, 0.0);
	objects[1] = malloc(sizeof(t_object));
	if (!objects[1])
		return ;
	objects[1]->type = PLANE;
	objects[1]->object = malloc(sizeof(t_plane));
	if (!objects[1]->object)
		return ;
	((t_plane *) objects[1]->object)->color = set_color(255, 255, 255);
	set_vector_components(&((t_plane *) objects[1]->object)->normal,
		1.0, 1.0, 0.0);
	set_vector_components(&((t_plane *) objects[1]->object)->position,
		0.0, 6.0, 0.0);
	objects[2] = malloc(sizeof(t_object));
	if (!objects[2])
		return ;
	objects[2]->type = CYLINDER;
	objects[2]->object = malloc(sizeof(t_cylinder));
	if (!objects[2]->object)
		return ;
	((t_cylinder *) objects[2]->object)->color = set_color(0, 0, 255);
	((t_cylinder *) objects[2]->object)->diameter = 2;
	((t_cylinder *) objects[2]->object)->height = 4;
	set_vector_components(&((t_cylinder *) objects[2]->object)->rotation,
		0.0, 0.0, 1.0);
	set_vector_components(&((t_cylinder *) objects[2]->object)->position,
		-3.0, 5.0, 1.0);
	objects[3] = NULL;
	program->objects = objects;
}

void	init_camera(t_program *program)
{
	t_camera		*cam;
	t_vector		up;
	double			half_view_x;
	double			half_view_y;
	const double	rad_conversion = M_PI / 180.0;

	cam = &program->viewport->camera;
	cam->fov = 90.0;
	set_vector_components(&cam->position, 0.0, 0.0, 0.0);
	set_vector_components(&cam->direction, 0.0, 1.0, 0.0);
	set_vector_components(&up, 0.0, 0.0, 1.0);
	cam->direction = normalise(cam->direction);
	cam->right_axis = normalise(cross(cam->direction, up));
	cam->up_axis = normalise(cross(cam->right_axis, cam->direction));
	half_view_x = tan(cam->fov * rad_conversion / 2.0);
	half_view_y = half_view_x * ((double)(program->viewport->window_height - 1))
		/ ((double)(program->viewport->window_width - 1));
	program->viewport->pixel_dx = scalar_product(cam->right_axis,
			(2.0 * half_view_x)
			/ ((double)(program->viewport->window_width - 1)));
	program->viewport->pixel_dy = scalar_product(cam->up_axis,
			(2.0 * half_view_y)
			/ ((double)(program->viewport->window_height - 1)));
	program->viewport->pixel_start = add(subtract(cam->direction,
				scalar_product(cam->right_axis, half_view_x)),
			scalar_product(cam->up_axis, half_view_y));
}
