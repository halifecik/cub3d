/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:31:26 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/30 12:33:13 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

void	ft_initialize_map(t_map *map)
{
	if (!map)
		return ;
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->map_index = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = '\0';
# ifdef BONUS
	map->doors = NULL;
	map->door_count = 0;
	map->sprites = NULL;
	map->sprite_count = 0;
	map->sprite_order = NULL;
	map->sprite_distance = NULL;
# endif
}
