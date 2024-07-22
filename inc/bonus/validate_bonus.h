/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 18:06:59 by hiono             #+#    #+#             */
/*   Updated: 2024/07/22 16:23:10 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_BONUS_H
# define VALIDATE_BONUS_H

typedef struct s_counts
{
	int	count_ambient_light;
	int	count_camera;
	int	count_objects;
	int	count_lights;
}	t_counts;

// validate.c
t_bool	err(char *message);
int		validate_file(char *file, t_counts *counts);

// validate_double.c
int		validate_double(const char *number);
int		validate_udouble(const char *number);
int		validate_double_value(const char *number, double min, double max);
int		validate_double_info(const char *number);
int		validate_double_value_info(const char *number, double min,
			double max);

// validate_information.c
int		validate_rgb(const char *rgb);
int		validate_coordinate(const char *coordinate);
int		validate_normalized_vector(const char *normalized_vector);
int		validate_flag(const char *flag);

// validate_light.c
t_bool	is_valid_light_ambient(const char *line);
t_bool	is_valid_light(const char *line);

// validate_camera.c
t_bool	is_valid_camera(const char *line);

// validate_objects.c
t_bool	is_valid_sphere(const char *line);
t_bool	is_valid_plane(const char *line);
t_bool	is_valid_cylinder(const char *line);
t_bool	is_valid_cone(const char *line);

#endif
