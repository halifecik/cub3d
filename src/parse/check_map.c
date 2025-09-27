/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:40 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/27 21:06:00 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	check_chars(char **grid, int height)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (i < height)
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S' || grid[i][j] == 'E'
				|| grid[i][j] == 'W')
				player_count++;
			else if (!ft_is_whitespace(grid[i][j]) && grid[i][j] != '0'
				&& grid[i][j] != '1' && grid[i][j] != 'D')
				return (ft_print_error("Invalid character in map"));
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (ft_print_error("Map must have exactly one player"));
	return (0);
}

static int	find_player_start(t_map *map, char **grid, int height)
{
	int	i;
	int	j;
	int	found;

	found = 0;
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (grid[i][++j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S' || grid[i][j] == 'E'
				|| grid[i][j] == 'W')
			{
				map->player_x = j;
				map->player_y = i;
				map->player_dir = grid[i][j];
				found++;
			}
		}
	}
	if (found != 1)
		return (ft_print_error("Must only have singular player"));
	return (0);
}

static int	flood_fill(char **grid, int x, int y, int height)
{
	int	width;

	if (!grid || x < 0 || y < 0 || y >= height)
		return (1);
	width = (int)ft_strlen(grid[y]);
	if (x >= width)
		return (1);
	if (grid[y][x] == ' ')
		return (1);
	if (grid[y][x] != '0' && grid[y][x] != 'N' && grid[y][x] != 'S'
		&& grid[y][x] != 'E' && grid[y][x] != 'W' && grid[y][x] != 'D')
		return (0);
	if (x == 0 || y == 0 || y == height - 1 || x == width - 1)
		return (1);
	grid[y][x] = 'F';
	if (flood_fill(grid, x + 1, y, height) || flood_fill(grid, x - 1, y, height)
		|| flood_fill(grid, x, y + 1, height) || flood_fill(grid, x, y - 1,
			height))
		return (1);
	return (0);
}

int	ft_check_map(t_map *map)
{
	int		cpy_height;
	char	**cpy_map;

	if (!map || !map->grid)
		return (ft_print_error("Empty map"));
	cpy_map = ft_copy_map_lines(map, &cpy_height);
	if (!cpy_map)
		return (ft_print_error("Map lines dosent exist"));
	if (check_chars(cpy_map, cpy_height))
		return (ft_free_grid(cpy_map), 1);
	if (find_player_start(map, cpy_map, cpy_height))
		return (ft_free_grid(cpy_map), 1);
	map->grid[map->player_y + map->map_index][map->player_x] = '0';
	if (flood_fill(cpy_map, map->player_x, map->player_y, cpy_height))
	{
		ft_free_grid(cpy_map);
		return (ft_print_error("Map must be closed with walls"));
	}
	ft_free_grid(cpy_map);
	return (0);
}
