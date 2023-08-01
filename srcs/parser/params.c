#include "miniRT.h"

bool	parse_ambient(char **infos, t_data *data)
{
	bool	success;

	if (data->ambient.assigned == true)
		ft_error(ERR_DUPA, true, data);
	if (ft_strarrlen(infos) != 3)
		ft_error(ERR_INFOA, true, data);
	success = true;
	data->ambient.ratio = ft_strtod(infos[1], &success);
	if (!success || data->ambient.ratio < 0 || data->ambient.ratio > 1)
		ft_error(ERR_INFOA, true, data);
	if (!parse_color(infos[2], &data->ambient.color))
		ft_error(ERR_INFOA, true, data);
	data->ambient.assigned = true;
	return (true);
}

bool	parse_camera(char **infos, t_data *data)
{
	int	i;

	if (data->camera.assigned == true)
		ft_error(ERR_DUPC, true, data);
	if (ft_strarrlen(infos) != 4)
		ft_error(ERR_INFOC, true, data);
	if (!parse_point(infos[1], &data->camera.view))
		ft_error(ERR_INFOC, true, data);
	if (!parse_vector(infos[2], &data->camera.orientation))
		ft_error(ERR_INFOC, true, data);
	i = -1;
	while (infos[3][++i])
		if (!ft_isdigit(infos[3][i]))
			ft_error(ERR_INFOC, true, data);
	data->camera.fov = ft_atoi(infos[3]);
	if (data->camera.fov < 0 || data->camera.fov > 180)
		ft_error(ERR_INFOC, true, data);
	data->camera.assigned = true;
	return (true);
}

bool	parse_light(char **infos, t_data *data)
{
	bool	success;

	if (data->light.assigned == true)
		ft_error(ERR_DUPL, true, data);
	if (ft_strarrlen(infos) != 4)
		ft_error(ERR_INFOL, true, data);
	if (!parse_point(infos[1], &data->light.source))
		ft_error(ERR_INFOL, true, data);
	success = true;
	data->light.ratio = ft_strtod(infos[2], &success);
	if (!success || data->light.ratio < 0 || data->light.ratio > 1)
		ft_error(ERR_INFOL, true, data);
	if (!parse_color(infos[3], &data->light.color))
		ft_error(ERR_INFOL, true, data);
	data->light.assigned = true;
	return (true);
}
