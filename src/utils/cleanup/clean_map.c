/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:08:47 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 22:02:42 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clean_map(t_map *map)
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
	if (map->sprites)
	{
		free(map->sprites);
		map->sprites = NULL;
	}
	if (map->sprite_order)
	{
		free(map->sprite_order);
		map->sprite_order = NULL;
	}
	if (map->sprite_distance)
	{
		free(map->sprite_distance);
		map->sprite_distance = NULL;
	}
}
