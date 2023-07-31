#include "miniRT.h"

#define SHADING_FACTOR	0.2

double	clamp(double val, double min, double max)
{
	return (fmax(min, fmin(max, val)));
}

uint32_t	mlxcolor(t_color color, double fr, t_data data, bool light)
{
	double	r;
	double	g;
	double	b;

	if (!light)
	{
		r = color.r * SHADING_FACTOR * (data.light.ratio);
		g = color.g * SHADING_FACTOR * (data.light.ratio);
		b = color.b * SHADING_FACTOR * (data.light.ratio);
	}
	else
	{
		r = color.r * fr * (data.light.ratio);
		g = color.g * fr * (data.light.ratio);
		b = color.b * fr * (data.light.ratio);
	}
	r = fmax(COLOR_MIN, fmin(COLOR_MAX, r + data.ambient.ratio * data.ambient.color.r));
	g = fmax(COLOR_MIN, fmin(COLOR_MAX, g + data.ambient.ratio * data.ambient.color.g));
	b = fmax(COLOR_MIN, fmin(COLOR_MAX, b + data.ambient.ratio * data.ambient.color.b));
	return ((int) r << 24 | (int) g << 16 | (int) b << 8 | (int) color.a);
}

// void	colormixer(t_ray *ray)
// {
// 	if (!ray->light)
// 	{
// 		ray->color.r = ray->color.r * SHADING_FACTOR;
// 		ray->color.g = ray->color.g * SHADING_FACTOR;
// 		ray->color.b = ray->color.b * SHADING_FACTOR;
// 	}
// 	else
// 	{
// 		r = color.r + fr * data.light.color.r * data.light.ratio * 0.5;
// 		g = color.g + fr * data.light.color.g * data.light.ratio * 0.5;
// 		b = color.b + fr * data.light.color.b * data.light.ratio * 0.5;
// 	}
// }


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
			f = 0;
		}
		while (h < img->height)
		{
			//mlx_put_pixel(img, c, h++, mlxcolor(data->ambient.color, 1, true));
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
	//mlx_get_monitor_size(0, &width, &height);
	//mlx_set_window_size(*mlx, width, height);
}

uint32_t	bg_color(void)
{
	return (BG_R << 24 | BG_G << 16 | BG_B << 8 | BG_A);
}

void	draw_img(mlx_image_t *img, t_data *data)
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
}

int	test(t_data *data)
{
	mlx_image_t	*img;

	setup_window(&data->mlx);
	img = mlx_new_image(data->mlx, data->mlx->width, data->mlx->height);
	//apply_ambience_light(data);
	draw_img(img, data);
	mlx_image_to_window(data->mlx, img, 0, 0);
	mlx_close_hook(data->mlx, &ft_close_hook, data);
	mlx_key_hook(data->mlx, &ft_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
