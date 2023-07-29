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
	if (eq.discriminant < 0 || (eq.t1 < 0 && eq.t2 < 0)) // unit length instead of 0? hit behind the screen
		return ;
	if (eq.t1 <= eq.t2 && eq.t1 >= 0 && eq.t1 < ray->t_obj)
	{
		ray->color = sphere->color;
		ray->t_obj = eq.t1;
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
		ray->facing_ratio = sphere_facing_ratio(get_hitpoint(*ray, ray->t_obj), *sphere, data->light);
	}
	else if (eq.t1 > eq.t2 && eq.t2 >= 0 && eq.t2 < ray->t_obj)
	{
		ray->color = sphere->color;
		ray->t_obj = eq.t2;
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
		ray->facing_ratio = sphere_facing_ratio(get_hitpoint(*ray, ray->t_obj), *sphere, data->light);
	}
}

/**
 * Check if the primary ray hits the given plane.
 * It will update the color of the ray only if the hit distance is smaller
 * than the recorded one.
 * Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-plane-and-ray-disk-intersection.html
 * Known issue: the backside of the plane is not checked.
 * Since direction of the plane is perpendicular to one side of the plane.
 */
void	hit_plane(t_ray *ray, t_plane *plane, t_data *data, int idx)
{
	const double	denom = vec_dot(ray->direction, plane->vector);
	const t_vector	op = point_diff(ray->origin, plane->point);
	double			t;

	if (fabs(denom) < 1e-6) // ray could lie on the plane
		return ;
	t = - vec_dot(plane->vector, op) / denom;
	if (t < 0) // hitting the backside of the plane?
		return ;
	if (t >= 0 && t < ray->t_obj)
	{
		ray->color = plane->color;
		ray->t_obj = t;
		ray->light = in_light(data, get_hitpoint(*ray, ray->t_obj), idx);
		ray->facing_ratio = plane_facing_ratio(get_hitpoint(*ray, ray->t_obj), *plane, data->light);
	}
}

void	hit_cylinder(t_ray *ray, t_cylinder *cylinder, t_data *data, int idx)
{

}

/* Send a ray to check for all intersections of all the objects in the scene. */
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
		else if (data->objects[i].type == CYLINDER)
			hit_cylinder(ray, &data->objects[i].cylinder, data, i);
	}
}
