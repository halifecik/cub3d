/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:31:41 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 18:48:27 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_initialize_player(t_player *player)
{
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROT_SPEED;
}

int	ft_set_player_location(t_data *data, t_map *map)
{
	ft_initialize_player(&data->player);
	data->player.pos_x = map->player_x + 0.5;
	data->player.pos_y = map->player_y + 0.5;
	if (map->player_dir == 'N')
		return (ft_player_north(data), 0);
	else if (map->player_dir == 'S')
		return (ft_player_south(data), 0);
	else if (map->player_dir == 'E')
		return (ft_player_east(data), 0);
	else if (map->player_dir == 'W')
		return (ft_player_west(data), 0);
	return (1);
}
