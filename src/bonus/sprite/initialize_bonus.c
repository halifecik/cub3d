/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:00:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 18:47:20 by hademirc         ###   ########.fr       */
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
