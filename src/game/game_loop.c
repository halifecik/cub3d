/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:30:35 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 18:30:36 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close_window(t_data *data)
{
	ft_cleanup(data);
	exit(EXIT_SUCCESS);
	return (0);
}

void	ft_cleanup(t_data *data)
{
	int	i;

	if (data->graphics.mlx)
	{
		i = 0;
		while (i < 4)
		{
			if (data->graphics.textures[i].img)
				mlx_destroy_image(data->graphics.mlx,
					data->graphics.textures[i].img);
			i++;
		}
		if (data->graphics.img)
			mlx_destroy_image(data->graphics.mlx, data->graphics.img);
		if (data->graphics.window)
			mlx_destroy_window(data->graphics.mlx, data->graphics.window);
		mlx_destroy_display(data->graphics.mlx);
		free(data->graphics.mlx);
	}
}

int	ft_game_loop(t_data *data)
{
	ft_render_frame(data);
	mlx_put_image_to_window(data->graphics.mlx, data->graphics.window,
		data->graphics.img, 0, 0);
	return (0);
}
