#include "cub3d.h"

void	clean_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
            if (map->grid[i])
			    free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	if (map->doors)
	{
		free(map->doors);
		map->doors = NULL;
	}
}
