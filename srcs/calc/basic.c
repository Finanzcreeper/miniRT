#include "miniRT.h"

void	solve_quadeq(t_quadeq *eq)
{
	eq->discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
	if (eq->discriminant < 0)
		return ;
	eq->t1 = (-eq->b + sqrt(eq->discriminant)) / (2 * eq->a);
	eq->t2 = (-eq->b - sqrt(eq->discriminant)) / (2 * eq->a);
	eq->tmin = fmin(eq->t1, eq->t2);
}

t_vector	vec_subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}
