#include "cub3d.h"

void	ft_flood_fill(t_map *map, int y, int x, int *valid)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
	{
		*valid = 0;
		return ;
	}
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'F')
		return ;
	if (map->grid[y][x] == '\0')
	{
		*valid = 0;
		return ;
	}
	map->grid[y][x] = 'F';
	ft_flood_fill(map, y + 1, x, valid);
	ft_flood_fill(map, y - 1, x, valid);
	ft_flood_fill(map, y, x + 1, valid);
	ft_flood_fill(map, y, x - 1, valid);
}

void	ft_reset_flood_fill(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->grid[y]))
		{
			if (map->grid[y][x] == 'F')
				map->grid[y][x] = '0';
			x++;
		}
		y++;
	}
}
