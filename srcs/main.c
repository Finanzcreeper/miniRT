#include "miniRT.h"

// move to utils/libft later
static void	ft_error(char *msg, bool exit, t_data *data)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	if (!exit)
		return ;
	if (data && data->mlx)
		mlx_terminate(data->mlx);
	exit(EXIT_FAILURE);
}

// any error will call ft_error to exit in place
static void	init_data(char *file, t_data *data)
{

}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		ft_error("Wrong number of arguments!", true, NULL);
	init_data(av[1], &data);
	return (EXIT_SUCCESS);
}
