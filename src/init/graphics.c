/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:31:34 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 18:48:12 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_load_texture(t_data *data, char *path, int tex_index)
{
	t_texture	*texture;

	texture = &data->graphics.textures[tex_index];
	texture->img = mlx_xpm_file_to_image(data->graphics.mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (ERROR);
	texture->data = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	if (!texture->data)
		return (ERROR);
	return (SUCCESS);
}

static int	ft_load_textures(t_data *data)
{
	if (ft_load_texture(data, data->config.north_texture, NORTH_TEX))
		return (ERROR);
	if (ft_load_texture(data, data->config.south_texture, SOUTH_TEX))
		return (ERROR);
	if (ft_load_texture(data, data->config.east_texture, EAST_TEX))
		return (ERROR);
	if (ft_load_texture(data, data->config.west_texture, WEST_TEX))
		return (ERROR);
	return (SUCCESS);
}

int	ft_initialize_graphics(t_data *data)
{
	data->graphics.mlx = mlx_init();
	if (!data->graphics.mlx)
		return (ERROR);
	data->graphics.window = mlx_new_window(data->graphics.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT, "[cub3d] by f(x) = ax3 + bx2 + cx + d");
	if (!data->graphics.window)
		return (ERROR);
	data->graphics.img = mlx_new_image(data->graphics.mlx, SCREEN_WIDTH,
			SCREEN_HEIGHT);
	if (!data->graphics.img)
		return (ERROR);
	data->graphics.img_data = mlx_get_data_addr(data->graphics.img,
			&data->graphics.bits_per_pixel, &data->graphics.line_length,
			&data->graphics.endian);
	if (!data->graphics.img_data)
		return (ERROR);
	if (ft_load_textures(data))
		return (ERROR);
	return (SUCCESS);
}

int	ft_is_valid_position(t_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0 || map_x >= data->map.width
		|| map_y >= data->map.height)
		return (0);
	if (data->map.grid[map_y][map_x] == '1')
		return (0);
	return (1);
}

int	ft_handle_keypress(int keycode, t_data *data)
{
	double	new_x;
	double	new_y;

	if (keycode == KEY_ESC)
		ft_handle_close(data);
	else if (keycode == KEY_W)
	{
		new_x = data->player.pos_x + data->player.dir_x * MOVE_SPEED;
		new_y = data->player.pos_y + data->player.dir_y * MOVE_SPEED;
		if (ft_is_valid_position(data, new_x, new_y))
		{
			data->player.pos_x = new_x;
			data->player.pos_y = new_y;
		}
	}
	else if (keycode == KEY_S)
	{
		new_x = data->player.pos_x - data->player.dir_x * MOVE_SPEED;
		new_y = data->player.pos_y - data->player.dir_y * MOVE_SPEED;
		if (ft_is_valid_position(data, new_x, new_y))
		{
			data->player.pos_x = new_x;
			data->player.pos_y = new_y;
		}
	}
	ft_handle_keypress_2(keycode, data);
	return (0);
}

void	ft_handle_keypress_2(int keycode, t_data *data)
{
	double	new_x;
	double	new_y;

	if (keycode == KEY_A)
	{
		new_x = data->player.pos_x + data->player.dir_y * MOVE_SPEED;
		new_y = data->player.pos_y - data->player.dir_x * MOVE_SPEED;
		if (ft_is_valid_position(data, new_x, new_y))
		{
			data->player.pos_x = new_x;
			data->player.pos_y = new_y;
		}
	}
	else if (keycode == KEY_D)
	{
		new_x = data->player.pos_x - data->player.dir_y * MOVE_SPEED;
		new_y = data->player.pos_y + data->player.dir_x * MOVE_SPEED;
		if (ft_is_valid_position(data, new_x, new_y))
		{
			data->player.pos_x = new_x;
			data->player.pos_y = new_y;
		}
	}
	ft_handle_rotation(keycode, data);
}

void	ft_handle_rotation(int keycode, t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;

	if (keycode == KEY_LEFT)
	{
		old_dir_x = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(ROT_SPEED)
			- data->player.dir_y * sin(ROT_SPEED);
		data->player.dir_y = old_dir_x * sin(ROT_SPEED) + data->player.dir_y
			* cos(ROT_SPEED);
		old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(ROT_SPEED)
			- data->player.plane_y * sin(ROT_SPEED);
		data->player.plane_y = old_plane_x * sin(ROT_SPEED)
			+ data->player.plane_y * cos(ROT_SPEED);
	}
	else if (keycode == KEY_RIGHT)
	{
		old_dir_x = data->player.dir_x;
		data->player.dir_x = data->player.dir_x * cos(-ROT_SPEED)
			- data->player.dir_y * sin(-ROT_SPEED);
		data->player.dir_y = old_dir_x * sin(-ROT_SPEED) + data->player.dir_y
			* cos(-ROT_SPEED);
		old_plane_x = data->player.plane_x;
		data->player.plane_x = data->player.plane_x * cos(-ROT_SPEED)
			- data->player.plane_y * sin(-ROT_SPEED);
		data->player.plane_y = old_plane_x * sin(-ROT_SPEED)
			+ data->player.plane_y * cos(-ROT_SPEED);
	}
}

int	ft_handle_close(t_data *data)
{
	ft_cleanup_graphics(data);
	exit(0);
	return (0);
}

void	ft_cleanup_graphics(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->graphics.textures[i].img)
			mlx_destroy_image(data->graphics.mlx,
				data->graphics.textures[i].img);
		i++;
	}
	if (data->graphics.img)
		mlx_destroy_image(data->graphics.mlx, data->graphics.img);
	if (data->graphics.window)
		mlx_destroy_window(data->graphics.mlx, data->graphics.window);
}
