/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:54:16 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 20:33:37 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_draw_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = data->graphics.img_data + (y * data->graphics.line_length
			+ x * (data->graphics.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_colored_cell(t_data *data, int start_x, int start_y, int color)
{
	int	x;
	int	y;
	int	size;

	size = data->minimap.current_cell_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			ft_draw_pixel(data, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

int	ft_tile_color(char tile)
{
	if (tile == '1')
		return (GRAY_PIXEL);
	if (tile == 'D')
		return (PURPLE_PIXEL);
	if (tile == '0' || tile == 'X')
		return (LIGHT_GRAY_PIXEL);
	return (BLACK_PIXEL);
}

void	ft_draw_frame(t_data *data, int start_x, int start_y, int width)
{
	int	i;
	int	height;

	height = width;
	i = 0;
	while (i < width)
	{
		ft_draw_pixel(data, start_x + i, start_y, BLACK_PIXEL);
		ft_draw_pixel(data, start_x + i, start_y + height - 1, BLACK_PIXEL);
		i++;
	}
	i = 0;
	while (i < height)
	{
		ft_draw_pixel(data, start_x, start_y + i, BLACK_PIXEL);
		ft_draw_pixel(data, start_x + width - 1, start_y + i, BLACK_PIXEL);
		i++;
	}
}
