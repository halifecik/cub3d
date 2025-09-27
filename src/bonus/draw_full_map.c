#include "cub3d.h"

/* Yardımcı: full map hücrelerini çiz */
static void	draw_fullmap_cells(t_data *data, int cell_size, int offset_x, int offset_y)
{
	int i;
	int j;
	char tile;
	int color;

	i = -1;
	while (++i < data->map.height - data->map.map_index)
	{
		j = -1;
		while (++j < data->map.width)
		{
			tile = data->map.grid[i + data->map.map_index][j];
			color = ft_tile_color(tile);
			ft_draw_cell(data, offset_x + j * cell_size, offset_y + i * cell_size,
				cell_size, color);
		}
	}
	ft_draw_cell(data, offset_x + (int)data->player.pos_x * cell_size,
		offset_y + (int)data->player.pos_y * cell_size, cell_size, 0xFF0000);
}

/* Full screen map */
void	ft_draw_full_map(t_data *data)
{
	int cell_size;
	int offset_x;
	int offset_y;

	cell_size = SCREEN_WIDTH / data->map.width;
	if (cell_size > SCREEN_HEIGHT / (data->map.height - data->map.map_index))
		cell_size = SCREEN_HEIGHT / (data->map.height - data->map.map_index);
	offset_x = (SCREEN_WIDTH - data->map.width * cell_size) / 2;
	offset_y = (SCREEN_HEIGHT - (data->map.height - data->map.map_index) * cell_size) / 2;
	draw_fullmap_cells(data, cell_size, offset_x, offset_y);
}
