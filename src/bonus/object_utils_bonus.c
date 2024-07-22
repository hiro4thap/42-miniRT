/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:44:01 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:12:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/miniRT_bonus.h"

/// @brief Provided an object, calls the appropriate intersection function and
/// returns the distance to the objects. 
/// @param o An object containing a void pointer and an enum type.
/// @param origin The origin of ray.
/// @param ray The ray from origin through a pixel to the object.
/// @return distance to the object if ray intersects the object,
/// with point of intersection and normal set in the ray object. -1 otherwise.
double	to_intersection(t_object *o, t_vector origin, t_vector ray)
{
	if (o->type == SPHERE)
		return (to_sphere_intersection((t_sphere *) o->object, origin, ray));
	else if (o->type == PLANE)
		return (to_plane_intersection((t_plane *) o->object, origin, ray));
	else if (o->type == CYLINDER)
		return (
			to_cylinder_intersection((t_cylinder *) o->object, origin, ray));
	else if (o->type == CONE)
		return (to_cone_intersection((t_cone *) o->object, origin, ray));
	return (-1);
}

t_vector	find_normal(t_object *o, t_vector incident_point, t_vector ray)
{
	t_vector	normal;
	t_vector	bump_normal;

	if (o->type == SPHERE)
		normal = sphere_normal((t_sphere *) o->object, incident_point);
	else if (o->type == PLANE)
		normal = plane_normal((t_plane *) o->object, ray);
	else if (o->type == CYLINDER)
		normal = cylinder_normal((t_cylinder *) o->object, incident_point);
	else
		normal = cone_normal((t_cone *) o->object, incident_point);
	if (o->has_bump_map)
	{
		bump_normal = uv_bumpmap(uvmap(incident_point, o), &o->bump_map);
		return (bump_normal);
	}
	return (normal);
}
