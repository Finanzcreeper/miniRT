/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlu <dlu@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:25:53 by dlu               #+#    #+#             */
/*   Updated: 2023/07/19 18:59:16 by dlu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "MLX42/MLX42.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_color;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_vector
{
	int	x;
	int	y;
	int	z;
}	t_vector;

typedef struct s_ambient
{
	int		ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	t_point		view;
	t_vector	orientation;
	int			fov;
}	t_camera;

typedef struct s_light
{
	t_point	source;
	int		ratio;
	t_color	color;
}	t_light;

typedef struct s_sphere
{
	t_point	center;
	int		diameter;
	t_color	color;
}	t_sphere;

typedef struct s_plane
{
	t_point		point;
	t_vector	vector;
	t_color		color;
}	t_plane;

typedef struct s_cylinder
{
	t_point		center;
	t_vector	vector;
	int			diameter;
	int			height;
	t_color		color;
}	t_cylinder;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER
}	t_type;

typedef struct s_object
{
	int		type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
}	t_object;

typedef struct s_params
{
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
}	t_params;

#endif
