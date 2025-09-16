#include "cub3d.h"

int	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	ft_rtrim(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && is_space(line[i]))
	{
		line[i] = '\0';
		i--;
	}
}
