#include "miniRT.h"

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
	data->objs = (t_object *) ft_calloc(data->n_obj, sizeof(t_object));
	if (!data->objs)
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
	data.mlx = mlx_init(WINDOW_W, WINDOW_H, "miniRT", true);
	data.img = mlx_new_image(data.mlx, data.mlx->width, data.mlx->height);
	data.time = mlx_get_time();
	render(data.img, &data);
	mlx_image_to_window(data.mlx, data.img, 0, 0);
	init_context(&data);
	mlx_key_hook(data.mlx, &ft_keyhook, &data);
	mlx_resize_hook(data.mlx, &ft_resizehook, &data);
	mlx_scroll_hook(data.mlx, &ft_scrollhook, &data);
	mlx_close_hook(data.mlx, &ft_close_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (EXIT_SUCCESS);
}
