/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:36 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/26 19:15:13 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_can_move_to(t_data *data, int x, int y)
{
	char	cell;
	int		map_y;

	if (x < 0 || y < 0 || x >= data->map.width)
		return (0);
	map_y = y + data->map.map_index;
	if (map_y < 0 || map_y >= data->map.height)
		return (0);
	cell = data->map.grid[map_y][x];
	if (cell == '0')
		return (1);
	if (cell == 'D')
	{
		double door_state = ft_get_door_animation_state(data, x, y);
		return (door_state >= 0.7);
	}
	return (0);
}

void	ft_move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * data->player.move_speed;
	new_y = data->player.pos_y + data->player.dir_y * data->player.move_speed;
	if (ft_can_move_to(data, (int)new_x, (int)data->player.pos_y))
		data->player.pos_x = new_x;
	if (ft_can_move_to(data, (int)data->player.pos_x, (int)new_y))
		data->player.pos_y = new_y;
}

void	ft_move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * data->player.move_speed;
	new_y = data->player.pos_y - data->player.dir_y * data->player.move_speed;
	if (ft_can_move_to(data, (int)new_x, (int)data->player.pos_y))
		data->player.pos_x = new_x;
	if (ft_can_move_to(data, (int)data->player.pos_x, (int)new_y))
		data->player.pos_y = new_y;
}

void	ft_strafe_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.plane_x * data->player.move_speed;
	new_y = data->player.pos_y - data->player.plane_y * data->player.move_speed;
	if (ft_can_move_to(data, (int)new_x, (int)data->player.pos_y))
		data->player.pos_x = new_x;
	if (ft_can_move_to(data, (int)data->player.pos_x, (int)new_y))
		data->player.pos_y = new_y;
}

void	ft_strafe_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.plane_x * data->player.move_speed;
	new_y = data->player.pos_y + data->player.plane_y * data->player.move_speed;
	if (ft_can_move_to(data, (int)new_x, (int)data->player.pos_y))
		data->player.pos_x = new_x;
	if (ft_can_move_to(data, (int)data->player.pos_x, (int)new_y))
		data->player.pos_y = new_y;
}
