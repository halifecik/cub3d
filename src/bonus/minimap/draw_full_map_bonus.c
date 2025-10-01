/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_full_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:54:10 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 17:04:57 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	fullmap_cell_color(t_data *data, int map_x, int map_y)
{
	int	row_len;

	if (map_x < 0 || map_y < 0
		|| map_y >= data->map.height - data->map.map_index)
		return (BLACK_PIXEL);
	row_len = ft_strlen(data->map.grid[map_y + data->map.map_index]);
	if (map_x >= row_len)
		return (BLACK_PIXEL);
	return (ft_tile_color(data->map.grid[map_y + data->map.map_index][map_x]));
}

static void	draw_fullmap_cells(t_data *data, int cell_size, int offset_x,
	int offset_y)
{
	int	i;
	int	j;
	int	map_x;
	int	map_y;
	int	color;

	i = -1;
	while (++i < data->map.height - data->map.map_index)
	{
		j = -1;
		while (++j < data->map.width)
		{
			map_x = j;
			map_y = i;
			color = fullmap_cell_color(data, map_x, map_y);
			ft_draw_colored_cell(data, offset_x + j * cell_size,
				offset_y + i * cell_size, color);
		}
	}
	ft_draw_colored_cell(data, offset_x + (int)data->player.pos_x * cell_size,
		offset_y + (int)data->player.pos_y * cell_size, RED_PIXEL);
}

void	ft_draw_full_map(t_data *data)
{
	int	cell_size;
	int	offset_x;
	int	offset_y;

	cell_size = SCREEN_WIDTH / data->map.width;
	if (cell_size > SCREEN_HEIGHT / (data->map.height - data->map.map_index))
		cell_size = SCREEN_HEIGHT / (data->map.height - data->map.map_index);
	data->minimap.current_cell_size = cell_size;
	offset_x = (SCREEN_WIDTH - data->map.width * cell_size) / 2;
	offset_y = (SCREEN_HEIGHT - (data->map.height - data->map.map_index)
			* cell_size) / 2;
	draw_fullmap_cells(data, cell_size, offset_x, offset_y);
}
