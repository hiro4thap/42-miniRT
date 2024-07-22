/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:27:09 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 11:23:30 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "definitions.h"
# include "vector.h"
# include "color.h"

typedef struct s_data	t_data;

enum e_objects
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
};

enum e_material
{
	TEX_COLOR,
	TEX_CHECKERBOARD
};

typedef struct s_texture
{
	t_data	*texture;
	int		width;
	int		height;
}	t_texture;

typedef struct s_object
{
	enum e_objects	type;
	void			*object;
	int				has_bump_map;
	t_texture		bump_map;
	enum e_material	material_type;
}	t_object;

typedef struct s_light_ambient
{
	double	ratio;
	t_color	color;
}	t_light_ambient;

typedef struct s_camera
{
	t_vector	position;
	t_vector	direction;
	t_vector	up_axis;
	t_vector	right_axis;
	double		fov;
}	t_camera;

typedef struct s_light
{
	t_vector	position;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	t_vector	position;
	double		diameter;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_vector	position;
	t_vector	normal;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vector	position;
	t_vector	rotation;
	double		diameter;
	double		height;
	t_color		color;
}	t_cylinder;

typedef struct s_cone
{
	t_vector	position;
	t_vector	axis;
	double		diameter;
	double		height;
	t_color		color;
}	t_cone;

// sphere.c
double		to_sphere_intersection(t_sphere *sphere, t_vector origin,
				t_vector line);
t_vector	sphere_normal(t_sphere *sphere, t_vector incident_point);

// plane.c
double		to_plane_intersection(t_plane *plane, t_vector origin,
				t_vector line);
t_vector	plane_normal(t_plane *plane, t_vector ray);

// cylinder.c
double		to_cylinder_intersection(t_cylinder *cylinder, t_vector origin,
				t_vector line);
t_vector	cylinder_normal(t_cylinder *cylinder, t_vector incident_point);

// cylinder_utils.c
double		to_cy_front_seam_intersection(t_cylinder *cylinder, t_vector origin,
				t_vector line, double grad);
double		to_cy_rear_seam_intersection(t_cylinder *cylinder, t_vector origin,
				t_vector line, double grad);
double		to_cy_top_cap_intersection(t_cylinder *cylinder, t_vector origin,
				t_vector line);
double		to_cy_buttom_cap_intersection(t_cylinder *cylinder, t_vector origin,
				t_vector line);

// cone.c
double		to_cone_intersection(t_cone *cone, t_vector origin, t_vector line);
t_vector	cone_normal(t_cone *cone, t_vector incident_point);

// cone_utils.c
double		find_grad(t_cone *cone, t_vector origin, double a, double b);
double		find_height(t_cone *cone, t_vector origin, t_vector line,
				double distance);
double		to_cn_top_cap_intersection(t_cone *cone, t_vector origin,
				t_vector line);
double		to_cn_buttom_cap_intersection(t_cone *cone, t_vector origin,
				t_vector line);
#endif
