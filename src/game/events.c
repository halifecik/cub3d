/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:33 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 21:03:19 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_close_window(data);
	else if (keycode == KEY_W)
		data->keys.w = 1;
	else if (keycode == KEY_S)
		data->keys.s = 1;
	else if (keycode == KEY_A)
		data->keys.a = 1;
	else if (keycode == KEY_D)
		data->keys.d = 1;
	else if (keycode == KEY_LEFT)
		data->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	return (0);
}

int	ft_key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 0;
	else if (keycode == KEY_S)
		data->keys.s = 0;
	else if (keycode == KEY_A)
		data->keys.a = 0;
	else if (keycode == KEY_D)
		data->keys.d = 0;
	else if (keycode == KEY_LEFT)
		data->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	return (0);
}

int	ft_mouse_press(int button, int x, int y, t_data *data)
{
	(void)button;
	(void)x;
	(void)y;
	(void)data;
	return (0);
}

int	ft_mouse_move(int x, int y, t_data *data)
{
	static int	last_x = -1;
	int			delta_x;
	double		rotation_speed;
	double		old_dir_x;
	double		old_plane_x;

	(void)y;
	if (last_x == -1)
	{
		last_x = x;
		return (0);
	}
	delta_x = x - last_x;
	last_x = x;
	if (delta_x == 0)
		return (0);
	rotation_speed = delta_x * 0.002;
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
	return (0);
}
