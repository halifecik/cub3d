/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:33 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/25 18:03:00 by mugenan          ###   ########.fr       */
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
	else if (keycode == KEY_L)
	{
		if (data->keys.l)
			data->keys.l = 0;
		else 
			data->keys.l = 1;
	}
	else if (keycode == KEY_LEFT)
		data->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	else if (keycode == KEY_TAB)
		data->keys.tab = 1;
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
	else if (keycode == KEY_TAB)
		data->keys.tab = 0;
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

static void	ft_mouse_lock(t_data *data)
{
	if (!data->keys.l)
	{
		mlx_mouse_move(data->graphics.mlx, data->graphics.window,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	else
		mlx_mouse_show(data->graphics.mlx, data->graphics.window);
}

int	ft_mouse_move(int x, int y, t_data *data)
{
	int		delta_x;
	double	rotation_speed;
	double	old_dir_x;
	double	old_plane_x;

	(void)y;
	delta_x = x - SCREEN_WIDTH / 2;
	if (delta_x == 0)
		return (0);
	rotation_speed = delta_x * MOUSE_SENSITIVITY;
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
	ft_mouse_lock(data);
	return (0);
}
