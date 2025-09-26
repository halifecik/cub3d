/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 18:30:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/26 19:15:13 by hademirc         ###   ########.fr       */
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

void	ft_update_doors(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		if (data->map.doors[i].is_opening)
		{
			data->map.doors[i].animation_state += DOOR_ANIMATION_SPEED;
			if (data->map.doors[i].animation_state >= DOOR_OPEN)
			{
				data->map.doors[i].animation_state = DOOR_OPEN;
				data->map.doors[i].is_opening = 0;
			}
		}
		else if (data->map.doors[i].is_closing)
		{
			data->map.doors[i].animation_state -= DOOR_ANIMATION_SPEED;
			if (data->map.doors[i].animation_state <= DOOR_CLOSED)
			{
				data->map.doors[i].animation_state = DOOR_CLOSED;
				data->map.doors[i].is_closing = 0;
			}
		}
		i++;
	}
}

static double	ft_distance_to_door(t_data *data, int door_x, int door_y)
{
	double	dx;
	double	dy;

	dx = data->player.pos_x - door_x - 0.5;
	dy = data->player.pos_y - door_y - 0.5;
	return (sqrt(dx * dx + dy * dy));
}

static t_door	*ft_find_closest_door(t_data *data)
{
	int		i;
	double	min_distance;
	double	distance;
	t_door	*closest_door;

	if (data->map.door_count == 0)
		return (NULL);
	closest_door = NULL;
	min_distance = DOOR_INTERACTION_RANGE + 1.0;
	i = 0;
	while (i < data->map.door_count)
	{
		distance = ft_distance_to_door(data, data->map.doors[i].x,
				data->map.doors[i].y);
		if (distance < min_distance && distance <= DOOR_INTERACTION_RANGE)
		{
			min_distance = distance;
			closest_door = &data->map.doors[i];
		}
		i++;
	}
	return (closest_door);
}

void	ft_interact_with_door(t_data *data)
{
	t_door	*door;

	door = ft_find_closest_door(data);
	if (!door)
		return ;
	if (door->is_opening || door->is_closing)
		return ;
	if (door->animation_state <= DOOR_CLOSED + 0.1)
	{
		door->is_opening = 1;
		door->is_closing = 0;
	}
	else if (door->animation_state >= DOOR_OPEN - 0.1)
	{
		door->is_closing = 1;
		door->is_opening = 0;
	}
	else
	{
		if (door->animation_state < 0.5)
		{
			door->is_opening = 1;
			door->is_closing = 0;
		}
		else
		{
			door->is_closing = 1;
			door->is_opening = 0;
		}
	}
}

int	ft_is_door_at_position(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		if (data->map.doors[i].x == x && data->map.doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

double	ft_get_door_animation_state(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		if (data->map.doors[i].x == x && data->map.doors[i].y == y)
			return (data->map.doors[i].animation_state);
		i++;
	}
	return (DOOR_CLOSED);
}