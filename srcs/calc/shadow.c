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
		if ((data->objects[i].type == SPHERE
			&& block_sphere(&shadow_ray, &data->objects[i].sphere))
			|| (data->objects[i].type == PLANE
			&& block_plane(&shadow_ray, &data->objects[i].plane)))
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
	return (true);
}

bool	block_plane(t_ray *ray, t_plane *plane)
{
	(void)ray;
	(void)plane;
	return (true);
}
