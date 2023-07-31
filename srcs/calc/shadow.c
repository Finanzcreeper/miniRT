#include "miniRT.h"

bool	in_light(t_data *data, t_point hitpoint, int idx)
{
	t_vector	shadow_ray_dir;
	t_ray		shadow_ray;
	int			i;

	shadow_ray_dir = vec_normalize(point_diff(data->light.source, hitpoint));
	shadow_ray = init_shadow_ray(hitpoint, shadow_ray_dir);
	i = -1;
	while (++i < data->n_obj && i != idx)
	{
		if ((data->objs[i].type == SPHERE
			&& block_sphere(&shadow_ray, &data->objs[i].sp))
			|| (data->objs[i].type == PLANE
			&& block_plane(&shadow_ray, &data->objs[i].pl))
			|| (data->objs[i].type == CYLINDER
			&& block_cylinder(&shadow_ray, &data->objs[i].cy)))
			return (false);
	}
	return (true);
}

bool	block_sphere(t_ray *ray, t_sphere *sphere)
{
	const t_vector	oc = point_diff(ray->origin, sphere->center);
	t_quadeq		eq;

	eq.a = vec_dot(ray->direction, ray->direction);
	eq.b = 2.0 * vec_dot(oc, ray->direction);
	eq.c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	solve_quadeq(&eq);
	if (eq.discriminant < 0)
		return (false);
	if (eq.t1 < 0 && eq.t2 < 0)
		return (false);
	return (true);
}

bool	block_plane(t_ray *ray, t_plane *plane)
{
	const double	denom = vec_dot(ray->direction, plane->vector);
	const t_vector	op = point_diff(ray->origin, plane->point);
	double			t;

	if (fabs(denom) < 1e-6)
		return (false);
	t = - vec_dot(plane->vector, op) / denom;
	if (t < 0)
		return (false);
	return (true);
}


bool	block_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	const t_vector	oc = point_diff(ray->origin, cylinder->top);
	t_quadeq		eq;

	eq.a = vec_dot(ray->direction, ray->direction) -
		pow(vec_dot(ray->direction, cylinder->vector), 2);
	eq.b = 2 * (vec_dot(ray->direction, oc) - vec_dot(ray->direction,
		cylinder->vector) * vec_dot(oc, cylinder->vector));
	eq.c = vec_dot(oc, oc) - pow(vec_dot(oc, cylinder->vector), 2) -
		pow(cylinder->radius, 2);
	solve_quadeq(&eq);
	if (eq.discriminant < 0)
		return (false);
	if (eq.t1 < 0 && eq.t2 < 0)
		return (false);
	return (true);
}
