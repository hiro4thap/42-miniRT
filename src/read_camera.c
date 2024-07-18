/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 14:37:31 by hiono             #+#    #+#             */
/*   Updated: 2024/07/18 13:20:12 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

int	read_camera(const char *line, t_camera *camera, t_program *program)
{
	t_vector		up;
	int				index;
	double			half_view_x;
	double			half_view_y;

	index = ft_strlen("C");
	index += read_coordinate(&line[index], &camera->position);
	index += read_coordinate(&line[index], &camera->direction);
	index += read_double(&line[index], &camera->fov);
	set_vector_components(&up, 0.0, 0.0, 1.0);
	camera->right_axis = normalise(cross(camera->direction, up));
	camera->up_axis = normalise(cross(camera->right_axis, camera->direction));
	half_view_x = tan(camera->fov * M_PI / 180.0 / 2.0);
	half_view_y = half_view_x * ((double)(program->viewport.window_height - 1))
		/ ((double)(program->viewport.window_width - 1));
	program->viewport.pixel_dx = scalar_product(camera->right_axis,
			(2.0 * half_view_x)
			/ ((double)(program->viewport.window_width - 1)));
	program->viewport.pixel_dy = scalar_product(camera->up_axis,
			(2.0 * half_view_y)
			/ ((double)(program->viewport.window_height - 1)));
	program->viewport.pixel_start = add(subtract(camera->direction,
				scalar_product(camera->right_axis, half_view_x)),
			scalar_product(camera->up_axis, half_view_y));
	return (EXIT_SUCCESS);
}
