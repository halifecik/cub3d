#include "cub3d.h"

static int	get_texture_num(t_data *data)
{
	t_raycast	*ray;

	ray = &data->raycast;
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (EAST_TEX);
		else
			return (WEST_TEX);
	}
	else
	{
		if (ray->ray_dir_y > 0)
			return (SOUTH_TEX);
		else
			return (NORTH_TEX);
	}
}

static void	calculate_wall_x(t_data *data)
{
	t_raycast	*ray;

	ray = &data->raycast;
	if (ray->side == 0)
		ray->wall_x = data->player.pos_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		ray->wall_x = data->player.pos_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

static void	calculate_tex_x(t_data *data)
{
	int			tex_width;
	t_raycast	*ray;

	ray = &data->raycast;
	tex_width = data->graphics.textures[ray->tex_num].width;
	ray->tex_x = (int)(ray->wall_x * (double)tex_width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = tex_width - ray->tex_x - 1;
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
	int			offset;

	texture = &data->graphics.textures[data->raycast.tex_num];
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	offset = tex_y * texture->line_length + data->raycast.tex_x
		* (texture->bits_per_pixel / 8);
	color = *(int *)(texture->data + offset);
	return (color);
}
