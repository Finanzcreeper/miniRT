#include "miniRT.h"

void	translation(t_point *pt, t_action act, int key, t_object *obj)
{
	if (act == INCREMENT && key == MLX_KEY_D)
		pt->x += TRAN_STEP;
	if (act == INCREMENT && key == MLX_KEY_W)
		pt->y += TRAN_STEP;
	if (act == INCREMENT && key == 20)
		pt->z += TRAN_STEP;
	if (act == DECREMENT && key == MLX_KEY_A)
		pt->x -= TRAN_STEP;
	if (act == DECREMENT && key == MLX_KEY_S)
		pt->y -= TRAN_STEP;
	if (act == DECREMENT && key == 21)
		pt->z -= TRAN_STEP;
	if (obj && obj->type == CYLINDER)
		update_cy(&obj->cy);
}

void	rotation(t_vec *vec, t_action act, int key, t_object *obj)
{
	if (key == MLX_KEY_W || key == MLX_KEY_S)
		*vec = rotate_x(*vec, act);
	if (key == 20 || key == 21)
		*vec = rotate_y(*vec, act);
	if (key == MLX_KEY_A || key == MLX_KEY_D)
		*vec = rotate_z(*vec, act);
	if (obj && obj->type == CYLINDER)
		update_cy(&obj->cy);
}

bool	adjust_camera(t_action action, t_data *data, int key)
{
	if (data->action == TRANSLATION)
		translation(&data->camera.view, action, key, NULL);
	if (data->action == ROTATION)
		rotation(&data->camera.orientation, action, key, NULL);
	render(data->img, data);
	return (true);
}

bool	adjust_light(t_action action, t_data *data, int key)
{
	if (data->action == TRANSLATION)
		translation(&data->light.source, action, key, NULL);
	render(data->img, data);
	return (true);
}
