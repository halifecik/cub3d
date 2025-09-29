/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:00:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 22:25:12 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_count_sprites(t_data *data)
{
	int	count;
	int	y;
	int	x;
	int	map_height;

	if (!data || !data->map.grid)
		return (0);
	count = 0;
	y = 0;
	map_height = data->map.height - data->map.map_index;
	while (y < map_height)
	{
		if (!data->map.grid[y + data->map.map_index])
			break ;
		x = 0;
		while (data->map.grid[y + data->map.map_index][x])
		{
			if (data->map.grid[y + data->map.map_index][x] == SPRITE)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	ft_initialize_sprite(t_data *data, int sprite_idx, int x, int y)
{
	data->map.sprites[sprite_idx].x = x + 0.5;
	data->map.sprites[sprite_idx].y = y + 0.5;
	data->map.sprites[sprite_idx].collected = 0;
	data->map.sprites[sprite_idx].animation_time = 0.0;
	data->map.sprites[sprite_idx].float_offset = 0.0;
	data->map.sprites[sprite_idx].texture_index = COIN_TEX_BASE;
}

static void	ft_populate_sprites(t_data *data)
{
	int	sprite_idx;
	int	y;
	int	x;
	int	map_height;

	sprite_idx = 0;
	y = 0;
	map_height = data->map.height - data->map.map_index;
	while (y < map_height && sprite_idx < data->map.sprite_count)
	{
		if (!data->map.grid[y + data->map.map_index])
			break ;
		x = 0;
		while (data->map.grid[y + data->map.map_index][x]
			&& sprite_idx < data->map.sprite_count)
		{
			if (data->map.grid[y + data->map.map_index][x] == SPRITE)
			{
				ft_initialize_sprite(data, sprite_idx, x, y);
				sprite_idx++;
			}
			x++;
		}
		y++;
	}
}

void	ft_update_map_grid(t_data *data, int i)
{
	int	grid_x;
	int	grid_y;

	grid_x = (int)data->map.sprites[i].x;
	grid_y = (int)data->map.sprites[i].y;
	if (grid_y + data->map.map_index < data->map.height
		&& grid_x < (int)ft_strlen(data->map.grid[grid_y
				+ data->map.map_index]))
		data->map.grid[grid_y + data->map.map_index][grid_x] = '0';
}

static int	ft_build_sprite_path(char *sprite_path, int i)
{
	char	*num_str;
	char	*temp;

	num_str = ft_itoa(i);
	if (!num_str)
		return (ERROR);
	temp = ft_strjoin("./textures/coin_", num_str);
	if (!temp)
	{
		free(num_str);
		return (ERROR);
	}
	ft_strlcpy(sprite_path, temp, 50);
	free(temp);
	temp = ft_strjoin(sprite_path, ".xpm");
	if (!temp)
	{
		free(num_str);
		return (ERROR);
	}
	ft_strlcpy(sprite_path, temp, 50);
	free(temp);
	free(num_str);
	return (SUCCESS);
}

int	ft_load_sprite_textures(t_data *data)
{
	char	sprite_path[50];
	int		i;

	if (!data || !data->graphics.mlx)
		return (ERROR);
	i = 0;
	while (i < COIN_FRAMES)
	{
		if (ft_build_sprite_path(sprite_path, i))
			return (ERROR);
		if (ft_load_texture(data, sprite_path, COIN_TEX_BASE + i))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	ft_initialize_sprites(t_data *data)
{
	if (!data || !data->map.grid)
		return ;
	data->map.sprite_count = ft_count_sprites(data);
	if (data->map.sprite_count == 0)
	{
		data->map.sprites = NULL;
		data->map.sprite_order = NULL;
		data->map.sprite_distance = NULL;
		return ;
	}
	data->map.sprites = malloc(sizeof(t_sprite) * data->map.sprite_count);
	data->map.sprite_order = malloc(sizeof(int) * data->map.sprite_count);
	data->map.sprite_distance = malloc(sizeof(double) * data->map.sprite_count);
	if (!data->map.sprites || !data->map.sprite_order
		|| !data->map.sprite_distance)
		return ;
	ft_populate_sprites(data);
}
