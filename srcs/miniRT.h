#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "miniRT_types.h"
# include "miniRT_defines.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>

char	*ft_read_file(const char *filename);

//testing
int		test(t_data *data);

#endif
