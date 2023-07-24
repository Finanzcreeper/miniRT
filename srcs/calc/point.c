#include "miniRT.h"

// t_vector	point_add(t_vector v1, t_vector v2)
// {
// 	t_vector	result;

// 	result.x = v1.x + v2.x;
// 	result.y = v1.y + v2.y;
// 	result.z = v1.z + v2.z;
// 	return (result);
// }

t_vector	point_diff(t_point p1, t_point p2)
{
	t_vector	result;

	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	result.z = p1.z - p2.z;
	return (result);
}

t_point	get_hitpoint(t_ray ray, double t)
{
	t_point	hitpoint;

	hitpoint.x = ray.origin.x + t * ray.direction.x;
	hitpoint.y = ray.origin.y + t * ray.direction.y;
	hitpoint.z = ray.origin.z + t * ray.direction.z;
	return (hitpoint);
}

bool	hit_nothing(t_point point)
{
	return (point.x == INFINITY && point.y == INFINITY && point.z == INFINITY);
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
