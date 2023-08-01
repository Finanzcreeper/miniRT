#include "miniRT.h"

static void	hit_cylinder_disk(t_ray *ray, t_cylinder *cy, t_data *data, int idx)
{
	const double	t3 = vec_dot(point_diff(cy->top, ray->origin),
			cy->vector) / vec_dot(ray->direction, cy->vector);
	const double	t4 = vec_dot(point_diff(cy->bottom, ray->origin),
			cy->vector) / vec_dot(ray->direction, cy->vector);
	const t_vector	v3 = point_diff(get_hitpoint(*ray, t3), cy->top);
	const t_vector	v4 = point_diff(get_hitpoint(*ray, t4), cy->bottom);

	if (vec_dot(v3, v3) <= cy->r * cy->r && t3 > 0 && t3 < ray->t_obj)
	{
		ray->t_obj = t3;
		ray->color = cy->color;
		ray->fr = cy_fr_top(get_hitpoint(*ray, ray->t_obj), *cy, data->light);
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	}
	if (vec_dot(v4, v4) <= cy->r * cy->r && t4 > 0 && t4 < ray->t_obj)
	{
		ray->t_obj = t4;
		ray->color = cy->color;
		ray->fr = cy_fr_bottom(get_hitpoint(*ray, ray->t_obj), *cy,
				data->light);
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	}
}

void	cy_quadeq(t_quadeq *eq, t_ray *ray, t_cylinder *cy, t_vector oc)
{
	eq->a = vec_dot(ray->direction, ray->direction)
		- pow(vec_dot(ray->direction, cy->vector), 2);
	eq->b = 2 * (vec_dot(ray->direction, oc) - vec_dot(ray->direction,
				cy->vector) * vec_dot(oc, cy->vector));
	eq->c = vec_dot(oc, oc) - pow(vec_dot(oc, cy->vector), 2)
		- pow(cy->r, 2);
	solve_quadeq(eq);
}

void	hit_cylinder(t_ray *ray, t_cylinder *cy, t_data *data, int idx)
{
	const t_vector	oc = point_diff(ray->origin, cy->top);
	t_vector		hit_vector;
	t_quadeq		eq;
	const double	t_temp = ray->t_obj;

	cy_quadeq(&eq, ray, cy, oc);
	if (eq.d >= 0 && eq.t1 >= 0 && eq.t2 < 0 && eq.t1 < ray->t_obj)
		ray->t_obj = eq.t1;
	else if (eq.d >= 0 && eq.t1 > eq.t2 && eq.t2 >= 0 && eq.t2 < ray->t_obj)
		ray->t_obj = eq.t2;
	else
		return ;
	hit_vector = point_diff(get_hitpoint(*ray, ray->t_obj), cy->top);
	if (vec_dot(hit_vector, cy->vector) >= 0
		&& (vec_dot(hit_vector, cy->vector) <= cy->height))
	{
		ray->color = cy->color;
		ray->fr = cy_fr_side(get_hitpoint(*ray, ray->t_obj), *cy, data->light);
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	}
	else
		ray->t_obj = t_temp;
	hit_cylinder_disk(ray, cy, data, idx);
}
