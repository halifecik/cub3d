/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:35 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 20:43:58 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_game_loop(t_data *data)
{
	data->frame++;
	if (data->keys.w)
		ft_move_forward(data);
	if (data->keys.s)
		ft_move_backward(data);
	if (data->keys.a)
		ft_strafe_left(data);
	if (data->keys.d)
		ft_strafe_right(data);
	if (data->keys.right)
		ft_rotate_right(data);
	if (data->keys.left)
		ft_rotate_left(data);
	ft_update_doors(data);
	ft_render_frame(data);
	if (data->keys.tab)
		ft_draw_full_map(data);
	else
		ft_draw_minimap(data);
	mlx_put_image_to_window(data->graphics.mlx, data->graphics.window,
		data->graphics.img, 0, 0);
	return (0);
}
