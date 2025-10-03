/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boundary_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:33:53 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/03 19:43:53 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_boundary_condition(char **grid, int height, int index_x,
		int index_y)
{
	int	i;
	int	j;
	int	width;

	i = index_x;
	j = index_y;
	width = (int)ft_strlen(grid[i]);
	if (grid[i][j] == '0' || grid[i][j] == 'N' || grid[i][j] == 'S'
		|| grid[i][j] == 'E' || grid[i][j] == 'W' || grid[i][j] == 'X'
		|| grid[i][j] == 'D')
	{
		if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
			return (1);
		if ((j > 0 && grid[i][j - 1] == ' ') || (j < width - 1 && grid[i][j
				+ 1] == ' ') || (i > 0 && j < (int)ft_strlen(grid[i - 1])
				&& grid[i - 1][j] == ' ') || (i < height - 1
				&& j < (int)ft_strlen(grid[i + 1]) && grid[i + 1][j] == ' '))
			return (1);
	}
	return (0);
}

int	ft_check_boundary_zeros(char **grid, int height)
{
	int	i;
	int	j;
	int	width;

	i = -1;
	while (++i < height)
	{
		if (!grid[i])
		{
			i++;
			continue ;
		}
		width = (int)ft_strlen(grid[i]);
		j = -1;
		while (++j < width)
		{
			if (ft_boundary_condition(grid, height, i, j))
				return (1);
		}
	}
	return (0);
}
