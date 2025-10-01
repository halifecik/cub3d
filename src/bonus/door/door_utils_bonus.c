/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:51:32 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 16:51:34 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	ft_player_on_door(t_data *data, t_door *door)
{
	double	px;
	double	py;

	px = data->player.pos_x;
	py = data->player.pos_y;
	if (px >= door->x - 0.2 && px <= door->x + 1.2
		&& py >= door->y - 0.2 && py <= door->y + 1.2)
		return (1);
	return (0);
}

static double	ft_distance_to_door(t_data *data, int door_x, int door_y)
{
	double	dx;
	double	dy;

	dx = data->player.pos_x - door_x - 0.5;
	dy = data->player.pos_y - door_y - 0.5;
	return (sqrt(dx * dx + dy * dy));
}

t_door	*ft_find_closest_door(t_data *data)
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
