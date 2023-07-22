#include "miniRT.h"

// move to utils/libft later
void	ft_error(char *msg, bool toexit, t_data *data)
{
	ft_putendl_fd("Error", STDERR);
	ft_putendl_fd(msg, STDERR);
	if (toexit)
		free_exit(data, EXIT_FAILURE);
}

void	free_exit(t_data *data, int status)
{
	if (data && data->file_content)
		free(data->file_content);
	if (data && data->objects)
		free(data->objects);
	if (data && data->lines)
		ft_strarrfree(data->lines);
	if (data && data->infos)
		ft_strarrfree(data->infos);
	if (data && data->mlx)
		mlx_terminate(data->mlx);
	exit(status);
}

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

static void	init_data(t_data *data)
{
	data->file_content = NULL;
	data->lines = NULL;
	data->infos = NULL;
	data->objects = NULL;
	data->mlx = NULL;
	data->ambient.assigned = false;
	data->camera.assigned = false;
	data->light.assigned = false;
	data->n_obj = 0;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_error(ERR_ARG, true, NULL);
	init_data(&data);
	load_data(av[1], &data);
	//test(&data);
	free_exit(&data, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
