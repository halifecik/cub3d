/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:05:13 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/02 20:06:27 by hademirc         ###   ########.fr       */
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

int	ft_flood_fill(char **grid, int x, int y, int height)
{
	int	width;

	if (!grid || y < 0 || y >= height)
		return (1);
	if (!grid[y])
		return (1);
	width = (int)ft_strlen(grid[y]);
	if (x < 0 || x >= width)
		return (1);
	if (grid[y][x] == ' ')
		return (1);
	if (grid[y][x] == 'F' || grid[y][x] == '1')
		return (0);
	if (grid[y][x] != '0' && grid[y][x] != 'N' && grid[y][x] != 'S'
		&& grid[y][x] != 'E' && grid[y][x] != 'W')
		return (0);
	if (x == 0 || y == 0 || y == height - 1 || x == width - 1)
		return (1);
	grid[y][x] = 'F';
	if (ft_flood_fill(grid, x + 1, y, height) || ft_flood_fill(grid, x - 1, y,
			height) || ft_flood_fill(grid, x, y + 1, height)
		|| ft_flood_fill(grid, x, y - 1, height))
		return (1);
	return (0);
}

void	ft_mark_map(char **grid, int x, int y, int height)
{
	int	width;

	if (!grid || y < 0 || y >= height)
		return ;
	if (!grid[y])
		return ;
	width = (int)ft_strlen(grid[y]);
	if (x < 0 || x >= width)
		return ;
	if (grid[y][x] == 'M' || grid[y][x] == ' ')
		return ;
	if (grid[y][x] != '0' && grid[y][x] != '1' && grid[y][x] != 'N'
		&& grid[y][x] != 'S' && grid[y][x] != 'E' && grid[y][x] != 'W')
		return ;
	grid[y][x] = 'M';
	ft_mark_map(grid, x + 1, y, height);
	ft_mark_map(grid, x - 1, y, height);
	ft_mark_map(grid, x, y + 1, height);
	ft_mark_map(grid, x, y - 1, height);
}

int	ft_check_separated_map(char **grid, int height, t_map *map)
{
	int	i;
	int	j;
	int	map_regions;

	(void)map;
	map_regions = 0;
	i = -1;
	while (++i < height)
	{
		j = 0;
		while (grid[i][j])
		{
			if ((grid[i][j] == '0' || grid[i][j] == '1' || grid[i][j] == 'N'
					|| grid[i][j] == 'S' || grid[i][j] == 'E'
					|| grid[i][j] == 'W') && grid[i][j] != 'M')
			{
				map_regions++;
				if (map_regions > 1)
					return (ft_perror("Map contains separated areas"));
				ft_mark_map(grid, j, i, height);
			}
			j++;
		}
	}
	return (0);
}
