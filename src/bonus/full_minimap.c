#include "cub3d.h"

static void	ft_draw_cell_screen(t_data *data, int start_x, int start_y,
		int size, int color)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (start_x + x >= 0 && start_x + x < SCREEN_WIDTH && start_y
				+ y >= 0 && start_y + y < SCREEN_HEIGHT)
			{
				dst = data->graphics.img_data + ((start_y + y)
						* data->graphics.line_length + (start_x + x)
						* (data->graphics.bits_per_pixel / 8));
				*(unsigned int *)dst = color;
			}
			x++;
		}
		y++;
	}
}

void	ft_draw_full_map(t_data *data)
{
	int		x;
	int		y;
	int		map_width;
	int		map_height;
	int		cell_size;
	int		offset_x;
	int		offset_y;
	char	tile;

	map_width = data->map.width;
	map_height = data->map.height - data->map.map_index;
	cell_size = SCREEN_WIDTH / map_width;
	if (cell_size > SCREEN_HEIGHT / map_height)
		cell_size = SCREEN_HEIGHT / map_height;
	offset_x = (SCREEN_WIDTH - (map_width * cell_size)) / 2;
	offset_y = (SCREEN_HEIGHT - (map_height * cell_size)) / 2;
	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (x < map_width)
		{
			tile = data->map.grid[y + data->map.map_index][x];
			ft_draw_cell_screen(data, offset_x + x * cell_size, offset_y + y
				* cell_size, cell_size, (tile == '1') ? 0x444444 : 0xCCCCCC);
			x++;
		}
		y++;
	}
	ft_draw_cell_screen(data, offset_x + (int)data->player.pos_x * cell_size,
		offset_y + (int)data->player.pos_y * cell_size, cell_size, 0xFF0000);
}
