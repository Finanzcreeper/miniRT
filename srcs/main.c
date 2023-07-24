#include "miniRT.h"

// any error will call ft_error to exit in place
static void	load_data(char *file, t_data *data)
{
	const char	*ext = ft_strrchr(file, '.');

	if (!ext || ft_strncmp(ext, SCENE_EXT, ft_strlen(SCENE_EXT)))
		ft_error(ERR_EXT, true, NULL);
	data->file_content = ft_read_file(file);
	if (!data->file_content)
		ft_error(ERR_OPEN, true, data);
	if (!*data->file_content)
		ft_error(ERR_EMPTY, true, data);
	data->n_obj = obj_count(data->file_content);
	data->objects = ft_calloc(data->n_obj, sizeof(t_object));
	if (!data->objects)
		ft_error(ERR_MALLOC, true, data);
	parse_content(data, data->file_content);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_error(ERR_ARG, true, NULL);
	init_data(&data);
	load_data(av[1], &data);
	test(&data);
	//ft_free(&data);
	return (EXIT_SUCCESS);
}
