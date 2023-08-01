#include "miniRT.h"

static uint32_t	bg_color(void)
{
	return (BG_R << 24 | BG_G << 16 | BG_B << 8 | BG_A);
}

void	render(mlx_image_t *img, t_data *data)
{
	int			h;
	int			w;
	t_ray		ray;

	w = -1;
	while (++w < (int) img->width)
	{
		h = -1;
		while (++h < (int) img->height)
		{
			ray = init_ray(data, img, h, w);
			intersection(&ray, data);
			if (ray.t_obj == INFINITY)
				mlx_put_pixel(img, w, h, bg_color());
			else
				mlx_put_pixel(img, w, h, mlxcolor(ray.color, ray.fr, *data,
						ray.light));
		}
	}
	update_controlled(data);
}

void	update_controlled(t_data *data)
{
	mlx_delete_image(data->mlx, data->prt.w);
	if (data->idx == CAM_IDX)
		data->prt.w = mlx_put_string(data->mlx, "Controlling: Camera", 0, 80);
	if (data->idx == LIGHT_IDX)
		data->prt.w = mlx_put_string(data->mlx, "Controlling: Light", 0, 80);
	if (data->objs[data->idx].type == SPHERE)
		data->prt.w = mlx_put_string(data->mlx, "Controlling: Sphere", 0, 80);
	if (data->objs[data->idx].type == CYLINDER)
		data->prt.w = mlx_put_string(data->mlx, "Controlling: Cylinder", 0, 80);
	if (data->objs[data->idx].type == PLANE)
		data->prt.w = mlx_put_string(data->mlx, "Controlling: Plane", 0, 80);
}

void	increment_rerender(t_data *data)
{
	if (data->idx == CAM_IDX && adjust_camera(INCREMENT, data))
		return ;
	if (data->idx == LIGHT_IDX && adjust_light(INCREMENT, data))
		return ;
	if (data->idx >= data->n_obj)
		return ;
	if (data->action == TRANSLATION)
		translation(data->objs[data->idx].pt, INCREMENT, data->axis);
	if (data->action == ROTATION && data->objs[data->idx].type == CYLINDER)
		rotation(&data->objs[data->idx].cy.vector, INCREMENT, data->axis);
	if (data->action == ROTATION && data->objs[data->idx].type == PLANE)
		rotation(&data->objs[data->idx].pl.vector, INCREMENT, data->axis);
	// render(data->img, data);
}

void	decrement_rerender(t_data *data)
{	if (data->idx == CAM_IDX && adjust_camera(DECREMENT, data))
		return ;
	if (data->idx == LIGHT_IDX && adjust_light(DECREMENT, data))
		return ;
	if (data->idx >= data->n_obj)
		return ;
	if (data->action == TRANSLATION)
		translation(data->objs[data->idx].pt, DECREMENT, data->axis);
	if (data->action == ROTATION && data->objs[data->idx].type == CYLINDER)
		rotation(&data->objs[data->idx].cy.vector, DECREMENT, data->axis);
	if (data->action == ROTATION && data->objs[data->idx].type == PLANE)
		rotation(&data->objs[data->idx].pl.vector, DECREMENT, data->axis);
	// render(data->img, data);
}
