#include "miniRT.h"

double	sp_facing_ratio(t_point hp, t_sphere sp, t_light light)
{
	const t_vec	n = vec_normalize(point_diff(hp, sp.center));
	const t_vec	ol = vec_normalize(point_diff(light.source, hp));
	double		fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}

double	pl_facing_ratio(t_point hitpoint, t_plane plane, t_light light)
{
	const t_vec	n = plane.vector;
	const t_vec	n2 = vec_negate(plane.vector);
	const t_vec	ol = vec_normalize(point_diff(light.source, hitpoint));
	double		fr;

	fr = fmax(0, fmax(vec_dot(n, ol), vec_dot(n2, ol)));
	return (fr);
}

double	cy_fr_side(t_point hitpoint, t_cylinder cylinder, t_light light)
{
	const t_vec	n = vec_normalize(point_diff(hitpoint, cylinder.center));
	const t_vec	ol = vec_normalize(point_diff(light.source, hitpoint));
	double		fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}

double	cy_fr_top(t_point hitpoint, t_cylinder cylinder, t_light light)
{
	const t_vec	n = vec_negate(cylinder.vector);
	const t_vec	ol = vec_normalize(point_diff(light.source, hitpoint));
	double		fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}

double	cy_fr_bottom(t_point hitpoint, t_cylinder cylinder, t_light light)
{
	const t_vec	n = cylinder.vector;
	const t_vec	ol = vec_normalize(point_diff(light.source, hitpoint));
	double		fr;

	fr = fmax(0, vec_dot(n, ol));
	return (fr);
}
