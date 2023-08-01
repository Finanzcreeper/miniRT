#include "miniRT.h"

/**
 * Check if the primary ray hits the given sphere.
 * It will update the color of the ray only if the hit distance is smaller
 * than the recorded one.
 * Reference: https://raytracing.github.io/books/RayTracingInOneWeekend.html#addingasphere/ray-sphereintersection
 * Optimization: unify the two root into one block.
 * Known issue/To-do: Inside of the object.
 */
void	hit_sphere(t_ray *ray, t_sphere *sphere, t_data *data, int idx)
{
	const t_vector	oc = point_diff(ray->origin, sphere->center);
	t_quadeq		eq;

	eq.a = vec_dot(ray->direction, ray->direction);
	eq.b = 2.0 * vec_dot(oc, ray->direction);
	eq.c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	solve_quadeq(&eq);
	if (eq.discriminant >= 0 && eq.t1 >= 0 && eq.t2 < 0 && eq.t1 < ray->t_obj)
		ray->t_obj = eq.t1;
	else if (eq.discriminant >= 0 && eq.t2 >= 0 && eq.t2 < ray->t_obj)
		ray->t_obj = eq.t2;
	else
		return ;
	ray->color = sphere->color;
	ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	ray->fr = sphere_facing_ratio(get_hitpoint(*ray, ray->t_obj), *sphere, data->light);
}

/**
 * Check if the primary ray hits the given plane.
 * It will update the color of the ray only if the hit distance is smaller
 * than the recorded one.
 * Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
 * fabs to make sure it's checking both side, because on the other side, denom is negative.
 */
void	hit_plane(t_ray *ray, t_plane *plane, t_data *data, int idx)
{
	const double	denom = vec_dot(ray->direction, plane->vector);
	const t_vector	op = point_diff(ray->origin, plane->point);
	double			t;

	if (fabs(denom) < 1e-6)
		return ;
	t = -vec_dot(plane->vector, op) / denom;
	if (t >= 0 && t < ray->t_obj)
	{
		ray->color = plane->color;
		ray->t_obj = t;
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
		ray->fr = plane_facing_ratio(get_hitpoint(*ray, ray->t_obj), *plane, data->light);
	}
}

void	hit_cylinder_disk(t_ray *ray, t_cylinder *cy, t_data *data, int idx)
{
	const double	t3 = vec_dot(point_diff(cy->top, ray->origin), cy->vector)
		/ vec_dot(ray->direction, cy->vector);
	const double	t4 = vec_dot(point_diff(cy->bottom, ray->origin), cy->vector)
		/ vec_dot(ray->direction, cy->vector);
	const t_vector	v3 = point_diff(get_hitpoint(*ray, t3), cy->top);
	const t_vector	v4 = point_diff(get_hitpoint(*ray, t4), cy->bottom);

	if (vec_dot(v3, v3) <= cy->radius * cy->radius && t3 > 0 && t3 < ray->t_obj)
	{
		ray->t_obj = t3;
		ray->color = cy->color;
		ray->fr = cy_fr_top(get_hitpoint(*ray, ray->t_obj), *cy, data->light);
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	}
	if (vec_dot(v4, v4) <= cy->radius*cy->radius && t4 > 0 && t4 < ray->t_obj)
	{
		ray->t_obj = t4;
		ray->color = cy->color;
		ray->fr = cy_fr_bottom(get_hitpoint(*ray, ray->t_obj), *cy, data->light);
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	}
}

/**
 * Ref: https://hugi.scene.org/online/hugi24/coding%20graphics%20chris%20dragan%20raytracing%20shapes.htm
*/
void	hit_cylinder(t_ray *ray, t_cylinder *cy, t_data *data, int idx)
{
	const t_vector	oc = point_diff(ray->origin, cy->top);
	t_vector		hit_vector;
	t_quadeq		eq;

	eq.a = vec_dot(ray->direction, ray->direction) -
		pow(vec_dot(ray->direction, cy->vector), 2);
	eq.b = 2 * (vec_dot(ray->direction, oc) - vec_dot(ray->direction,
		cy->vector) * vec_dot(oc, cy->vector));
	eq.c = vec_dot(oc, oc) - pow(vec_dot(oc, cy->vector), 2) -
		pow(cy->radius, 2);
	solve_quadeq(&eq);
	if (eq.discriminant >= 0 && eq.t1 <= eq.t2 && eq.t1 >= 0 && eq.t1 < ray->t_obj)
		ray->t_obj = eq.t1;
	else if (eq.discriminant >= 0 && eq.t1 > eq.t2 && eq.t2 >= 0 && eq.t2 < ray->t_obj)
		ray->t_obj = eq.t2;
	else
		return ;
	hit_vector = point_diff(get_hitpoint(*ray, ray->t_obj), cy->top);
	if (vec_dot(hit_vector, cy->vector) > 0
		&& (vec_dot(hit_vector, cy->vector) <= cy->height))
	{
		ray->color = cy->color;
		ray->fr = cy_fr_side(get_hitpoint(*ray, ray->t_obj), *cy, data->light);
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
	}
	else
		ray->t_obj = INFINITY;
	hit_cylinder_disk(ray, cy, data, idx);
}

/* Send a ray to check for all intersections of all the objects in the scene. */
void	intersection(t_ray *ray, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_obj)
	{
		if (data->objs[i].type == SPHERE)
			hit_sphere(ray, &data->objs[i].sp, data, i);
		else if (data->objs[i].type == PLANE)
			hit_plane(ray, &data->objs[i].pl, data, i);
		else if (data->objs[i].type == CYLINDER)
			hit_cylinder(ray, &data->objs[i].cy, data, i);
	}
}
