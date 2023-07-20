#include "miniRT.h"

// move to utils/libft later
static void	ft_error(char *msg, bool toexit, t_data *data)
{
	ft_putendl_fd("Error", STDERR);
	ft_putendl_fd(msg, STDERR);
	if (!toexit)
		return ;
	if (data && data->mlx)
		mlx_terminate(data->mlx);
	exit(EXIT_FAILURE);
}

// any error will call ft_error to exit in place
static void	init_data(char *file, t_data *data)
{
	const char	*ext = ft_strrchr(file, '.');
	char		*content;

	if (!ext || ft_strncmp(ext, SCENE_EXT, ft_strlen(SCENE_EXT)))
		ft_error(ERR_EXT, true, NULL);
	content = ft_read_file(file);
	if (!content)
		;
	(void) data;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_error(ERR_ARG, true, NULL);
	init_data(av[1], &data);
	return (EXIT_SUCCESS);
}
