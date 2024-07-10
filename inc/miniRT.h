/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 17:23:51 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/08 16:39:56 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>

# ifndef __linux__
#  include "../lib/libmlx/mlx.h"
# else
#  include "../lib/libmlx_Linux/mlx.h"
# endif
# include "../lib/libft/inc/libft.h"

# include "definitions.h"
# include "vector.h"
# include "objects.h"
# include "color.h"
# include "read.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_viewport
{
	int			window_width;
	int			window_height;
	t_camera	camera;
	t_vector	pixel_dx;
	t_vector	pixel_dy;
	t_vector	pixel_start;
}	t_viewport;

typedef struct s_program
{
	void			*mlx_pointer;
	void			*window;
	t_viewport		*viewport;
	t_object		**objects;
	t_light			**lights;
	t_light_ambient	ambient;
}	t_program;

typedef struct s_incident_ray
{
	t_vector	ray;
	t_vector	incident_point;
	t_vector	surface_normal;
	t_color		object_color;
}	t_incident_ray;

// main.c
double		to_intersection(t_object *o, t_vector origin, t_vector ray);
t_vector	find_normal(t_object *o, t_vector incident_point, t_vector ray);

// render.c
int			render_frame(t_program *program);
void		generate_image(t_data *image, t_program *program);

// light.c
t_color		get_light(t_incident_ray *ray,
				t_light_ambient *light_ambient, t_light **lights);

// utils.c
void		set_pixel(t_data *data, int x, int y, t_color color);
double		max(double a, double b);
double		min(double a, double b);

// hooks.c
int			input(int key, t_program *program);
int			exit_program(t_program *program);

t_color		*get_color(t_object *object);

// load_scene.c
void		load_lights(t_program *program);
void		get_objects(t_program *program);
void		init_camera(t_program *program);

#endif
