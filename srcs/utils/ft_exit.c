#include "miniRT.h"

void	ft_error(char *msg, bool toexit, t_data *data)
{
	ft_putendl_fd("Error", STDERR);
	ft_putendl_fd(msg, STDERR);
	if (toexit)
		ft_exit(data, EXIT_FAILURE);
}

void	ft_exit(t_data *data, int status)
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
