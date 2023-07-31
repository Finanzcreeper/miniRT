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
t_ray		init_shadow_ray(t_point origin, t_vector direction);
int			ft_strarrlen(char **arr);
void		ft_strarrfree(char **arr);
void		ft_error(char *msg, bool toexit, t_data *data);
void		ft_exit(t_data *data, int status);
void		ft_free(t_data *data);
void		ft_close_hook(void *param);
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
t_vector	point_diff(t_point p1, t_point p2);
double		vec_dot(t_vector v1, t_vector v2);
t_vector	vec_cross(t_vector v1, t_vector v2);
t_vector	vec_normalize(t_vector v);
t_vector	vec_negate(t_vector v);
void		solve_quadeq(t_quadeq *eq);
t_point		get_hitpoint(t_ray ray, double t);
void		hit_sphere(t_ray *ray, t_sphere *sphere, t_data *data, int idx);
void		hit_plane(t_ray *ray, t_plane *plane, t_data *data, int idx);

bool		in_light(t_data *data, t_point hitpoint, int idx);

bool		block_sphere(t_ray *ray, t_sphere *sphere);
bool		block_plane(t_ray *ray, t_plane *plane);
bool		block_cylinder(t_ray *ray, t_cylinder *cylinder);
void		intersection(t_ray *ray, t_data *data);

double		sphere_facing_ratio(t_point hitpoint, t_sphere sphere, t_light light);
double		plane_facing_ratio(t_point hitpoint, t_plane plane, t_light light);
double		cy_fr_side(t_point hitpoint, t_cylinder cy, t_light light);
double		cy_fr_top(t_point hitpoint, t_cylinder cy, t_light light);
double		cy_fr_bottom(t_point hitpoint, t_cylinder cy, t_light light);

void		ft_keyhook(mlx_key_data_t keydata, void *param);

/* Testing. */
int			test(t_data *data);

#endif
