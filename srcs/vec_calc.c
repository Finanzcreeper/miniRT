#include "miniRT.h"

t_vector	vec_scale(t_vector v1, double scale)
{
	t_vector	result;

	result.x = v1.x * scale;
	result.y = v1.y * scale;
	result.z = v1.z * scale;
	return (result);
}

double	vec_dot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	vec_cross(t_vector v1, t_vector v2)
{
	t_vector result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
