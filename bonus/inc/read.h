/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:40:00 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 13:55:17 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_H
# define READ_H

# include <fcntl.h>
# include "miniRT.h"

typedef struct s_program	t_program;

// read_file.c
int	read_file(char *file, t_program *program);

// read_information.c
int	read_double(const char *number, double *data);
int	read_rgb(const char *rgb, t_color *data);
int	read_coordinate(const char *coordinate, t_vector *data);
int	read_material_type(const char *flag, enum e_material *data);
int	read_flag(const char *flag, int *data);

// read_objects.c
int	read_sphere(const char *line, t_object **objects, int object_index);
int	read_plane(const char *line, t_object **objects, int object_index);
int	read_cylinder(const char *line, t_object **objects, int object_index);
int	read_cone(const char *line, t_object **objects, int object_index);

// read_camera.c
int	read_camera(const char *line, t_camera *camera, t_program *program);

// read_lights.c
int	read_light_ambient(const char *line, t_light_ambient *light_ambient);
int	read_light(const char *line, t_light **lights, int light_index);

#endif
