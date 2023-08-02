#include "miniRT.h"

bool	parse_sphere(char **infos, int *idx, t_data *data)
{
	t_sphere	*obj;
	bool		success;

	obj = &data->objs[*idx].sp;
	data->objs[*idx].type = SPHERE;
	data->objs[*idx].color = &obj->color;
	data->objs[*idx].pt = &obj->center;
	if (ft_strarrlen(infos) != 4)
		ft_error(ERR_SP, true, data);
	if (!parse_point(infos[1], &obj->center))
		ft_error(ERR_SP, true, data);
	success = true;
	obj->diameter = ft_strtod(infos[2], &success);
	obj->r = obj->diameter / 2;
	if (!success)
		ft_error(ERR_SP, true, data);
	if (!parse_color(infos[3], &obj->color))
		ft_error(ERR_SP, true, data);
	return (++(*idx), true);
}

bool	parse_plane(char **infos, int *idx, t_data *data)
{
	t_plane	*obj;

	obj = &data->objs[*idx].pl;
	data->objs[*idx].type = PLANE;
	data->objs[*idx].color = &obj->color;
	data->objs[*idx].pt = &obj->point;
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

bool	parse_cylinder(char **infos, int *idx, t_data *data)
{
	t_cylinder	*obj;
	bool		success;

	obj = &data->objs[*idx].cy;
	data->objs[*idx].type = CYLINDER;
	data->objs[*idx].color = &obj->color;
	data->objs[*idx].pt = &obj->center;
	if (ft_strarrlen(infos) != 6)
		ft_error(ERR_CY, true, data);
	if (!parse_point(infos[1], &obj->center))
		ft_error(ERR_CY, true, data);
	if (!parse_vector(infos[2], &obj->o_vector))
		ft_error(ERR_CY, true, data);
	success = true;
	obj->diameter = ft_strtod(infos[3], &success);
	obj->height = ft_strtod(infos[4], &success);
	if (!success)
		ft_error(ERR_CY, true, data);
	if (!parse_color(infos[5], &obj->color))
		ft_error(ERR_CY, true, data);
	return (update_cy(obj), ++(*idx), true);
}
