#include "miniRT.h"

/**
 * Check if the primary ray hits the given sphere.
 * It will update the color of the ray only if the hit distance is smaller
 * than the recorded one.
 */
void	hit_sphere(t_ray *ray, t_sphere *sphere, t_data *data)
{
	const t_vec	oc = point_diff(ray->origin, sphere->center);
	t_quadeq	eq;

	eq.a = vec_dot(ray->direction, ray->direction);
	eq.b = 2.0 * vec_dot(oc, ray->direction);
	eq.c = vec_dot(oc, oc) - sphere->r * sphere->r;
	solve_quadeq(&eq);
	if (eq.tmin < ray->t_obj)
		ray->t_obj = eq.tmin;
	else
		return ;
	ray->color = sphere->color;
	ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj));
	ray->fr = sp_facing_ratio(get_hitpoint(*ray, ray->t_obj), *sphere,
			data->light);
}

/**
 * Check if the primary ray hits the given plane.
 * It will update the color of the ray only if the hit distance is smaller
 * than the recorded one.
 * fabs to make sure it's checking both side,
 * because on the other side, denom is negative.
 */
void	hit_plane(t_ray *ray, t_plane *plane, t_data *data)
{
	const double	denom = vec_dot(ray->direction, plane->vector);
	const t_vec		op = point_diff(ray->origin, plane->point);
	double			t;

	if (fabs(denom) < 1e-6)
		return ;
	t = -vec_dot(plane->vector, op) / denom;
	if (t >= 0 && t < ray->t_obj)
	{
		ray->color = plane->color;
		ray->t_obj = t;
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj));
		ray->fr = pl_facing_ratio(get_hitpoint(*ray, ray->t_obj), *plane,
				data->light);
	}
}

/* Send a ray to check for all intersections of all the objects in the scene. */
void	intersection(t_ray *ray, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_obj)
	{
		if (data->objs[i].type == SPHERE)
			hit_sphere(ray, &data->objs[i].sp, data);
		else if (data->objs[i].type == PLANE)
			hit_plane(ray, &data->objs[i].pl, data);
		else if (data->objs[i].type == CYLINDER)
		{
			hit_cylinder(ray, &data->objs[i].cy, data);
			hit_cy_disk(ray, &data->objs[i].cy, data);
		}
	}
}
