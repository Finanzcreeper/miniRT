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
	const t_vector	up = {0, 1, 0};

	ray.origin = data->camera.view;
	t_vector	right = vec_cross(up, data->camera.orientation);
	t_vector	true_up = vec_cross(data->camera.orientation, right);

	float	ndc_x = (width + 0.5f) / img->width * 2.0f - 1.0f; // remapping from [0, 1] to [-1, 1]
	float	ndc_y = 1.0f - (height+ 0.5f) / img->height * 2.0f; // for y, up is positive

	float z = -1.0f; // focal length by convention
	float r = tan((data->camera.fov * (M_PI / 180)) / 2.0f); // field of view
	float screen_x = ndc_x * r * (img->width / img->height);
	float screen_y = ndc_y * r;

	ray.direction.x = screen_x * right.x + screen_y * true_up.x - z * data->camera.orientation.x;
	ray.direction.y = screen_x * right.y + screen_y * true_up.y - z * data->camera.orientation.y;
	ray.direction.z = screen_x * right.z + screen_y * true_up.z - z * data->camera.orientation.z;

	ray.direction = vec_normalize(ray.direction);
	ray.view = NULL;
	return (ray);
}
