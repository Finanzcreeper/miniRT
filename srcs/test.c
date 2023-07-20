#include "miniRT.h"

int main(void)
{
	ft_printf("%s\n", "Test that libft is linked correctly.");
	mlx_t	*mlx = mlx_init(200, 200, "miniRT", false);
	mlx_loop(mlx);
	return (0);
}
