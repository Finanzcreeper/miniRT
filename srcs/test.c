#include "miniRT.h"

void	colormaker(t_color *color)
{
	color->mlxcolor = (color->r << 24 | color->g << 16 | color->b << 8 | 255);
}


void	object_ambiance(t_data *data, int c)
{
	const double	ratio = data->ambient.ratio;
	const t_color	amb_color = data->ambient.color;
	t_color	*obj_color;

	obj_color = data->objects[c].color;
	if (obj_color->r + amb_color.r * ratio < 255)
		obj_color->r += amb_color.r * ratio;
	else
		obj_color->r = 255;
	if (obj_color->g + amb_color.g * ratio < 255)
		obj_color->g += amb_color.g * ratio;
	else
		obj_color->g = 255;
	if (obj_color->b + amb_color.b * ratio < 255)
		obj_color->b += amb_color.b * ratio;
	else
		obj_color->b = 255;
}

void	apply_ambience_light(t_data *data)
{
	int	c;

	c = -1;
	while (++c < data->n_obj)
		object_ambiance(data, c);
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
	int	width = 640;
	int	height = 640;

	// width = 1;
	// height = 1;
	*mlx = mlx_init(width, height, "miniRT", true);
	// mlx_get_monitor_size(0, &width, &height);
	mlx_set_window_size(*mlx, width, height);
}

uint32_t	bg_color(void)
{
	return (BG_R << 24 | BG_G << 16 | BG_B << 8 | 255);
}

void	draw_sphere(mlx_image_t *img, t_data *data)
{
	int			h;
	int			w;
	t_ray		ray;
	t_point		hitpoint;

	colormaker(&data->ambient.color);
	colormaker(data->objects[0].color);
	w = -1;
	while (++w < (int) img->width)
	{
		h = -1;
		while (++h < (int) img->height)
		{
			ray = init_ray(data, img, h, w);
			hitpoint = sphere_intersection(ray, data->objects[0].sphere);
			if (hit_nothing(hitpoint))
				mlx_put_pixel(img, w, h, bg_color());
			else
				mlx_put_pixel(img, w, h, data->objects[0].color->mlxcolor);
		}
	}
}

int	test(t_data *data)
{
	mlx_image_t	*img;

	setup_window(&data->mlx);
	colormaker(&data->ambient.color);
	img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	apply_ambience_light(data);
	draw_sphere(img, data);
	mlx_image_to_window(data->mlx, img, 0, 0);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
