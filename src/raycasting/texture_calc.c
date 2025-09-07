#include "cub3d.h"

static int	get_texture_num(t_data *data)
{
	if (data->raycast.side == 0)
	{
		if (data->raycast.ray_dir_x > 0)
			return (EAST_TEX);
		else
			return (WEST_TEX);
	}
	else
	{
		if (data->raycast.ray_dir_y > 0)
			return (SOUTH_TEX);
		else
			return (NORTH_TEX);
	}
}

static void	calculate_wall_x(t_data *data)
{
	if (data->raycast.side == 0)
		data->raycast.wall_x = data->player.pos_y + data->raycast.perp_wall_dist * data->raycast.ray_dir_y;
	else
		data->raycast.wall_x = data->player.pos_x + data->raycast.perp_wall_dist * data->raycast.ray_dir_x;
	data->raycast.wall_x -= floor(data->raycast.wall_x);
}

static void	calculate_tex_x(t_data *data)
{
	int	tex_width;

	tex_width = data->graphics.textures[data->raycast.tex_num].width;
	data->raycast.tex_x = (int)(data->raycast.wall_x * (double)tex_width);
	if (data->raycast.side == 0 && data->raycast.ray_dir_x > 0)
		data->raycast.tex_x = tex_width - data->raycast.tex_x - 1;
	if (data->raycast.side == 1 && data->raycast.ray_dir_y < 0)
		data->raycast.tex_x = tex_width - data->raycast.tex_x - 1;
}

void	calculate_texture_coordinates(t_data *data)
{
	data->raycast.tex_num = get_texture_num(data);
	calculate_wall_x(data);
	calculate_tex_x(data);
}

int	get_texture_color(t_data *data, int tex_y)
{
	t_texture	*texture;
	int			color;
	int			tex_width;
	int			tex_height;

	texture = &data->graphics.textures[data->raycast.tex_num];
	tex_width = texture->width;
	tex_height = texture->height;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_height)
		tex_y = tex_height - 1;
	color = *(int *)(texture->data + (tex_y * texture->line_length + data->raycast.tex_x * (texture->bits_per_pixel / 8)));
	return (color);
}
