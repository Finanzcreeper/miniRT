#include "miniRT.h"

// uint32_t	mlxcolor(t_color color, double fr, t_data data, bool light)
// {
// 	double	r;
// 	double	g;
// 	double	b;

// 	if (!light)
// 	{
// 		r = 0;
// 		g = 0;
// 		b = 0;
// 	}
// 	else
// 	{
// 		r = color.r * fr * (data.light.ratio);
// 		g = color.g * fr * (data.light.ratio);
// 		b = color.b * fr * (data.light.ratio);
// 	}
// 	r = fmax(COLOR_MIN, fmin(COLOR_MAX, r + data.ambient.ratio
// 				* (data.ambient.color.r + color.r) / 2));
// 	g = fmax(COLOR_MIN, fmin(COLOR_MAX, g + data.ambient.ratio
// 				* (data.ambient.color.g + color.g) / 2));
// 	b = fmax(COLOR_MIN, fmin(COLOR_MAX, b + data.ambient.ratio
// 				* (data.ambient.color.b + color.b) / 2));
// 	return ((int) r << 24 | (int) g << 16 | (int) b << 8 | (int) color.a);
// }

uint32_t	mlxcolor(t_color color, double fr, t_data data, bool light)
{
	double	r;
	double	g;
	double	b;
	double	a;

	if (!light)
	{
		r = ((color.r * 1 / 255) * data.ambient.color.r);
		g = ((color.g * 1 / 255) * data.ambient.color.g);
		b = ((color.b * 1 / 255) * data.ambient.color.b);
		a = fmin(COLOR_MAX, (color.a * data.ambient.ratio));
	}
	else
	{
		r = fmin(COLOR_MAX, ((color.r * 1 / 255) * data.light.color.r) + ((color.r * 1 / 255) * data.ambient.color.r));
		g = fmin(COLOR_MAX, ((color.g * 1 / 255) * data.light.color.g) + ((color.g * 1 / 255) * data.ambient.color.g));
		b = fmin(COLOR_MAX, ((color.b * 1 / 255) * data.light.color.b) + ((color.b * 1 / 255) * data.ambient.color.b));
		a = fmin(COLOR_MAX, ((color.a * fr * data.light.ratio)
					+ (color.a * data.ambient.ratio)));
	}
	return ((int) r << 24 | (int) g << 16 | (int) b << 8 | (int) a);
}
