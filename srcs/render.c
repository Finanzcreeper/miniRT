#include "miniRT.h"

static bool	render_inside(mlx_image_t *img, t_data *data)
{
	int			h;
	int			w;
	t_ray		ray;

	if (!data || !data->cam_inside)
		return (false);
	w = -1;
	while (++w < (int) img->width)
	{
		h = -1;
		while (++h < (int) img->height)
		{
			ray.color = *data->cam_inside->color;
			ray.light = false;
			ray.fr = 1;
			mlx_put_pixel(img, w, h, mlxcolor(ray.color, ray.fr, *data,
					ray.light));
		}
	}
	return (true);
}

void	render(mlx_image_t *img, t_data *data)
{
	int			h;
	int			w;
	t_ray		ray;

	data->cam_inside = NULL;
	check_inside(data);
	if (data->cam_inside && render_inside(img, data))
		return ;
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
}

void	update_controlled(t_data *data, int idx)
{
	mlx_delete_image(data->mlx, data->prt.w);
	if (idx == CAM_IDX)
		data->prt.w = mlx_put_string(data->mlx, STR_CAM, 0, 80);
	if (idx == LIGHT_IDX)
		data->prt.w = mlx_put_string(data->mlx, STR_LIGHT, 0, 80);
	if (idx < 0 || idx >= data->n_obj)
		return ;
	if (data->objs[idx].type == SPHERE)
		data->prt.w = mlx_put_string(data->mlx, STR_SP, 0, 80);
	if (data->objs[idx].type == CYLINDER)
		data->prt.w = mlx_put_string(data->mlx, STR_CY, 0, 80);
	if (data->objs[idx].type == PLANE)
		data->prt.w = mlx_put_string(data->mlx, STR_PL, 0, 80);
}

void	increment_rerender(t_data *data, int key)
{
	t_object	*obj;

	if (data->idx == CAM_IDX && adjust_camera(INCREMENT, data, key))
		return ;
	if (data->idx == LIGHT_IDX && adjust_light(INCREMENT, data, key))
		return ;
	if (data->idx >= data->n_obj)
		return ;
	obj = &data->objs[data->idx];
	if (data->action == TRANSLATION)
		translation(data->objs[data->idx].pt, INCREMENT, key, obj);
	if (data->action == ROTATION && data->objs[data->idx].type == CYLINDER)
		rotation(&obj->cy.o_vector, INCREMENT, key, obj);
	if (data->action == ROTATION && data->objs[data->idx].type == PLANE)
		rotation(&obj->pl.vector, INCREMENT, key, obj);
	render(data->img, data);
}

void	decrement_rerender(t_data *data, int key)
{
	t_object	*obj;

	if (data->idx == CAM_IDX && adjust_camera(DECREMENT, data, key))
		return ;
	if (data->idx == LIGHT_IDX && adjust_light(DECREMENT, data, key))
		return ;
	if (data->idx >= data->n_obj)
		return ;
	obj = &data->objs[data->idx];
	if (data->action == TRANSLATION)
		translation(data->objs[data->idx].pt, DECREMENT, key, obj);
	if (data->action == ROTATION && data->objs[data->idx].type == CYLINDER)
		rotation(&obj->cy.o_vector, DECREMENT, key, obj);
	if (data->action == ROTATION && data->objs[data->idx].type == PLANE)
		rotation(&obj->pl.vector, DECREMENT, key, obj);
	render(data->img, data);
}
