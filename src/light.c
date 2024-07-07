/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42adel.org.au>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:56:20 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/07 18:15:56 by hiono            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

/// @brief Finds diffuse light component through dot product of light ray and
/// surface normal at point of ray incidence.
/// @param ray The ray from the camera origin through a pixel to the object.
/// @param light The light point source.
/// @return The color of light set to the appropriate proption based on normal.
static t_color	get_difuse(t_incident_ray *ray, t_light *light)
{
	t_vector	light_direction;
	t_color		result;
	double		diffuse_proportion;

	light_direction = normalise(
			vector_in_direction(light->position, ray->incident_point));
	diffuse_proportion = -dot(ray->surface_normal, light_direction);
	if (diffuse_proportion < 0.0)
		diffuse_proportion = 0.0;
	result = color_proportion(light->color,
			diffuse_proportion * light->brightness);
	return (result);
}

/// @brief Finds specular light component based on how close the light
/// reflection vector is to the view (ray) vector.
/// @param ray The ray from the camera origin through a pixel to the object.
/// @param light The light point source.
/// @return The color of light set to appropriate proption based on power 16.
static t_color	get_specular(t_incident_ray *ray, t_light *light)
{
	t_vector	light_direction;
	t_vector	light_reflection;
	t_color		result;
	double		specular_proportion;

	light_direction = normalise(
			vector_in_direction(light->position, ray->incident_point));
	light_reflection = normalise(
			subtract(light_direction,
				scalar_product(ray->surface_normal,
					2.0 * dot(light_direction, ray->surface_normal))));
	specular_proportion = -dot(light_reflection, ray->ray);
	if (specular_proportion < 0)
		specular_proportion = 0;
	specular_proportion = pow(specular_proportion, 16);
	result = color_proportion(light->color,
			specular_proportion * light->brightness);
	return (result);
}

/// @brief Calculates the combined color components from ambient, diffuse,
/// and specular light source.
/// @param ray The ray from the camera origin through a pixel to the object.
/// @param light_ambient The ambient light.
/// @param light A point light source.
/// @return The combined color component.
t_color	get_light(t_incident_ray *ray,
		t_light_ambient *light_ambient, t_light **lights)
{
	t_color	ambient;
	t_color	difuse;
	t_color	specular;
	t_color	light;
	t_color	result;

	ambient = color_proportion(light_ambient->color, light_ambient->ratio);
	result = set_color(0, 0, 0);
	while (*lights)
	{
		difuse = get_difuse(ray, *lights);
		specular = set_color(0, 0, 0);
		if (SPECULAR_ON)
			specular = get_specular(ray, *lights);
		light = color_add(color_add(ambient, difuse), specular);
		result = color_add(result, light);
		lights++;
	}
	result = color_add(result, ambient);
	return (result);
}
