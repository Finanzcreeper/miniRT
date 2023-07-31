#ifndef MINIRT_TYPES_H
# define MINIRT_TYPES_H

# include "MLX42/MLX42.h"
# include "stdbool.h"

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
	double	a;
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
	double	radius;
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
	t_point		top;
	t_point		bottom;
	t_vector	vector;
	double		diameter;
	double		radius;
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
	t_color	*color;
	t_point	*pt;
	union
	{
		t_sphere	sp;
		t_plane		pl;
		t_cylinder	cy;
	};
}	t_object;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
	t_color		color;
	bool		light;
	bool		in_obj;
	double		t_obj;
	double		t_light;
	double		fr;
}	t_ray;

typedef struct s_quadeq
{
	double	a;
	double	b;
	double	c;
	double	t1;
	double	t2;
	double	tmin;
	double	discriminant;
}	t_quadeq;

typedef enum e_axis
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z
}	t_axis;

typedef enum e_action
{
	TRANSLATION,
	ROTATION,
	INCREMENT,
	DECREMENT
}	t_action;

typedef struct s_data
{
	char		*file_content;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_object	*objs;
	int			n_obj;
	mlx_t		*mlx;
	mlx_image_t	*img;
	char		**lines;
	char		**infos;
	int			idx;
	int			axis;
	int			action;
}	t_data;

#endif
