#include "miniRT.h"

t_point	sphere_intersection(t_ray ray, t_sphere sphere)
{
	const t_vector	oc = point_diff(ray.origin, sphere.center);
	t_quadeq		eq;

	eq.a = vec_dot(ray.direction, ray.direction);
	eq.b = 2.0 * vec_dot(oc, ray.direction);
	eq.c = vec_dot(oc, oc) - sphere.radius * sphere.radius;
	solve_quadeq(&eq);
	if (eq.discriminant < 0)
		return ((t_point) {INFINITY, INFINITY, INFINITY});
	if (eq.t1 <= eq.t2)
		return (get_hitpoint(ray, eq.t1));
	return (get_hitpoint(ray, eq.t2));
}
