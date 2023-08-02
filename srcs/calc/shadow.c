#include "miniRT.h"

static bool	block_sphere(t_ray *ray, t_sphere *sphere, t_data *data)
{
	const t_light	light = data->light;
	const t_vec		oc = point_diff(ray->origin, sphere->center);
	const double	t_light = vec_len(point_diff(ray->origin, light.source));
	t_quadeq		eq;

	eq.a = vec_dot(ray->direction, ray->direction);
	eq.b = 2.0 * vec_dot(oc, ray->direction);
	eq.c = vec_dot(oc, oc) - sphere->r * sphere->r;
	solve_quadeq(&eq);
	if (eq.d < 0)
		return (false);
	if (eq.t1 - CORRECT_F < 0 && eq.t2 - CORRECT_F < 0)
		return (false);
	if (eq.t1 - CORRECT_F >= t_light && eq.t2 - CORRECT_F >= t_light)
		return (false);
	return (true);
}

static bool	block_plane(t_ray *ray, t_plane *plane, t_data *data)
{
	const t_light	light = data->light;
	const double	denom = vec_dot(ray->direction, plane->vector);
	const double	t_light = vec_len(point_diff(ray->origin, light.source));
	const t_vec		op = point_diff(ray->origin, plane->point);
	double			t;

	if (fabs(denom) < 1e-6)
		return (false);
	t = -vec_dot(plane->vector, op) / denom;
	if (t - CORRECT_F < 0)
		return (false);
	if (t - CORRECT_F >= t_light)
		return (false);
	return (true);
}

static bool	block_cy_disk(t_ray *ray, t_cylinder *cy, t_data *data)
{
	const double	tl = vec_len(point_diff(ray->origin, data->light.source));
	const double	t3 = vec_dot(point_diff(cy->top, ray->origin),
			cy->vector) / vec_dot(ray->direction, cy->vector);
	const double	t4 = vec_dot(point_diff(cy->bottom, ray->origin),
			cy->vector) / vec_dot(ray->direction, cy->vector);
	const t_vec		v3 = point_diff(get_hitpoint(*ray, t3), cy->top);
	const t_vec		v4 = point_diff(get_hitpoint(*ray, t4), cy->bottom);

	if (vec_dot(v3, v3) <= cy->r * cy->r && t3 - CORRECT_F > 0
		&& t3 - CORRECT_F < tl)
		return (true);
	if (vec_dot(v4, v4) <= cy->r * cy->r && t4 - CORRECT_F > 0
		&& t4 - CORRECT_F < tl)
		return (true);
	return (false);
}

static bool	block_cylinder(t_ray *ray, t_cylinder *cy, t_data *data)
{
	const t_vec		oc = point_diff(ray->origin, cy->top);
	const double	tl = vec_len(point_diff(ray->origin, data->light.source));
	t_quadeq		eq;
	t_vec			hit_vec;

	cy_quadeq(&eq, ray, cy, oc);
	if (eq.d < 0)
		return (false);
	if (eq.t1 - CORRECT_F < 0 && eq.t2 - CORRECT_F < 0)
		return (false);
	if (eq.t1 - CORRECT_F >= tl && eq.t2 - CORRECT_F >= tl)
		return (false);
	hit_vec = point_diff(get_hitpoint(*ray, eq.tmin - CORRECT_F), cy->top);
	if (vec_dot(hit_vec, cy->vector) - CORRECT_F > 0
		&& (vec_dot(hit_vec, cy->vector) - CORRECT_F <= cy->height))
		return (true);
	return (false);
}

bool	in_light(t_data *data, t_point hp)
{
	const t_vec	sray_dir = vec_normalize(point_diff(data->light.source, hp));
	t_ray		shadow_ray;
	int			i;

	shadow_ray = init_shadow_ray(hp, sray_dir);
	i = -1;
	while (++i < data->n_obj)
	{
		if ((data->objs[i].type == SPHERE
				&& block_sphere(&shadow_ray, &data->objs[i].sp, data))
			|| (data->objs[i].type == PLANE
				&& block_plane(&shadow_ray, &data->objs[i].pl, data))
			|| (data->objs[i].type == CYLINDER
				&& block_cylinder(&shadow_ray, &data->objs[i].cy, data))
			|| (data->objs[i].type == CYLINDER
				&& block_cy_disk(&shadow_ray, &data->objs[i].cy, data)))
			return (false);
	}
	return (true);
}
