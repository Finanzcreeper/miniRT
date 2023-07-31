#include "miniRT.h"

double	sphere_facing_ratio(t_point hitpoint, t_sphere sphere, t_light light)
{
	const t_vector	n = vec_normalize(point_diff(hitpoint, sphere.center));
	const t_vector	ol = vec_normalize(point_diff(light.source, hitpoint));
	double			fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}

double	plane_facing_ratio(t_point hitpoint, t_plane plane, t_light light)
{
	const t_vector	n = plane.vector;
	const t_vector	ol = vec_normalize(point_diff(light.source, hitpoint));
	double			fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}

double	cy_fr_side(t_point hitpoint, t_cylinder cylinder, t_light light)
{
	const t_vector	n = vec_normalize(point_diff(hitpoint, cylinder.center));
	const t_vector	ol = vec_normalize(point_diff(light.source, hitpoint));
	double			fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}

double	cy_fr_top(t_point hitpoint, t_cylinder cylinder, t_light light)
{
	const t_vector	n = vec_negate(cylinder.vector);
	const t_vector	ol = vec_normalize(point_diff(light.source, hitpoint));
	double			fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}

double	cy_fr_bottom(t_point hitpoint, t_cylinder cylinder, t_light light)
{
	const t_vector	n = cylinder.vector;
	const t_vector	ol = vec_normalize(point_diff(light.source, hitpoint));
	double			fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}
