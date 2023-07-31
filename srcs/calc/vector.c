#include "miniRT.h"

/* Scale a vector. */
t_vector	vec_scale(t_vector v1, double scale)
{
	t_vector	result;

	result.x = v1.x * scale;
	result.y = v1.y * scale;
	result.z = v1.z * scale;
	return (result);
}

/* Calculate the dot product of two vectors. */
double	vec_dot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/* Calculate the cross product of two vectors. */
t_vector	vec_cross(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

/* Normalize a vector. */
t_vector	vec_normalize(t_vector v)
{
	const double	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vector		result;

	result.x = v.x / mag;
	result.y = v.y / mag;
	result.z = v.z / mag;
	return (result);
}

t_vector	vec_negate(t_vector v)
{
	t_vector result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}
