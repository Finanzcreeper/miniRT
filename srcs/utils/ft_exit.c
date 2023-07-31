#include "miniRT.h"

void	ft_error(char *msg, bool toexit, t_data *data)
{
	ft_putendl_fd("Error", STDERR);
	ft_putendl_fd(msg, STDERR);
	if (toexit)
		ft_exit(data, EXIT_FAILURE);
}

void	ft_free(t_data *data)
{
	if (data && data->file_content)
		free(data->file_content);
	if (data && data->objs)
		free(data->objs);
	if (data && data->lines)
		ft_strarrfree(data->lines);
	if (data && data->infos)
		ft_strarrfree(data->infos);
}

void	ft_exit(t_data *data, int status)
{
	ft_free(data);
	if (data && data->mlx)
		mlx_terminate(data->mlx);
	exit(status);
}

void	ft_close_hook(void *param)
{
	t_data	*data;

	data = param;
	ft_free(data);
}
