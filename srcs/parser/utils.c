#include "miniRT.h"

static bool	is_dbl(char *nbr)
{
	int	digit;

	digit = 0;
	if (*nbr == '+' || *nbr == '-')
		++nbr;
	while (ft_isdigit(*nbr) && ++nbr)
		++digit;
	if (*nbr == '\0' && digit)
		return (true);
	if (*nbr != '.')
		return (false);
	++nbr;
	while (ft_isdigit(*nbr) && ++nbr)
		++digit;
	if (*nbr != '\0')
		return (false);
	return (true);
}

double	ft_strtod(char *nbr, bool *success)
{
	const char	sign = nbr[0];
	const int	integer = ft_atoi(nbr);
	double		fraction;
	double		factor;

	if (*success == false)
		return (0);
	if (!is_dbl(nbr))
		return (*success = false, 0);
	while (*nbr == '+' || *nbr == '-' || ft_isdigit(*nbr))
		++nbr;
	if (*nbr == '\0')
		return (*success = true, (double) integer);
	++nbr;
	factor = 0.1;
	fraction = 0.0;
	while (ft_isdigit(*nbr) && ++nbr)
	{
		fraction += (*(nbr - 1) - '0') * factor;
		factor *= 0.1;
	}
	if (integer >= 0 && sign != '-')
		return (*success = true, (double)(integer + fraction));
	return (*success = true, (double)(integer - fraction));
}

/* Count the number of objects of a given file content. */
int	obj_count(char *content)
{
	char	**lines;
	char	**infos;
	int		i;
	int		count;

	lines = ft_split(content, '\n');
	count = 0;
	i = -1;
	while (lines[++i])
	{
		infos = ft_split(lines[i], ' ');
		if (infos[0] && (parse_type(infos[0]) == SPHERE || parse_type(infos[0])
				== PLANE || parse_type(infos[0]) == CYLINDER))
			++count;
		ft_strarrfree(infos);
	}
	ft_strarrfree(lines);
	return (count);
}
