/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:47 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 22:02:42 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_ceiling_and_floor(t_data *data, int x)
{
	int	y;

	y = -1;
	while (++y < data->raycast.draw_start)
		ft_put_pixel(data, x, y, data->config.ceiling_color);
	y = data->raycast.draw_end;
	while (++y < SCREEN_HEIGHT)
		ft_put_pixel(data, x, y, data->config.floor_color);
}

static void	ft_draw_wall_texture(t_data *data, int x)
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
		tex_y = (int)tex_pos
			& (data->graphics.textures[data->raycast.tex_num].height - 1);
		tex_pos += step;
		color = ft_texture_color(data, tex_y);
		ft_put_pixel(data, x, y, color);
	}
}

static void	ft_draw_vertical_line(t_data *data, int x, int y)
{
	char	cell;
	double	door_state;

	ft_texture_coordinates(data);
	cell = data->map.grid[data->raycast.map_y + data->map.map_index]
	[data->raycast.map_x];
	if (cell == 'D')
	{
		door_state = ft_get_door_animation_state(data, data->raycast.map_x,
				data->raycast.map_y);
		ft_draw_door_line(data, x, y, door_state);
		return ;
	}
	ft_draw_ceiling_and_floor(data, x);
	ft_draw_wall_texture(data, x);
}

void	ft_render_frame(t_data *data)
{
	static double	z_buffer[SCREEN_WIDTH];
	int				x;
	int				y;

	x = -1;
	y = -1;
	while (++x < SCREEN_WIDTH)
	{
		ft_cast_ray(data, x);
		ft_draw_vertical_line(data, x, y);
		z_buffer[x] = data->raycast.perp_wall_dist;
	}
	ft_update_sprites(data);
	ft_render_sprites(data, z_buffer);
}
