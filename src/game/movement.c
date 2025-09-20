/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:36 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 18:30:37 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_move_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
	if (data->map.grid[(int)data->player.pos_y][(int)new_x] == '0')
		data->player.pos_x = new_x;
	if (data->map.grid[(int)new_y][(int)data->player.pos_x] == '0')
		data->player.pos_y = new_y;
}

void	ft_move_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
	if (data->map.grid[(int)data->player.pos_y][(int)new_x] == '0')
		data->player.pos_x = new_x;
	if (data->map.grid[(int)new_y][(int)data->player.pos_x] == '0')
		data->player.pos_y = new_y;
}

void	ft_strafe_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.plane_x * MOVE_SPEED;
	new_y = data->player.pos_y - data->player.plane_y * MOVE_SPEED;
	if (data->map.grid[(int)data->player.pos_y][(int)new_x] == '0')
		data->player.pos_x = new_x;
	if (data->map.grid[(int)new_y][(int)data->player.pos_x] == '0')
		data->player.pos_y = new_y;
}

void	ft_strafe_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.plane_x * MOVE_SPEED;
	new_y = data->player.pos_y + data->player.plane_y * MOVE_SPEED;
	if (data->map.grid[(int)data->player.pos_y][(int)new_x] == '0')
		data->player.pos_x = new_x;
	if (data->map.grid[(int)new_y][(int)data->player.pos_x] == '0')
		data->player.pos_y = new_y;
}
