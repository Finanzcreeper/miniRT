#include "miniRT.h"

void	solve_quadeq(t_quadeq *eq)
{
	eq->tmin = INFINITY;
	eq->d = eq->b * eq->b - 4 * eq->a * eq->c;
	if (eq->d < 0)
		return ;
	eq->t1 = (-eq->b + sqrt(eq->d)) / (2 * eq->a);
	eq->t2 = (-eq->b - sqrt(eq->d)) / (2 * eq->a);
	if (eq->t1 >= 0 && eq->t2 >= 0)
		eq->tmin = fmin(eq->t1, eq->t2);
	else if (eq->t1 >= 0 && eq->t2 < 0)
		eq->tmin = eq->t1;
}

t_vec	point_diff(t_point p1, t_point p2)
{
	t_vec	result;

	result.x = p1.x - p2.x;
	result.y = p1.y - p2.y;
	result.z = p1.z - p2.z;
	return (result);
}

t_vec	vec_diff(t_vec v1, t_vec v2)
{
	t_vec	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
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

uint32_t	bg_color(void)
{
	return (BG_R << 24 | BG_G << 16 | BG_B << 8 | BG_A);
}
