/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:35:43 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/23 16:22:45 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_is_map_line(char *line)
{
	int	j;
	int	valid;

	if (!line)
		return (0);
	j = 0;
	valid = 0;
	while (line[j])
	{
		if (line[j] == '0' || line[j] == '1' || line[j] == 'N'
			|| line[j] == 'S' || line[j] == 'E' || line[j] == 'W')
			valid = 1;
		else if (!ft_is_whitespace(line[j]))
			return (0);
		j++;
	}
	return (valid);
}

static int	find_map_start(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		if (ft_is_map_line(map->grid[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_copy_map_lines(t_map *map, int *cpy_height)
{
	char	**copy;
	int		start;
	int		i;
	int		j;

	if (!map || !map->grid)
		return (NULL);
	start = find_map_start(map);
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
