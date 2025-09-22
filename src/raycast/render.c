/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:47 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 21:24:52 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		offset = y * data->graphics.line_length + x * (data->graphics.bits_per_pixel / 8);
		dst = data->graphics.img_data + offset;
		*(unsigned int *)dst = color;
	}
}

static void	ft_draw_borders(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		x = -1;
		while (++x < SCREEN_WIDTH)
		{
			if (x < VIEWPORT_OFFSET_X || x >= VIEWPORT_OFFSET_X + VIEWPORT_WIDTH ||
				y < VIEWPORT_OFFSET_Y || y >= VIEWPORT_OFFSET_Y + VIEWPORT_HEIGHT)
				ft_put_pixel(data, x, y, BLACK_PIXEL);
		}
	}
}

static void	ft_draw_vertical_line(t_data *data, int x)
{
	int		y;
	double	step;
	int		tex_y;
	int		color;
	double	tex_pos;
	int		screen_x;

	screen_x = x + VIEWPORT_OFFSET_X;
	ft_texture_coordinates(data);
	step = 1.0 * data->graphics.textures[data->raycast.tex_num].height / data->raycast.line_height;
	tex_pos = (data->raycast.draw_start - VIEWPORT_HEIGHT / 2 + data->raycast.line_height / 2) * step;
	y = -1;
	while (++y < data->raycast.draw_start)
		ft_put_pixel(data, screen_x, y + VIEWPORT_OFFSET_Y, data->config.ceiling_color);
	while (y <= data->raycast.draw_end)
	{
		tex_y = (int)tex_pos & (data->graphics.textures[data->raycast.tex_num].height - 1);
		tex_pos += step;
		color = ft_texture_color(data, tex_y);
		ft_put_pixel(data, screen_x, y + VIEWPORT_OFFSET_Y, color);
		y++;
	}
	y--;
	while (++y < VIEWPORT_HEIGHT)
		ft_put_pixel(data, screen_x, y + VIEWPORT_OFFSET_Y, data->config.floor_color);
}

void	ft_render_frame(t_data *data)
{
	int	x;

	ft_draw_borders(data);
	x = -1;
	while (++x < VIEWPORT_WIDTH)
	{
		ft_cast_ray(data, x);
		ft_draw_vertical_line(data, x);
	}
}
