#include "miniRT.h"

// t_vector	point_add(t_vector v1, t_vector v2)
// {
// 	t_vector	result;

// 	result.x = v1.x + v2.x;
// 	result.y = v1.y + v2.y;
// 	result.z = v1.z + v2.z;
// 	return (result);
// }

t_vector	point_diff(t_point v1, t_point v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

// t_vector	vec_multiply(t_vector v1, t_vector v2)
// {
// 	t_vector	result;

// 	result.x = v1.x * v2.x;
// 	result.y = v1.y * v2.y;
// 	result.z = v1.z * v2.z;
// 	return (result);
// }

// t_vector	vec_divide(t_vector v1, t_vector v2)
// {
// 	t_vector	result;

// 	result.x = v1.x / v2.x;
// 	result.y = v1.y / v2.y;
// 	result.z = v1.z / v2.z;
// 	return (result);
// }
