#include "miniRT.h"

uint32_t	mlxcolor(t_color color, double fr, t_data data, bool light)
{
	double	r;
	double	g;
	double	b;

	if (!light)
	{
		r = color.r * SHADOW_F * (data.light.ratio);
		g = color.g * SHADOW_F * (data.light.ratio);
		b = color.b * SHADOW_F * (data.light.ratio);
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
