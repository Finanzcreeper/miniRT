#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "miniRT_types.h"
# include "miniRT_defines.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>

/* Utils. */
void		init_data(t_data *data);
t_ray		init_ray(t_data *data, mlx_image_t *img, int height, int width);
int			ft_strarrlen(char **arr);
void		ft_strarrfree(char **arr);
void		ft_error(char *msg, bool toexit, t_data *data);
void		ft_exit(t_data *data, int status);
double		ft_strtod(char *nbr, bool *success);
char		*ft_read_file(const char *filename);

/* Parser. */
int			obj_count(char *content);
t_type		parse_type(char *s);
bool		parse_vector(char *s, t_vector *vector);
bool		parse_point(char *s, t_point *point);
bool		parse_color(char *s, t_color *color);
bool		parse_ambient(char **infos, t_data *data);
bool		parse_camera(char **infos, t_data *data);
bool		parse_light(char **infos, t_data *data);
bool		parse_sphere(char **infos, int *idx, t_data *data);
bool		parse_plane(char **infos, int *idx, t_data *data);
bool		parse_cylinder(char **infos, int *idx, t_data *data);
void		parse_content(t_data *data, char *content);

/* Calculations. */
t_vector	point_diff(t_point v1, t_point v2);
double		vec_dot(t_vector v1, t_vector v2);
t_vector	vec_cross(t_vector v1, t_vector v2);
t_vector	vec_normalize(t_vector v);
void		solve_quadeq(t_quadeq *eq);
t_point		get_hitpoint(t_ray ray, double t);
t_point		sphere_intersection(t_ray ray, t_sphere sphere);
bool		hit_nothing(t_point point);

/* Testing. */
int			test(t_data *data);

#endif
