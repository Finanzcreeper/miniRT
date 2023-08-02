#include "miniRT.h"

void	translation(t_point *pt, t_action act, t_axis axis, t_object *obj)
{
	if (act == INCREMENT && axis == AXIS_X)
		pt->x += TRAN_STEP;
	if (act == INCREMENT && axis == AXIS_Y)
		pt->y += TRAN_STEP;
	if (act == INCREMENT && axis == AXIS_Z)
		pt->z += TRAN_STEP;
	if (act == DECREMENT && axis == AXIS_X)
		pt->x -= TRAN_STEP;
	if (act == DECREMENT && axis == AXIS_Y)
		pt->y -= TRAN_STEP;
	if (act == DECREMENT && axis == AXIS_Z)
		pt->z -= TRAN_STEP;
	if (obj && obj->type == CYLINDER)
		update_cy(&obj->cy);
}

void	rotation(t_vector *vec, t_action act, t_axis axis, t_object *obj)
{
	if (axis == AXIS_X)
		*vec = rotate_x(*vec, act);
	if (axis == AXIS_Y)
		*vec = rotate_y(*vec, act);
	if (axis == AXIS_Z)
		*vec = rotate_z(*vec, act);
	if (obj && obj->type == CYLINDER)
		update_cy(&obj->cy);
}

bool	adjust_camera(t_action action, t_data *data, t_axis axis)
{
	if (data->action == TRANSLATION)
		translation(&data->camera.view, action, axis, NULL);
	if (data->action == ROTATION)
		rotation(&data->camera.orientation, action, axis, NULL);
	render(data->img, data);
	return (true);
}

bool	adjust_light(t_action action, t_data *data, t_axis axis)
{
	if (data->action == TRANSLATION)
		translation(&data->light.source, action, axis, NULL);
	render(data->img, data);
	return (true);
}
