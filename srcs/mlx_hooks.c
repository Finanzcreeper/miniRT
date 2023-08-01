#include "miniRT.h"

/*changing control scheme to somethign that may be more intuitive (for wasd gamers at least)
Selection of objects handeled with QE to allow easz acces to switchin objects without moving hand from traslation keys
Translation of objects on X and Y axis handled per WASD respectively*/
void	ft_keyhook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		ft_exit(data, EXIT_SUCCESS);
	if (keydata.key == MLX_KEY_T && keydata.action == MLX_PRESS)
		data->action = TRANSLATION;
	if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
		data->action = ROTATION;
	if (keydata.key == MLX_KEY_Q && keydata.action == MLX_PRESS
		&& data->idx > CAM_IDX)
	{
		data->idx--;
		update_controlled(data);
	}
	if (keydata.key == MLX_KEY_E && keydata.action == MLX_PRESS
		&& data->idx < data->n_obj - 1)
	{
		data->idx++;
		update_controlled(data);
	}
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		increment_rerender(data, AXIS_X);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		decrement_rerender(data, AXIS_X);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		increment_rerender(data, AXIS_Y);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		decrement_rerender(data, AXIS_Y);
	//render(data->img, data);
}

void	ft_scrollhook(double xdelta, double ydelta, void *param)
{
	t_data	*data;

	xdelta = xdelta + 0;
	data = param;
	if (ydelta > 0)
		increment_rerender(data, AXIS_Z);
	if (ydelta < 0)
		decrement_rerender(data, AXIS_Z);
	//render(data->img, data);
}
