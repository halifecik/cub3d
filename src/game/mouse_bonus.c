/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:35:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 17:57:29 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	ft_mouse_lock(t_data *data)
{
	if (!data->keys.l)
	{
		mlx_mouse_hide(data->graphics.mlx, data->graphics.window);
		mlx_mouse_move(data->graphics.mlx, data->graphics.window,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	else
		mlx_mouse_show(data->graphics.mlx, data->graphics.window);
}

static void	ft_mouse_rotate(t_data *data, double rotation_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rotation_speed)
		- data->player.dir_y * sin(rotation_speed);
	data->player.dir_y = old_dir_x * sin(rotation_speed)
		+ data->player.dir_y * cos(rotation_speed);
	old_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rotation_speed)
		- data->player.plane_y * sin(rotation_speed);
	data->player.plane_y = old_plane_x * sin(rotation_speed)
		+ data->player.plane_y * cos(rotation_speed);
}

int	ft_mouse_move(int x, int y, t_data *data)
{
	int		delta_x;
	double	rotation_speed;

	(void)y;
	delta_x = x - SCREEN_WIDTH / 2;
	if (delta_x == 0)
		return (0);
	rotation_speed = delta_x * MOUSE_SENSITIVITY;
	ft_mouse_rotate(data, rotation_speed);
	ft_mouse_lock(data);
	return (0);
}
