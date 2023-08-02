#include "miniRT.h"

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
