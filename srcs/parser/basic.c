#include "miniRT.h"

/* Parse a color in the format of R,G,B, returns whether it's successful. */
bool	parse_color(char *s, t_color *color)
{
	char	**parts;
	int		i;
	int		j;

	parts = ft_split(s, ',');
	if (!parts || ft_strarrlen(parts) != 3)
		return (ft_strarrfree(parts), false);
	i = -1;
	while (parts[++i])
	{
		j = -1;
		while (parts[i][++j])
			if (!ft_isdigit(parts[i][j]))
				return (ft_strarrfree(parts), false);
		if (ft_atoi(parts[i]) < 0 || ft_atoi(parts[i]) > 255)
			return (ft_strarrfree(parts), false);
	}
	color->r = (double) ft_atoi(parts[0]);
	color->g = (double) ft_atoi(parts[1]);
	color->b = (double) ft_atoi(parts[2]);
	color->a = (double) DEFAULT_A;
	return (ft_strarrfree(parts), true);
}

/* Parse a point in the format of x,y,z, returns whether it's successful. */
bool	parse_point(char *s, t_point *point)
{
	char	**parts;
	bool	success;

	parts = ft_split(s, ',');
	if (!parts || ft_strarrlen(parts) != 3)
		return (ft_strarrfree(parts), false);
	success = true;
	point->x = ft_strtod(parts[0], &success);
	point->y = ft_strtod(parts[1], &success);
	point->z = ft_strtod(parts[2], &success);
	if (!success)
		return (ft_strarrfree(parts), false);
	return (ft_strarrfree(parts), true);
}

/* Parse a normalized vector, returns whether it's successful. */
bool	parse_vector(char *s, t_vec *vector)
{
	char	**parts;
	bool	success;

	parts = ft_split(s, ',');
	if (!parts || ft_strarrlen(parts) != 3)
		return (ft_strarrfree(parts), false);
	success = true;
	vector->x = ft_strtod(parts[0], &success);
	vector->y = ft_strtod(parts[1], &success);
	vector->z = ft_strtod(parts[2], &success);
	if (!success || vector->x < -1 || vector->x > 1 || vector->y < -1
		|| vector->y > 1 || vector->z < -1 || vector->z > 1)
		return (ft_strarrfree(parts), false);
	return (ft_strarrfree(parts), true);
}

t_type	parse_type(char *s)
{
	if (ft_strlen(s) == 1 && ft_strncmp(s, "A", 1) == 0)
		return (AMBIENT);
	if (ft_strlen(s) == 1 && ft_strncmp(s, "C", 1) == 0)
		return (CAMERA);
	if (ft_strlen(s) == 1 && ft_strncmp(s, "L", 1) == 0)
		return (LIGHT);
	if (ft_strlen(s) == 2 && ft_strncmp(s, "sp", 2) == 0)
		return (SPHERE);
	if (ft_strlen(s) == 2 && ft_strncmp(s, "pl", 2) == 0)
		return (PLANE);
	if (ft_strlen(s) == 2 && ft_strncmp(s, "cy", 2) == 0)
		return (CYLINDER);
	return (INVALID);
}
