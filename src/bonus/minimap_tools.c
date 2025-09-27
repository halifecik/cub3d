#include "cub3d.h"

void	ft_draw_pixel(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = data->graphics.img_data
		+ (y * data->graphics.line_length + x * (data->graphics.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_cell(t_data *data, int start_x, int start_y, int size, int color)
{
	int x;
	int y;

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
		return 0x444444;
	if (tile == 'D')
		return 0xB53389;
	return 0xCCCCCC;
}

void	ft_draw_frame(t_data *data, int start_x, int start_y, int width, int height)
{
	int i;

	i = 0;
	while (i < width)
	{
		ft_draw_pixel(data, start_x + i, start_y, 0x000000);
		ft_draw_pixel(data, start_x + i, start_y + height - 1, 0x000000);
		i++;
	}
	i = 0;
	while (i < height)
	{
		ft_draw_pixel(data, start_x, start_y + i, 0x000000);
		ft_draw_pixel(data, start_x + width - 1, start_y + i, 0x000000);
		i++;
	}
}
