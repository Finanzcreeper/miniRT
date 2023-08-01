#include "miniRT.h"

bool	parse_line(char *line, t_data *data, int *idx)
{
	t_type	type;

	if (data->infos)
		ft_strarrfree(data->infos);
	data->infos = ft_split(line, ' ');
	if (!data->infos || !data->infos[0])
		return (ft_strarrfree(data->infos), data->infos = NULL, false);
	type = parse_type(data->infos[0]);
	if (type == INVALID)
		ft_error(ERR_TYPE, true, data);
	if (type == AMBIENT)
		return (parse_ambient(data->infos, data));
	if (type == CAMERA)
		return (parse_camera(data->infos, data));
	if (type == LIGHT)
		return (parse_light(data->infos, data));
	if (type == SPHERE)
		return (parse_sphere(data->infos, idx, data));
	if (type == PLANE)
		return (parse_plane(data->infos, idx, data));
	if (type == CYLINDER)
		return (parse_cylinder(data->infos, idx, data));
	return (false);
}

void	parse_content(t_data *data, char *content)
{
	int		i;
	int		idx;

	data->lines = ft_split(content, '\n');
	i = -1;
	idx = 0;
	while (data->lines[++i])
		parse_line(data->lines[i], data, &idx);
	if (!data->ambient.assigned || !data->light.assigned
		|| !data->camera.assigned)
		ft_error(ERR_MISS, true, data);
	ft_strarrfree(data->lines);
	data->lines = NULL;
}
