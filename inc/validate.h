/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hiono <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:06:59 by hiono             #+#    #+#             */
/*   Updated: 2024/07/17 15:25:45 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_H
# define VALIDATE_H

// validate.c
t_bool	err(char *message);
int		validate(char *file, int *count_objects, int *count_lights);

// validate_information.c
int		validate_double(const char *number);
int		validate_udouble(const char *number);
int		validate_double_value(const char *number, double min, double max);
int		validate_rgb(const char *rgb);
int		validate_coordinate(const char *coordinate);
int		validate_normalized_vector(const char *normalized_vector);

// validate_light.c
t_bool	is_valid_light_ambient(const char *line);
t_bool	is_valid_light(const char *line);

// validate_camera.c
t_bool	is_valid_camera(const char *line);

// validate_objects.c
t_bool	is_valid_sphere(const char *line);
t_bool	is_valid_plane(const char *line);
t_bool	is_valid_cylinder(const char *line);

#endif
