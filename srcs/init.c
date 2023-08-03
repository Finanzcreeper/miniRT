#include "miniRT.h"

void	init_data(t_data *data)
{
	data->file_content = NULL;
	data->lines = NULL;
	data->infos = NULL;
	data->objs = NULL;
	data->cam_inside = NULL;
	data->mlx = NULL;
	data->ambient.assigned = false;
	data->camera.assigned = false;
	data->light.assigned = false;
	data->n_obj = 0;
	data->idx = CAM_IDX;
	data->action = TRANSLATION;
}

t_ray	init_ray(t_data *data, mlx_image_t *img, int height, int width)
{
	const t_vec	up = {0, 1, 0};
	t_raymap	m;
	t_ray		ray;

	ray.origin = data->camera.view;
	m.right = vec_cross(up, data->camera.orientation);
	m.true_up = vec_cross(data->camera.orientation, m.right);
	m.ndc_x = (width + 0.5f) / img->width * 2.0f - 1.0f;
	m.ndc_y = 1.0f - (height + 0.5f) / img->height * 2.0f;
	m.z = FOCAL_LEN;
	m.r = tan((data->camera.fov * (M_PI / 180)) / 2.0f);
	m.screen_x = m.ndc_x * m.r * ((float) img->width / (float) img->height);
	m.screen_y = m.ndc_y * m.r;
	ray.direction.x = m.screen_x * m.right.x + m.screen_y * m.true_up.x
		- m.z * data->camera.orientation.x;
	ray.direction.y = m.screen_x * m.right.y + m.screen_y * m.true_up.y
		- m.z * data->camera.orientation.y;
	ray.direction.z = m.screen_x * m.right.z + m.screen_y * m.true_up.z
		- m.z * data->camera.orientation.z;
	ray.direction = vec_normalize(ray.direction);
	ray.light = true;
	ray.t_obj = INFINITY;
	return (ray);
}

t_ray	init_shadow_ray(t_point origin, t_vec direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

void	init_context(t_data *data)
{
	data->prt.wasd = mlx_put_string(data->mlx, STR_WASD, 0, 0);
	data->prt.scroll = mlx_put_string(data->mlx, STR_SCROLL, 0, 20);
	data->prt.swap_obj = mlx_put_string(data->mlx, STR_SWAP, 0, 40);
	data->prt.swap_rot_trans = mlx_put_string(data->mlx, STR_ACT, 0, 60);
	data->prt.w = mlx_put_string(data->mlx, STR_CAM, 0, 80);
}
