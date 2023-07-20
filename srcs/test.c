/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:35:27 by nreher            #+#    #+#             */
/*   Updated: 2023/07/20 04:38:29 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int main(void)
{
	ft_printf("%s\n", "Test that libft is linked correctly.");
	mlx_t	*mlx = mlx_init(200, 200, "miniRT", false);
	mlx_loop(mlx);
	return (0);
}
