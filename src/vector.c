
#include "../inc/vector.h"

void set_vector(t_vector *vector, t_vector const ref)
{
	vector->x = ref.x;
	vector->y = ref.y;
	vector->z = ref.z;
}

void	set_vector_components(t_vector *vector, double x, double y, double z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

/// @brief This may need an error tolerance.
/// @param a 
/// @param b 
/// @return 
t_bool	equal(t_vector a, t_vector b)
{
	if ((a.x == b.x)
		&& (a.y == b.y)
		&& (a.z == b.z))
		return (TRUE);
	return (FALSE);
}

t_vector	normalise(t_vector a)
{
	const double	norm = magnitude(a);
	t_vector		result;

	set_vector_components(&result, a.x / norm, a.y / norm, a.z / norm);
	return (result);
}

t_vector	scalar_product(t_vector a, double n)
{
	t_vector	result;

	result.x = a.x * n;
	result.y = a.y * n;
	result.z = a.z * n;
	return (result);
}

t_vector	add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector	subtract(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vector    cross(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result);
}

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x
			+ a.y * b.y
			+ a.z * b.z);
}

double	magnitude(t_vector a)
{
	return (sqrt(dot(a, a)));
}

double	angle_between(t_vector a, t_vector b)
{
	return (acos(dot(a,b)/(magnitude(a) * magnitude(b))));
}

#include <stdio.h>
void		print_vector(t_vector a)
{
	printf("(%lf, %lf, %lf)", a.x, a.y, a.z);
}
