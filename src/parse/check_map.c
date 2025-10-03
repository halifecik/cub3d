/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:40 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/03 13:43:09 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_check_map_chars(char **grid, int height)
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
				&& grid[i][j] != '1' && grid[i][j] != 'D' && grid[i][j] != 'X')
				return (ft_perror("Invalid character in map"));
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (ft_perror("Map must have exactly one player"));
	return (0);
}

static int	ft_set_player_start(t_map *map, char **grid, int height)
{
	int	i;
	int	j;
	int	found;

	i = -1;
	found = 0;
	while (++i < height)
	{
		j = -1;
		while (grid[i][++j])
		{
			if (grid[i][j] == 'N' || grid[i][j] == 'S'
				|| grid[i][j] == 'E' || grid[i][j] == 'W')
			{
				map->player_x = j;
				map->player_y = i;
				map->player_dir = grid[i][j];
				found++;
			}
		}
	}
	if (found != 1)
		return (ft_perror("Must only have singular player"));
	map->grid[map->player_y + map->map_index][map->player_x] = '0';
	return (0);
}

static char	**ft_copy_map_lines(t_map *map, int *cpy_height)
{
	char	**copy;
	int		start;
	int		i;
	int		j;

	if (!map || !map->grid)
		return (NULL);
	start = ft_find_map_start(map);
	if (start == -1)
		return (NULL);
	map->map_index = start;
	*cpy_height = map->height - start;
	copy = ft_calloc(*cpy_height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = start;
	j = 0;
	while (i < map->height)
		copy[j++] = ft_strdup(map->grid[i++]);
	copy[j] = NULL;
	return (copy);
}

int	ft_check_map(t_map *map)
{
	int		cpy_height;
	char	**cpy_map;
	char	**sep_check_map;

	if (!map || !map->grid)
		return (ft_perror("Empty map"));
	cpy_map = ft_copy_map_lines(map, &cpy_height);
	if (!cpy_map)
		return (ft_perror("Map lines do not exist"));
	sep_check_map = ft_copy_map_lines(map, &cpy_height);
	if (!sep_check_map)
		return (ft_free_grid(cpy_map), ft_perror("Map lines do not exist"));
	if (ft_check_map_chars(cpy_map, cpy_height)
		|| ft_set_player_start(map, cpy_map, cpy_height)
		|| ft_check_boundary_zeros(cpy_map, cpy_height)
		|| ft_check_separated_map(sep_check_map, cpy_height, map)
		|| ft_flood_fill(cpy_map, map->player_x, map->player_y, cpy_height))
	{
		ft_free_grid(cpy_map);
		ft_free_grid(sep_check_map);
		return (ft_perror("Map must be valid and closed"));
	}
	ft_free_grid(cpy_map);
	ft_free_grid(sep_check_map);
	return (0);
}
