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

t_ray	init_ray(t_data *data, mlx_image_t *img, int height, int width)
{
	t_ray 			ray;
	t_vector		direction;
	const double	unit_x = 10 / (img->width); // 30 degree for now
	const double	unit_y = 10 / (img->height); // 30 degree for now

	//printf("unit: %d %d\n", img->width, img->height);
	ray.origin = data->camera.view;
	direction.x = data->camera.orientation.x + unit_x * width;
	direction.y = data->camera.orientation.y + unit_y * height;
	direction.z = data->camera.orientation.z;
	//direction = vec_normalize(direction);
	ray.direction = direction;
	//printf("direction: %f %f %f\n", direction.x, direction.y, direction.z);
	ray.view = NULL;
	return (ray);
}
