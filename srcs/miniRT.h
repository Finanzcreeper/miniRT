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

int			ft_strarrlen(char **arr);
void		ft_strarrfree(char **arr);

void		ft_error(char *msg, bool toexit, t_data *data);
char		*ft_read_file(const char *filename);
int			obj_count(char *content);
double		ft_strtod(char *nbr, bool *success);
t_type		parse_type(char *s);
bool		parse_vector(char *s, t_vector *vector);
bool		parse_point(char *s, t_point *point);
bool		parse_color(char *s, t_color *color);
void		parse_content(t_data *data, char *content);
bool		parse_ambient(char **infos, t_data *data);
bool		parse_camera(char **infos, t_data *data);
bool		parse_light(char **infos, t_data *data);
bool		parse_sphere(char **infos, int *idx, t_data *data);
bool		parse_plane(char **infos, int *idx, t_data *data);
bool		parse_cylinder(char **infos, int *idx, t_data *data);

void		free_exit(t_data *data, int status);

//testing
int			test(t_data *data);

#endif
