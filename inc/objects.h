/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:27:09 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/02 23:27:23 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "definitions.h"
# include "vector.h"
# include "color.h"

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

#endif
