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
t_ray		init_shadow_ray(t_point origin, t_vec direction);
void		init_context(t_data *data);
int			ft_strarrlen(char **arr);
void		ft_strarrfree(char **arr);
void		ft_error(char *msg, bool toexit, t_data *data);
void		ft_exit(t_data *data, int status);
void		ft_free(t_data *data);
void		ft_close_hook(void *param);
void		ft_keyhook(mlx_key_data_t keydata, void *param);
void		ft_scrollhook(double xdelta, double ydelta, void *param);
void		ft_resizehook(int32_t width, int32_t height, void *param);
double		ft_strtod(char *nbr, bool *success);
char		*ft_read_file(const char *filename);
uint32_t	bg_color(void);

/* Parser. */
int			obj_count(char *content);
t_type		parse_type(char *s);
bool		parse_vector(char *s, t_vec *vector);
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
t_vec		point_diff(t_point p1, t_point p2);
t_vec		vec_diff(t_vec v1, t_vec v2);
double		vec_len(t_vec v);
double		vec_dot(t_vec v1, t_vec v2);
t_vec		vec_cross(t_vec v1, t_vec v2);
t_vec		vec_normalize(t_vec v);
t_vec		vec_negate(t_vec v);
t_vec		rotate_x(t_vec vec, t_action action);
t_vec		rotate_y(t_vec vec, t_action action);
t_vec		rotate_z(t_vec vec, t_action action);
void		solve_quadeq(t_quadeq *eq);
void		update_cy(t_cylinder *obj);
t_point		get_hitpoint(t_ray ray, double t);
void		hit_sphere(t_ray *ray, t_sphere *sphere, t_data *data);
void		hit_plane(t_ray *ray, t_plane *plane, t_data *data);
void		hit_cylinder(t_ray *ray, t_cylinder *cy, t_data *data);
void		hit_cy_disk(t_ray *ray, t_cylinder *cy, t_data *data);
void		intersection(t_ray *ray, t_data *data);
bool		in_light(t_data *data, t_point hp);
double		sp_facing_ratio(t_point hp, t_sphere sp, t_light light);
double		pl_facing_ratio(t_point hitpoint, t_plane plane, t_light light);
double		cy_fr_side(t_point hitpoint, t_cylinder cy, t_light light);
double		cy_fr_top(t_point hitpoint, t_cylinder cy, t_light light);
double		cy_fr_bottom(t_point hitpoint, t_cylinder cy, t_light light);
void		cy_quadeq(t_quadeq *eq, t_ray *ray, t_cylinder *cy, t_vec oc);
void		translation(t_point *pt, t_action act, int key, t_object *obj);
void		rotation(t_vec *vec, t_action act, int key, t_object *obj);
void		increment_rerender(t_data *data, int key);
void		decrement_rerender(t_data *data, int key);
void		render(mlx_image_t *img, t_data *data);
bool		adjust_camera(t_action action, t_data *data, int key);
bool		adjust_light(t_action action, t_data *data, int key);
void		update_controlled(t_data *data, int idx);
void		check_inside(t_data *data);
uint32_t	mlxcolor(t_color color, double fr, t_data data, bool light);

#endif
