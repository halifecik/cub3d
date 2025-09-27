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

static int	minimap_cell_color(t_data *data, int map_x, int map_y)
{
	int row_len;

	if (map_x < 0 || map_y < 0 || map_y >= data->map.height - data->map.map_index)
		return 0x000000;
	row_len = ft_strlen(data->map.grid[map_y + data->map.map_index]);
	if (map_x >= row_len)
		return 0x000000;
	return ft_tile_color(data->map.grid[map_y + data->map.map_index][map_x]);
}

static void	draw_minimap_cells(t_data *data, int start_x, int start_y, int cell_size)
{
	int i;
	int j;
	int map_x;
	int map_y;
	int color;

	i = -1;
	while (++i < data->minimap.visible_cells)
	{
		j = -1;
		while (++j < data->minimap.visible_cells)
		{
			map_x = start_x + j;
			map_y = start_y + i;
			color = minimap_cell_color(data, map_x, map_y);
			ft_draw_cell(data, j * cell_size, i * cell_size, cell_size, color);
		}
	}
}

void	ft_draw_minimap(t_data *data)
{
	int cell_size;
	int half;
	int start_x;
	int start_y;

	cell_size = data->minimap.cell_size;
	half = data->minimap.visible_cells / 2;
	start_x = (int)data->player.pos_x - half;
	start_y = (int)data->player.pos_y - half;

	draw_minimap_cells(data, start_x, start_y, cell_size);
	ft_draw_cell(data, half * cell_size, half * cell_size, cell_size, 0xFF0000);
	ft_draw_frame(data, 0, 0, data->minimap.visible_cells * cell_size,
		data->minimap.visible_cells * cell_size);
}
