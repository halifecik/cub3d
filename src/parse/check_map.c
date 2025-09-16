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

static int	check_chars(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < (int)ft_strlen(map->grid[i]))
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
				map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
				player_count++;
			else if (map->grid[i][j] != '0' && map->grid[i][j] != '1' &&
				map->grid[i][j] != ' ')
				return (ft_print_error("Invalid character in map"));
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (ft_print_error("Map must have exactly one player start"));
	return (0);
}

static int	find_player_start(t_map *map, int *player_x, int *player_y)
{
	int	i;
	int	j;
	int	found;

	i = -1;
	found = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < (int)ft_strlen(map->grid[i]))
		{
			if (map->grid[i][j] == 'N' || map->grid[i][j] == 'S' ||
				map->grid[i][j] == 'E' || map->grid[i][j] == 'W')
			{
				*player_x = j;
				*player_y = i;
				found++;
			}
		}
	}
	if (found == 0)
		return (ft_print_error("No player start found"));
	if (found > 1)
		return (ft_print_error("Multiple player starts found"));
	return (0);
}

static int	flood_fill(char **grid, int x, int y, t_map *map)
{
	int	width;

	if (!grid || x < 0 || y < 0 || y >= map->height)
		return (1);
	width = (int)ft_strlen(grid[y]);
	if (x >= width)
		return (1);
	if (grid[y][x] != '0' && grid[y][x] != 'N' && grid[y][x] != 'S' &&
		grid[y][x] != 'E' && grid[y][x] != 'W')
		return (0);
	if (x == 0 || y == 0 || y == map->height - 1 || x == width - 1)
		return (1);
	grid[y][x] = 'F';
	if (flood_fill(grid, x + 1, y, map)
		|| flood_fill(grid, x - 1, y, map)
		|| flood_fill(grid, x, y + 1, map)
		|| flood_fill(grid, x, y - 1, map))
		return (1);
	return (0);
}

int	ft_check_map(t_map *map)
{
	int		player_x;
	int		player_y;
	char	**grid_copy;

	if (!map || !map->grid)
		return (ft_print_error("Empty map"));
	if (check_chars(map))
		return (1);
	if (find_player_start(map, &player_x, &player_y))
		return (1);
	grid_copy = copy_grid(map->grid, map->height);
	if (!grid_copy)
		return (ft_print_error("Malloc fail"));
	if (flood_fill(grid_copy, player_x, player_y, map))
	{
		free_grid(grid_copy);
		return (ft_print_error("Map not closed by walls"));
	}
	free_grid(grid_copy);
	return (0);
}
