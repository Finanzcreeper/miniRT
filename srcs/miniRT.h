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
double		vec_len(t_vector v);
double		vec_dot(t_vector v1, t_vector v2);
t_vector	vec_cross(t_vector v1, t_vector v2);
t_vector	vec_normalize(t_vector v);
t_vector	vec_negate(t_vector v);
t_vector	rotate_x(t_vector vec, t_action action);
t_vector	rotate_y(t_vector vec, t_action action);
t_vector	rotate_z(t_vector vec, t_action action);
void		solve_quadeq(t_quadeq *eq);
t_point		get_hitpoint(t_ray ray, double t);
void		hit_sphere(t_ray *ray, t_sphere *sphere, t_data *data, int idx);
void		hit_plane(t_ray *ray, t_plane *plane, t_data *data, int idx);

bool		in_light(t_data *data, t_point hitpoint, int idx);

bool		block_sphere(t_ray *ray, t_sphere *sphere, t_data *data);
bool		block_plane(t_ray *ray, t_plane *plane, t_data *data);
bool		block_cylinder(t_ray *ray, t_cylinder *cylinder, t_data *data);
void		hit_cylinder(t_ray *ray, t_cylinder *cy, t_data *data, int idx);
void		intersection(t_ray *ray, t_data *data);
void		update_cy(t_cylinder *obj);
double		sp_facing_ratio(t_point hitpoint, t_sphere sphere, t_light light);
double		pl_facing_ratio(t_point hitpoint, t_plane plane, t_light light);
double		cy_fr_side(t_point hitpoint, t_cylinder cy, t_light light);
double		cy_fr_top(t_point hitpoint, t_cylinder cy, t_light light);
double		cy_fr_bottom(t_point hitpoint, t_cylinder cy, t_light light);

void		ft_keyhook(mlx_key_data_t keydata, void *param);

void		translation(t_point *pt, t_action act, t_axis axis, t_object *obj);
void		rotation(t_vector *vec, t_action act, t_axis axis, t_object *obj);
void		increment_rerender(t_data *data, t_axis axis);
void		decrement_rerender(t_data *data, t_axis axis);
void		render(mlx_image_t *img, t_data *data);
bool		adjust_camera(t_action action, t_data *data, t_axis axis);
bool		adjust_light(t_action action, t_data *data, t_axis axis);
uint32_t	mlxcolor(t_color color, double fr, t_data data, bool light);

void		cy_quadeq(t_quadeq *eq, t_ray *ray, t_cylinder *cy, t_vector oc);

/* Testing. */
int			test(t_data *data);
void		ft_scrollhook(double xdelta, double ydelta, void *param);
void		init_context(t_data *data);
void		update_controlled(t_data *data, int idx);

#endif
