/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:23:51 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 09:39:42 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include <stdio.h>

# ifndef __linux__
#  include "../lib/libmlx/mlx.h"
# else
#  include "../lib/libmlx_Linux/mlx.h"
# endif
# include "../lib/libft/inc/libft.h"

# include "mlx_helpers.h"
# include "definitions.h"
# include "vector.h"
# include "objects.h"
# include "color.h"
# include "read.h"
# include "validate.h"
# include "uvmap.h"
# include "matrix.h"

typedef struct s_incident_ray
{
	t_vector	ray;
	t_vector	incident_point;
	t_vector	surface_normal;
	t_color		object_color;
}	t_incident_ray;

// object_utils.c
double		to_intersection(t_object *o, t_vector origin, t_vector ray);
t_vector	find_normal(t_object *o, t_vector incident_point, t_vector ray);

// render.c
int			render_frame(t_program *program);

// light.c
t_color		get_light(t_incident_ray *ray,
				t_light_ambient *light_ambient, t_light **lights,
				t_object **objects);

// utils.c
void		set_pixel(t_data *data, int x, int y, t_color color);
double		max(double a, double b);
double		min(double a, double b);

// hooks.c
int			input(int key, t_program *program);
int			exit_program(t_program *program);

// cleanup.c
int			cleanup(t_program *program, int exit_status);

#endif
