#include "miniRT.h"

double	vec_len(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/* Calculate the dot product of two vectors. */
double	vec_dot(t_vec v1, t_vec v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/* Calculate the cross product of two vectors. */
t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}

/* Normalize a vector. */
t_vec	vec_normalize(t_vec v)
{
	const double	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vec			result;

	result.x = v.x / mag;
	result.y = v.y / mag;
	result.z = v.z / mag;
	return (result);
}

t_vec	vec_negate(t_vec v)
{
	t_vec	result;

	result.x = -v.x;
	result.y = -v.y;
	result.z = -v.z;
	return (result);
}
