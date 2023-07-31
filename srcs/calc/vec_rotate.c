#include "miniRT.h"

t_vector	rotate_x(t_vector vec, t_action action)
{
	const double	radian = ROT_STEP * M_PI / 180;
	double			cos_rot;
	double			sin_rot;
	t_vector		ret;

	if (action == INCREMENT)
	{
		cos_rot = cos(radian);
		sin_rot = sin(radian);
	}
	else
	{
		cos_rot = cos(-radian);
		sin_rot = sin(-radian);
	}
	ret.x = vec.x;
	ret.y = vec.y * cos_rot - vec.z * sin_rot;
	ret.z = vec.y * sin_rot + vec.z * cos_rot;
	return (ret);
}

t_vector	rotate_y(t_vector vec, t_action action)
{
	const double	radian = ROT_STEP * M_PI / 180;
	double			cos_rot;
	double			sin_rot;
	t_vector		ret;

	if (action == INCREMENT)
	{
		cos_rot = cos(radian);
		sin_rot = sin(radian);
	}
	else
	{
		cos_rot = cos(-radian);
		sin_rot = sin(-radian);
	}
	ret.y = vec.y;
	ret.x = vec.x * cos_rot + vec.z * sin_rot;
	ret.z = -vec.x * sin_rot + vec.z * cos_rot;
	return (ret);
}

t_vector	rotate_z(t_vector vec, t_action action)
{
	const double	radian = ROT_STEP * M_PI / 180;
	double			cos_rot;
	double			sin_rot;
	t_vector		ret;

	if (action == INCREMENT)
	{
		cos_rot = cos(radian);
		sin_rot = sin(radian);
	}
	else
	{
		cos_rot = cos(-radian);
		sin_rot = sin(-radian);
	}
	ret.z = vec.z;
	ret.x = vec.x * cos_rot - vec.y * sin_rot;
	ret.y = vec.x * sin_rot + vec.y * cos_rot;
	return (ret);
}
