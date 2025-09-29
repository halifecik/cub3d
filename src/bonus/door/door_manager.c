/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:50:54 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 16:52:13 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_count_doors(t_map *map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = map->map_index;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width && map->grid[i][j])
		{
			if (map->grid[i][j] == DOOR)
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

static void	ft_populate_doors(t_map *map)
{
	int	door_idx;
	int	i;
	int	j;

	door_idx = 0;
	i = map->map_index;
	while (i < map->height && door_idx < map->door_count)
	{
		j = 0;
		while (j < map->width && map->grid[i][j] && door_idx < map->door_count)
		{
			if (map->grid[i][j] == DOOR)
			{
				map->doors[door_idx].x = j;
				map->doors[door_idx].y = i - map->map_index;
				map->doors[door_idx].animation_state = DOOR_CLOSED;
				map->doors[door_idx].is_opening = 0;
				map->doors[door_idx].is_closing = 0;
				door_idx++;
			}
			j++;
		}
		i++;
	}
}

void	ft_initialize_doors(t_map *map)
{
	map->door_count = ft_count_doors(map);
	if (map->door_count == 0)
	{
		map->doors = NULL;
		return ;
	}
	map->doors = ft_calloc(map->door_count, sizeof(t_door));
	if (!map->doors)
	{
		ft_print_error("Failed to allocate memory for doors");
		return ;
	}
	ft_populate_doors(map);
}

static void	ft_update_door_animation(t_data *data, t_door *door)
{
	if (door->is_opening)
	{
		door->animation_state += DOOR_ANIMATION_SPEED;
		if (door->animation_state >= DOOR_OPEN)
		{
			door->animation_state = DOOR_OPEN;
			door->is_opening = 0;
		}
	}
	else if (door->is_closing)
	{
		if (!ft_player_on_door(data, door))
		{
			door->animation_state -= DOOR_ANIMATION_SPEED;
			if (door->animation_state <= DOOR_CLOSED)
			{
				door->animation_state = DOOR_CLOSED;
				door->is_closing = 0;
			}
		}
	}
}

void	ft_update_doors(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		ft_update_door_animation(data, &data->map.doors[i]);
		i++;
	}
}
