#include "cub3d.h"

void	ft_initialize_minimap(t_minimap *minimap)
{
	minimap->half = 0;
	minimap->start_x = 0;
	minimap->start_y = 0;
	minimap->cell_size = 20;
	minimap->visible_cells = 15;
	minimap->width = minimap->cell_size * minimap->visible_cells;
	minimap->height = minimap->width;
}

/* Normal minimap */
void	ft_draw_minimap(t_data *data)
{
	int i;
	int j;
	int map_x;
	int map_y;
	int half;
	char tile;
	int cell_size;

	cell_size = data->minimap.cell_size;
	half = data->minimap.visible_cells / 2;
	data->minimap.start_x = (int)data->player.pos_x - half;
	data->minimap.start_y = (int)data->player.pos_y - half;

	i = -1;
	while (++i < data->minimap.visible_cells)
	{
		j = -1;
		while (++j < data->minimap.visible_cells)
		{
			map_x = data->minimap.start_x + j;
			map_y = data->minimap.start_y + i + data->map.map_index;
			if (map_x >= 0 && map_x < data->map.width &&
				map_y >= 0 && map_y < data->map.height)
				tile = data->map.grid[map_y][map_x];
			else
				tile = ' ';
			ft_draw_cell(data, j * cell_size, i * cell_size, cell_size,
				(tile == ' ') ? 0x000000 : ft_tile_color(tile));
		}
	}
	ft_draw_cell(data, half * cell_size, half * cell_size, cell_size, 0xFF0000);
	ft_draw_frame(data, 0, 0, data->minimap.visible_cells * cell_size,
		data->minimap.visible_cells * cell_size);
}

/* Full screen map */
void	ft_draw_full_map(t_data *data)
{
	int i;
	int j;
	int offset_x;
	int offset_y;
	int cell_size;
	char tile;

	cell_size = SCREEN_WIDTH / data->map.width;
	if (cell_size > SCREEN_HEIGHT / (data->map.height - data->map.map_index))
		cell_size = SCREEN_HEIGHT / (data->map.height - data->map.map_index);
	offset_x = (SCREEN_WIDTH - data->map.width * cell_size) / 2;
	offset_y = (SCREEN_HEIGHT - (data->map.height - data->map.map_index) * cell_size) / 2;

	i = -1;
	while (++i < data->map.height - data->map.map_index)
	{
		j = -1;
		while (++j < data->map.width)
		{
			tile = data->map.grid[i + data->map.map_index][j];
			ft_draw_cell(data, offset_x + j * cell_size, offset_y + i * cell_size,
				cell_size, ft_tile_color(tile));
		}
	}
	ft_draw_cell(data, offset_x + (int)data->player.pos_x * cell_size,
		offset_y + (int)data->player.pos_y * cell_size, cell_size, 0xFF0000);
}
