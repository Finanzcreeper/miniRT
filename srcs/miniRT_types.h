#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# include "MLX42/MLX42.h"
# include "stdbool.h"

typedef struct s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				mlxcolor;
}	t_color;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ambient
{
	bool	assigned;
	double	ratio;
	t_color	color;
}	t_ambient;

typedef struct s_camera
{
	bool		assigned;
	t_point		view;
	t_vector	orientation;
	int			fov;
}	t_camera;

typedef struct s_light
{
	bool	assigned;
	t_point	source;
	double	ratio;
	t_color	color;
}	t_light;

typedef struct s_sphere
{
	t_point	center;
	double	diameter;
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
	double		diameter;
	double		height;
	t_color		color;
}	t_cylinder;

typedef enum e_type
{
	INVALID,
	AMBIENT,
	CAMERA,
	LIGHT,
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

typedef struct s_data
{
	char		*file_content;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objects;
	int			n_obj;
	mlx_t		*mlx;
}	t_data;

#endif
