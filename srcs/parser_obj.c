#include "miniRT.h"

bool	parse_sphere(char **infos, int *idx, t_data *data)
{
	t_sphere	*obj;
	bool		success;

	obj = &data->objects[*idx].sphere;
	data->objects[*idx].type = SPHERE;
	if (ft_strarrlen(infos) != 4)
		ft_error(ERR_SP, true, data);
	if (!parse_point(infos[1], &obj->center))
		ft_error(ERR_SP, true, data);
	success = true;
	obj->diameter = ft_strtod(infos[2], &success);
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

	obj = &data->objects[*idx].cylinder;
	data->objects[*idx].type = CYLINDER;
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
	return (++(*idx), true);
}
