#include "miniRT.h"

// move to utils/libft later
static void	ft_error(char *msg, bool toexit, t_data *data)
{
	ft_putendl_fd("Error", STDERR);
	ft_putendl_fd(msg, STDERR);
	if (!toexit)
		return ;
	if (data && data->file_content)
		free(data->file_content);
	if (data && data->mlx)
		mlx_terminate(data->mlx);
	exit(EXIT_FAILURE);
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
}

static void	init_data(t_data *data)
{
	data->file_content = NULL;
	data->mlx = NULL;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_error(ERR_ARG, true, NULL);
	init_data(&data);
	load_data(av[1], &data);
	return (EXIT_SUCCESS);
}
