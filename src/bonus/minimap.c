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

static void	ft_put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = data->graphics.img_data + (y * data->graphics.line_length
			+ x * (data->graphics.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	ft_draw_cell(t_data *data, int cell_x, int cell_y, int color)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;

	start_x = cell_x * data->minimap.cell_size;
	start_y = cell_y * data->minimap.cell_size;
	y = 0;
	while (y < data->minimap.cell_size)
	{
		x = 0;
		while (x < data->minimap.cell_size)
		{
			ft_put_pixel(data, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

static void	ft_draw_minimap_frame(t_data *data, int width, int height)
{
	int	i;
	i = 0;
	while (i < width)
	{
		ft_put_pixel(data, i, 0, 0x000000);          // TOP
		ft_put_pixel(data, i, height - 1, 0x000000); // BOTTOM
		i++;
	}
	i = 0;
	while (i < height)
	{
		ft_put_pixel(data, 0, i, 0x000000);          // LEFT
		ft_put_pixel(data, width - 1, i, 0x000000);  // RIGHT
		i++;
	}
}

static void	ft_draw_minimap_cell(t_data *data, int map_x, int map_y, int cell_x, int cell_y)
{
	char	tile;
	int		color;

	if (map_x >= 0 && map_x < data->map.width
		&& map_y >= data->map.map_index && map_y < data->map.height)
	{
		tile = data->map.grid[map_y][map_x];
		if (tile == '1')
			color = 0x444444; // GRAY
		else
			color = 0xCCCCCC; // LIGHT GRAY
	}
	else
		color = 0x000000; // BLACK for map outside

	ft_draw_cell(data, cell_x, cell_y, color);
}

void	ft_draw_minimap(t_data *data)
{
	int	i;
	int	j;
	int	map_x;
	int	map_y;
	int	half;

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
			ft_draw_minimap_cell(data, map_x, map_y, j, i);
		}
	}
	// Oyuncu ortada
	ft_draw_cell(data, half, half, 0xFF0000);
	ft_draw_minimap_frame(data, data->minimap.visible_cells * data->minimap.cell_size,
		data->minimap.visible_cells * data->minimap.cell_size);
}
#include "cub3d.h"

static void	ft_draw_cell_screen(t_data *data, int start_x, int start_y,
				int size, int color)
{
	int	x;
	int	y;
	char	*dst;

	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (start_x + x >= 0 && start_x + x < SCREEN_WIDTH
				&& start_y + y >= 0 && start_y + y < SCREEN_HEIGHT)
			{
				dst = data->graphics.img_data
					+ ((start_y + y) * data->graphics.line_length
					+ (start_x + x) * (data->graphics.bits_per_pixel / 8));
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
			ft_draw_cell_screen(data,
				offset_x + x * cell_size,
				offset_y + y * cell_size,
				cell_size,
				(tile == '1') ? 0x444444 : 0xCCCCCC);
			x++;
		}
		y++;
	}
	// Oyuncuyu doğru pozisyonda çiz
	ft_draw_cell_screen(data,
		offset_x + (int)data->player.pos_x * cell_size,
		offset_y + (int)data->player.pos_y * cell_size,
		cell_size,
		0xFF0000);
}
