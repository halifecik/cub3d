/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:08:47 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/30 12:41:03 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

static void	ft_clean_map_core(t_map *map)
{
	int	i;

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
# ifdef BONUS
	if (map->doors)
	{
		free(map->doors);
		map->doors = NULL;
	}
# endif
}

static void	ft_clean_map_sprites(t_map *map)
{
# ifdef BONUS
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
# else
	(void)map;
# endif
}

void	ft_clean_map(t_map *map)
{
	if (!map)
		return ;
# ifdef BONUS
	if (!map->grid && !map->doors && !map->sprites
		&& !map->sprite_order && !map->sprite_distance)
		return ;
# else
	if (!map->grid)
		return ;
# endif
	ft_clean_map_core(map);
	ft_clean_map_sprites(map);
}
