


#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

# include "definitions.h"

typedef struct s_vector
{
	double x;
	double y;
	double z;
}	t_vector;

void		set_vector(t_vector *vector, t_vector const ref);
void		set_vector_components(t_vector *vector, double x, double y, double z);
t_bool		equal(t_vector a, t_vector b);
t_vector	normalise(t_vector a);

t_vector	scalar_product(t_vector a, double n);
t_vector	add(t_vector a, t_vector b);
t_vector	subtract(t_vector a, t_vector b);

t_vector	cross(t_vector a, t_vector b);
double		dot(t_vector a, t_vector b);
double		magnitude(t_vector a);
double		angle_between(t_vector a, t_vector b);

void		print_vector(t_vector a);

#endif