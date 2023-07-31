#include "miniRT.h"

bool	parse_sphere(char **infos, int *idx, t_data *data)
{
	t_sphere	*obj;
	bool		success;

	obj = &data->objects[*idx].sphere;
	data->objects[*idx].type = SPHERE;
	data->objects[*idx].color = &obj->color;
	if (ft_strarrlen(infos) != 4)
		ft_error(ERR_SP, true, data);
	if (!parse_point(infos[1], &obj->center))
		ft_error(ERR_SP, true, data);
	success = true;
	obj->diameter = ft_strtod(infos[2], &success);
	obj->radius = obj->diameter / 2;
	if (!success)
		ft_error(ERR_SP, true, data);
	if (!parse_color(infos[3], &obj->color))
		ft_error(ERR_SP, true, data);
	return (++(*idx), true);
}

bool	parse_plane(char **infos, int *idx, t_data *data)
{
	t_plane	*obj;

	obj = &data->objects[*idx].plane;
	data->objects[*idx].type = PLANE;
	data->objects[*idx].color = &obj->color;
	if (ft_strarrlen(infos) != 4)
		ft_error(ERR_PL, true, data);
	if (!parse_point(infos[1], &obj->point))
		ft_error(ERR_PL, true, data);
	if (!parse_vector(infos[2], &obj->vector))
		ft_error(ERR_PL, true, data);
	if (!parse_color(infos[3], &obj->color))
		ft_error(ERR_PL, true, data);
	return (++(*idx), true);
}

void	calc_cylinder(t_cylinder *obj)
{
	obj->radius = obj->diameter / 2;
	obj->top.x = obj->center.x + obj->vector.x * obj->height / 2;
	obj->top.y = obj->center.y + obj->vector.y * obj->height / 2;
	obj->top.z = obj->center.z + obj->vector.z * obj->height / 2;
	obj->vector = vec_negate(obj->vector);
	obj->bottom.x = obj->top.x + obj->vector.x * obj->height;
	obj->bottom.y = obj->top.y + obj->vector.y * obj->height;
	obj->bottom.z = obj->top.z + obj->vector.z * obj->height;
}

bool	parse_cylinder(char **infos, int *idx, t_data *data)
{
	t_cylinder	*obj;
	bool		success;

	obj = &data->objects[*idx].cylinder;
	data->objects[*idx].type = CYLINDER;
	data->objects[*idx].color = &obj->color;
	if (ft_strarrlen(infos) != 6)
		ft_error(ERR_CY, true, data);
	if (!parse_point(infos[1], &obj->center))
		ft_error(ERR_CY, true, data);
	if (!parse_vector(infos[2], &obj->vector))
		ft_error(ERR_CY, true, data);
	success = true;
	obj->diameter = ft_strtod(infos[3], &success);
	obj->height = ft_strtod(infos[4], &success);
	if (!success)
		ft_error(ERR_CY, true, data);
	if (!parse_color(infos[5], &obj->color))
		ft_error(ERR_CY, true, data);
	return (calc_cylinder(obj), ++(*idx), true);
}
