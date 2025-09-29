/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:33 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 17:57:07 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_handle_movement_keys(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = 1;
	else if (keycode == KEY_S)
		data->keys.s = 1;
	else if (keycode == KEY_A)
		data->keys.a = 1;
	else if (keycode == KEY_D)
		data->keys.d = 1;
}

static void	ft_handle_special_keys(int keycode, t_data *data)
{
	if (keycode == KEY_L)
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
	else if (keycode == KEY_E)
		data->keys.e = 1;
}

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_close_window(data);
	ft_handle_movement_keys(keycode, data);
	ft_handle_special_keys(keycode, data);
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
	else if (keycode == KEY_E)
	{
		if (data->keys.e)
		{
			ft_interact_with_door(data);
			data->keys.e = 0;
		}
	}
	return (0);
}
