#include "miniRT.h"

void	translation(t_point *pt, t_action action, t_axis axis)
{
	if (action == INCREMENT && axis == AXIS_X)
		pt->x += TRAN_STEP;
	if (action == INCREMENT && axis == AXIS_Y)
		pt->y += TRAN_STEP;
	if (action == INCREMENT && axis == AXIS_Z)
		pt->z += TRAN_STEP;
	if (action == DECREMENT && axis == AXIS_X)
		pt->x -= TRAN_STEP;
	if (action == DECREMENT && axis == AXIS_Y)
		pt->y -= TRAN_STEP;
	if (action == DECREMENT && axis == AXIS_Z)
		pt->z -= TRAN_STEP;
}

void	rotation(t_vector *vec, t_action action, t_axis axis)
{
	if (axis == AXIS_X)
		*vec = rotate_x(*vec, action);
	if (axis == AXIS_Y)
		*vec = rotate_y(*vec, action);
	if (axis == AXIS_Z)
		*vec = rotate_z(*vec, action);
}

bool	adjust_camera(t_action action, t_data *data)
{
	(void) action;
	(void) data;
	return (true);
}

bool	adjust_light(t_action action, t_data *data)
{
	(void) action;
	(void) data;
	return (true);
}
