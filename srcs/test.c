#include "miniRT.h"

void	colormaker(t_color *color)
{
	color->mlxcolor = (color->r << 24 | color->g << 16 | color->b << 8 | 255);
}


void	sphere_ambiance(t_data *data, int c)
{
	if (data->objects[c].sphere.color.r + data->ambient.color.r < 255)
		data->objects[c].sphere.color.r += data->ambient.color.r;
	else
		data->objects[c].sphere.color.r = 255;
	if (data->objects[c].sphere.color.g + data->ambient.color.g < 255)
		data->objects[c].sphere.color.g += data->ambient.color.g;
	else
		data->objects[c].sphere.color.g = 255;
	if (data->objects[c].sphere.color.b + data->ambient.color.b < 255)
		data->objects[c].sphere.color.b += data->ambient.color.b;
	else
		data->objects[c].sphere.color.b = 255;
}

void	plane_ambiance(t_data *data, int c)
{
	if (data->objects[c].plane.color.r + data->ambient.color.r < 255)
		data->objects[c].plane.color.r += data->ambient.color.r;
	else
		data->objects[c].plane.color.r = 255;
	if (data->objects[c].plane.color.g + data->ambient.color.g < 255)
		data->objects[c].plane.color.g += data->ambient.color.g;
	else
		data->objects[c].plane.color.g = 255;
	if (data->objects[c].plane.color.b + data->ambient.color.b < 255)
		data->objects[c].plane.color.b += data->ambient.color.b;
	else
		data->objects[c].plane.color.b = 255;
}

void	cylinder_ambiance(t_data *data, int c)
{
	if (data->objects[c].cylinder.color.r + data->ambient.color.r < 255)
		data->objects[c].cylinder.color.r += data->ambient.color.r;
	else
		data->objects[c].cylinder.color.r = 255;
	if (data->objects[c].cylinder.color.g + data->ambient.color.g < 255)
		data->objects[c].cylinder.color.g += data->ambient.color.g;
	else
		data->objects[c].cylinder.color.g = 255;
	if (data->objects[c].cylinder.color.b + data->ambient.color.b < 255)
		data->objects[c].cylinder.color.b += data->ambient.color.b;
	else
		data->objects[c].cylinder.color.b = 255;
}

void	apply_ambience_light(t_data *data)
{
	int	c;

	c = 0;
	while (c < data->n_obj)
	{
		if (data->objects[c].type == SPHERE)
			sphere_ambiance(data, c);
		if (data->objects[c].type == CYLINDER)
			cylinder_ambiance(data, c);
		if (data->objects[c].type == PLANE)
			plane_ambiance(data, c);
	}
}

void	draw(mlx_image_t *img, t_data *data)
{
	unsigned int	c;
	int				i;
	int				f;
	unsigned int	h;

	h = 0;
	c = 0;
	data->ambient.color.r = 0;
	data->ambient.color.g = 255;
	data->ambient.color.b = 0;
	colormaker(&data->ambient.color);
	i = data->ambient.color.r;
	if (data->ambient.color.r > data->ambient.color.g)
		i = data->ambient.color.g;
	if (data->ambient.color.g > data->ambient.color.b)
		i = data->ambient.color.b;
	i = 255 - i;
	i = img->width / i;
	f = 0;
	while (c < img->width)
	{
		if (f == i)
		{
			if (data->ambient.color.r != 255)
				data->ambient.color.r += 1;
			if (data->ambient.color.g != 255)
				data->ambient.color.g += 1;
			if (data->ambient.color.b != 255)
				data->ambient.color.b += 1;
			colormaker(&data->ambient.color);
			f = 0;
		}
		while (h < img->height)
		{
			mlx_put_pixel(img, c, h++, data->ambient.color.mlxcolor);
		}
		h = 0;
		c++;
		f++;
	}
}
// 0.2126 * R + 0.7152 * G + 0.0722 * B = Y

void	setup_window(mlx_t **mlx)
{
	int			width;
	int			height;

	width = 1;
	height = 1;
	*mlx = mlx_init(width, height, "miniRT", true);
	mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(*mlx, width, height);
}

int	test(t_data *data)
{
	mlx_image_t	*img;

	setup_window(&data->mlx);
	colormaker(&data->ambient.color);
	img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	data->n_obj = 0;
	apply_ambience_light(data);
	draw(img, data);
	mlx_image_to_window(data->mlx, img, 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
