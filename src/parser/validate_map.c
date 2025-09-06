#include "cub3d.h"

/* tüm geçerli karakterleri kontrol et */
static int	check_chars(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < ft_strlen(map->grid[y]))
		{
			if (!ft_strchr("01NSEW", map->grid[y][x]))
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

/* player kontrolü, sadece bir tane olmalı */
static int	check_player(t_map *map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < ft_strlen(map->grid[y]))
		{
			if (ft_strchr("NSEW", map->grid[y][x]))
			{
				map->player_x = x;
				map->player_y = y;
				map->player_dir = map->grid[y][x];
				count++;
			}
			x++;
		}
		y++;
	}
	if (count != 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/* map validasyonu */
int	validate_map(t_map *map)
{
	int	valid;

	if (check_chars(map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_player(map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	valid = 1;
	flood_fill_recursive(map, map->player_y, map->player_x, &valid);
	reset_flood_fill(map);
	if (!valid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}