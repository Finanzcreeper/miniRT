#include "miniRT.h"

// static bool	in_light_inside_sp(t_data *data, t_sphere sp)
// {
// 	const t_light	light = data->light;
// 	const double	t_light = vec_len(point_diff(sp.center, light.source));

// 	if (t_light < sp.r)
// 		return (true);
// 	return (false);
// }

// static bool	in_light_inside_cy(t_data *data, t_cylinder cy)
// {
// 	const t_vec		pa = point_diff(data->light.source, cy.bottom);
// 	const t_vec		pb = point_diff(cy.top, cy.bottom);
// 	const double	t = vec_dot(pa, pb) / vec_dot(pb, pb);
// 	t_vec			pc;

// 	if (t < 0 || t > 1)
// 		return (false);
// 	pc.x = pb.x * t;
// 	pc.y = pb.y * t;
// 	pc.z = pb.z * t;
// 	return (vec_len(vec_diff(pc, (t_vec) pa)) <= cy.r);
// }

// bool	in_light_inside(t_ray ray, t_data *data, t_point hp, int idx)
// {
// 	if (idx >= data->n_obj)
// 		return (false);
// 	if (data->objs[idx].type == PLANE)
// 		return (true);
// 	if (data->objs[idx].type == SPHERE)
// 		return (in_light_inside_sp(data, data->objs[idx].sp));
// 	if (data->objs[idx].type == CYLINDER)
// 		return (in_light_inside_cy(data, data->objs[idx].cy));
// 	(void) hp;
// 	(void) ray;
// 	return (false);
// }

static void	inside_sp(t_object *obj, t_point cam, t_data *data)
{
	const double	t_light = vec_len(point_diff(obj->sp.center, cam));

	if (t_light < obj->sp.r)
		data->cam_inside = obj;
}

static void	inside_cy(t_object *obj, t_point cam, t_data *data)
{
	const t_cylinder	*cy = &obj->cy;
	const t_vec			v = point_diff(cam, cy->top);
	t_vec				proj;
	t_vec				r;

	proj.x = vec_dot(v, cy->vector) / vec_dot(cy->vector, cy->vector)
		* cy->vector.x;
	proj.y = vec_dot(v, cy->vector) / vec_dot(cy->vector, cy->vector)
		* cy->vector.y;
	proj.z = vec_dot(v, cy->vector) / vec_dot(cy->vector, cy->vector)
		* cy->vector.z;
	r = vec_diff(v, proj);
	if (vec_len(r) > cy->r)
		return ;
	if (vec_dot(proj, cy->vector) < 0 || vec_len(proj) > cy->height)
		return ;
	data->cam_inside = obj;
}

void	check_inside(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_obj)
	{
		if (data->objs[i].type == SPHERE)
			inside_sp(&data->objs[i], data->camera.view, data);
		if (data->objs[i].type == CYLINDER)
			inside_cy(&data->objs[i], data->camera.view, data);
	}
}
