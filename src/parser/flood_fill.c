#include "cub3d.h"

static int	check_chars(t_map *map)
{
	int	x;
	int	y;
	char	c;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < (int)ft_strlen(map->grid[y]))
		{
			c = map->grid[y][x];
			if (!ft_strchr("01NSEW ", c))
				return (EXIT_FAILURE);
			x++;
		}
		y++;
	}
	return (EXIT_SUCCESS);
}

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
		while (x < (int)ft_strlen(map->grid[y]))
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

static void	flood_fill(t_map *map, int y, int x, int *valid)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
	{
		*valid = 0;
		return ;
	}
	if (map->grid[y][x] == '1' || map->grid[y][x] == 'F')
		return ;
	if (map->grid[y][x] == ' ')
	{
		*valid = 0;
		return ;
	}
	map->grid[y][x] = 'F';
	flood_fill(map, y + 1, x, valid);
	flood_fill(map, y - 1, x, valid);
	flood_fill(map, y, x + 1, valid);
	flood_fill(map, y, x - 1, valid);
}

static void	reset_flood_fill(t_map *map)
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

int	validate_map(t_map *map)
{
	int	valid;

	if (check_chars(map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (check_player(map) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	valid = 1;
	flood_fill(map, map->player_y, map->player_x, &valid);
	reset_flood_fill(map);
	if (!valid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
