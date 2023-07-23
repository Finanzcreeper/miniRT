#include "miniRT.h"

void	solve_quadeq(t_quadeq *eq)
{
	eq->discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
	if (eq->discriminant < 0)
		return ;
	eq->t1 = (-eq->b + sqrt(eq->discriminant)) / (2 * eq->a);
	eq->t2 = (-eq->b - sqrt(eq->discriminant)) / (2 * eq->a);
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
