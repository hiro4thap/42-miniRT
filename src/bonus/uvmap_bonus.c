/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uvmap_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhughes <jhughes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 19:05:29 by jhughes           #+#    #+#             */
/*   Updated: 2024/07/22 16:12:29 by jhughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/uvmap_bonus.h"

static t_uvpoint	uvmap_cylinder(t_vector coordinates, t_cylinder *cylinder)
{
	t_uvpoint	result;
	t_vector	distance;
	t_vector	object_right;
	t_vector	reference;

	reference = vector_init(0, 1, 0);
	if (equal(reference, cylinder->rotation)
		|| equal(scalar_product(reference, -1), cylinder->rotation))
		object_right = vector_init(1, 0, 0);
	else
		object_right = cross(reference, cylinder->rotation);
	result.basis = mat3_init_col(
			object_right,
			cross(cylinder->rotation, object_right),
			cylinder->rotation);
	coordinates = mat3_vector_multiply(result.basis, coordinates);
	distance = subtract(coordinates,
			mat3_vector_multiply(result.basis, cylinder->position));
	result.u = 0.5 + (atan2(distance.y, distance.x)) / (2.0 * M_PI);
	result.v = 0.5 + (distance.z) / cylinder->height;
	return (result);
}

static t_uvpoint	uvmap_cone(t_vector coordinates, t_cone *cone)
{
	t_uvpoint	result;
	t_vector	distance;
	t_vector	object_right;
	t_vector	reference;

	reference = vector_init(0, 1, 0);
	if (equal(reference, cone->axis)
		|| equal(scalar_product(reference, -1), cone->axis))
		object_right = vector_init(1, 0, 0);
	else
		object_right = cross(reference, cone->axis);
	result.basis = mat3_init_col(
			object_right,
			cross(cone->axis, object_right),
			cone->axis);
	coordinates = mat3_vector_multiply(result.basis, coordinates);
	distance = subtract(coordinates,
			mat3_vector_multiply(result.basis, cone->position));
	result.u = 0.5 + (atan2(distance.y, distance.x)) / (2.0 * M_PI);
	result.v = 0.5 + (distance.z) / cone->height;
	return (result);
}

static t_uvpoint	uvmap_plane(t_vector coordinates, t_plane *plane)
{
	t_uvpoint	result;
	t_vector	distance;
	t_vector	object_right;
	t_vector	reference;

	reference = vector_init(0, 1, 0);
	if (equal(reference, plane->normal)
		|| equal(scalar_product(reference, -1), plane->normal))
		object_right = vector_init(1, 0, 0);
	else
		object_right = cross(reference, plane->normal);
	result.basis = mat3_init_col(
			object_right,
			cross(plane->normal, object_right),
			plane->normal);
	coordinates = mat3_vector_multiply(result.basis, coordinates);
	distance = subtract(coordinates,
			mat3_vector_multiply(result.basis, plane->position));
	result.u = 0.5 + fmod(distance.x, 10) / 20.0;
	result.v = 0.5 + fmod(distance.y, 10) / 20.0;
	return (result);
}

static t_uvpoint	uvmap_sphere(t_vector coordinates, t_sphere *sphere)
{
	t_uvpoint	result;
	t_vector	distance;

	result.basis = mat3_identity();
	distance = normalise(vector_in_direction(sphere->position, coordinates));
	result.u = 0.5 + (atan2(distance.y, distance.x)) / (2.0 * M_PI);
	result.v = 0.5 + (asin(distance.z)) / (M_PI);
	return (result);
}

/// @brief Maps from World Space (x,y,z) to Tangent Space (u, v),
/// where u, v in [0, 1].
/// @param coordinates 
/// @param object 
/// @return 
t_uvpoint	uvmap(t_vector coordinates, t_object *object)
{
	t_uvpoint	result;

	if (object->type == SPHERE)
		return (uvmap_sphere(coordinates, object->object));
	else if (object->type == CYLINDER)
		return (uvmap_cylinder(coordinates, object->object));
	else if (object->type == PLANE)
		return (uvmap_plane(coordinates, object->object));
	else if (object->type == CONE)
		return (uvmap_cone(coordinates, object->object));
	else
	{
		result.u = -1;
		result.v = -1;
	}
	return (result);
}
