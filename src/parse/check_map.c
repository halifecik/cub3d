#include "cub3d.h"

int	ft_cub_extension(char *filename)
{
	size_t	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) == 0)
		return (0);
	return (1);
}

