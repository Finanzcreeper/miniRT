#include "miniRT.h"

void	init_data(t_data *data)
{
	data->file_content = NULL;
	data->lines = NULL;
	data->infos = NULL;
	data->objects = NULL;
	data->mlx = NULL;
	data->ambient.assigned = false;
	data->camera.assigned = false;
	data->light.assigned = false;
	data->n_obj = 0;
}

t_ray	init_ray(t_data *data, t_vector direction)
{
	t_ray ray;

	ray.origin = data->camera.view;
	ray.direction = direction;
	ray.view = NULL;
	return (ray);
}
