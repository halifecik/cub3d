/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:31:26 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/26 19:15:13 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	map->doors = NULL;
	map->door_count = 0;
}
