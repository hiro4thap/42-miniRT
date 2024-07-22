/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:56:20 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:46:28 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static t_bool	is_lit(const t_incident_ray *ray, const t_light *light,
		t_object **objects)
{
	double		to_light;
	double		to_object;
	int			index;

	to_light = magnitude(vector_in_direction(light->position,
				ray->incident_point));
	index = 0;
	while (objects[index])
	{
		to_object = to_intersection(objects[index],
				ray->incident_point,
				vector_in_direction(ray->incident_point, light->position));
		if (1e-10 < to_object && to_object < to_light)
			return (FALSE);
		index++;
	}
	return (TRUE);
}

/// @brief Finds diffuse light component through dot product of light ray and
/// surface normal at point of ray incidence.
/// @param ray The ray from the camera origin through a pixel to the object.
/// @param light The light point source.
/// @return The color of light set to the appropriate proption based on normal.
static t_color	get_difuse(t_incident_ray *ray, t_light *light,
		t_object **objects)
{
	t_vector	light_direction;
	t_color		result;
	double		diffuse_proportion;

	light_direction = normalise(
			vector_in_direction(light->position, ray->incident_point));
	diffuse_proportion = -dot(ray->surface_normal, light_direction);
	if (diffuse_proportion < 0.0 || !is_lit(ray, light, objects))
		diffuse_proportion = 0.0;
	result = color_proportion(light->color,
			diffuse_proportion * light->brightness);
	return (result);
}

/// @brief Calculates the combined color components from ambient, diffuse,
/// light source.
/// @param ray The ray from the camera origin through a pixel to the object.
/// @param light_ambient The ambient light.
/// @param light A point light source.
/// @return The combined color component.
t_color	get_light(t_incident_ray *ray,
		t_light_ambient *light_ambient, t_light **lights, t_object **objects)
{
	t_color	ambient;
	t_color	difuse;
	t_color	light;
	t_color	result;

	ambient = color_proportion(light_ambient->color, light_ambient->ratio);
	result = set_color(0, 0, 0);
	while (*lights)
	{
		difuse = get_difuse(ray, *lights, objects);
		light = color_add(ambient, difuse);
		result = color_add(result, light);
		lights++;
	}
	result = color_add(result, ambient);
	return (result);
}
