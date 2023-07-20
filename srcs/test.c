#include "miniRT.h"

void	colormaker(t_color *color)
{
	color->mlxcolor = (color->r << 24 | color->g << 16 | color->b << 8 | 255);
}

void	draw(mlx_image_t *img, int color)
{
	unsigned int	c;

	c = 0;
	while (c < img->width)
		mlx_put_pixel(img, c++, img->height / 2, color);
}

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
	mlx_t		*mlx;
	mlx_image_t	*img;

	setup_window(&mlx);
	data->ambient.color.r = 255;
	data->ambient.color.g = 255;
	data->ambient.color.b = 255;
	colormaker(&data->ambient.color);
	img = mlx_new_image(mlx, mlx->width, mlx->height);
	draw(img, data->ambient.color.mlxcolor);
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
