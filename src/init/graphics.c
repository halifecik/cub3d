/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:31:34 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 22:02:42 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_load_texture(t_data *data, char *path, int tex_index)
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

static int	ft_load_door_textures(t_data *data)
{
	char	door_path[50];
	char	*num_str;
	char	*temp;
	int		i;

	i = 0;
	while (i < DOOR_FRAMES)
	{
		num_str = ft_itoa(i);
		temp = ft_strjoin("./textures/door_", num_str);
		ft_strlcpy(door_path, temp, sizeof(door_path));
		free(temp);
		temp = ft_strjoin(door_path, ".xpm");
		ft_strlcpy(door_path, temp, sizeof(door_path));
		free(temp);
		free(num_str);
		if (ft_load_texture(data, door_path, DOOR_TEX_BASE + i))
		{
			if (ft_load_texture(data, "./textures/door.xpm", DOOR_TEX_BASE + i))
				return (ERROR);
		}
		i++;
	}
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
	if (ft_load_door_textures(data))
		return (ERROR);
	if (ft_load_sprite_textures(data))
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
	mlx_mouse_hide(data->graphics.mlx, data->graphics.window);
	mlx_mouse_move(data->graphics.mlx, data->graphics.window, SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2);
	ft_initialize_minimap(&data->minimap);
	return (SUCCESS);
}
