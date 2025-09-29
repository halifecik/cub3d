/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:30:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 17:50:59 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT)
	{
		offset = y * data->graphics.line_length
			+ x * (data->graphics.bits_per_pixel / 8);
		dst = data->graphics.img_data + offset;
		*(unsigned int *)dst = color;
	}
}

static void	ft_draw_door_pixels(t_data *data, int x, int door_bottom)
{
	double	step;
	int		tex_y;
	int		color;
	double	tex_pos;
	int		y;

	step = 1.0 * data->graphics.textures[data->raycast.tex_num].height
		/ data->raycast.line_height;
	tex_pos = (data->raycast.draw_start - SCREEN_HEIGHT
			/ 2 + data->raycast.line_height / 2) * step;
	y = data->raycast.draw_start - 1;
	while (++y <= data->raycast.draw_end)
	{
		if (y <= door_bottom)
		{
			tex_y = (int)tex_pos
				& (data->graphics.textures[data->raycast.tex_num].height - 1);
			color = ft_texture_color(data, tex_y);
			ft_put_pixel(data, x, y, color);
		}
		tex_pos += step;
	}
}

static void	ft_draw_door_background(t_data *data, int x, int y)
{
	while (++y < data->raycast.draw_start)
		ft_put_pixel(data, x, y, data->config.ceiling_color);
	y = data->raycast.draw_end;
	while (++y < SCREEN_HEIGHT)
		ft_put_pixel(data, x, y, data->config.floor_color);
}

void	ft_draw_door_line(t_data *data, int x, int y, double door_state)
{
	int	door_bottom;

	ft_texture_coordinates(data);
	door_bottom = data->raycast.draw_end
		- (int)(door_state * data->raycast.line_height);
	ft_draw_door_background(data, x, y);
	ft_draw_door_pixels(data, x, door_bottom);
}
