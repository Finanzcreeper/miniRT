#include "miniRT.h"

void	hit_sphere(t_ray *ray, t_sphere *sphere, t_data *data, int idx)
{
	const t_vector	oc = point_diff(ray->origin, sphere->center);
	t_quadeq		eq;

	eq.a = vec_dot(ray->direction, ray->direction);
	eq.b = 2.0 * vec_dot(oc, ray->direction);
	eq.c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	solve_quadeq(&eq);
	if (eq.discriminant < 0)
		return ;
	if (eq.t1 <= eq.t2 && eq.t1 < ray->t_obj)
	{
		ray->color = sphere->color;
		ray->t_obj = eq.t1;
		//ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	}
	else if (eq.t1 > eq.t2 && eq.t2 < ray->t_obj)
	{
		ray->color = sphere->color;
		ray->t_obj = eq.t2;
		//ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	}
	(void)data;
	(void)idx;
}

void	hit_plane(t_ray *ray, t_plane *plane, t_data *data, int idx)
{
	const double	denom = vec_dot(ray->direction, plane->vector);
	const t_vector	op = point_diff(ray->origin, plane->point);
	double			t;

	if (denom < 1e-6)
		return ;
	t = - vec_dot(plane->vector, op) / denom;
	if (t < 0)
		return ;
	if (t < ray->t_obj)
	{
		ray->color = plane->color;
		ray->t_obj = t;
	}
	(void)data;
	(void)idx;
}

void	intersection(t_ray *ray, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_obj)
	{
		if (data->objects[i].type == SPHERE)
			hit_sphere(ray, &data->objects[i].sphere, data, i);
		else if (data->objects[i].type == PLANE)
			hit_plane(ray, &data->objects[i].plane, data, i);
	}
}
