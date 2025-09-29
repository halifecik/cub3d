/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:00:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 22:25:12 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_update_sprite_animation(t_sprite *sprite)
{
	sprite->animation_time += COIN_ANIMATION_SPEED;
	if (sprite->animation_time >= 1.0)
		sprite->animation_time = 0.0;
	sprite->texture_index = COIN_TEX_BASE + (int)(sprite->animation_time
			* COIN_FRAMES);
	if (sprite->texture_index >= COIN_TEX_BASE + COIN_FRAMES)
		sprite->texture_index = COIN_TEX_BASE;
}

static void	ft_update_sprite_float(t_sprite *sprite, int frame)
{
	double	base_float;
	double	variation;

	base_float = sin((frame * COIN_FLOAT_SPEED) + (sprite->x + sprite->y));
	variation = cos((frame * COIN_FLOAT_SPEED * 1.3) + (sprite->x * 2.0));
	variation *= 0.3;
	sprite->float_offset = (base_float + variation) * COIN_FLOAT_HEIGHT;
}

static void	ft_collect_single_sprite(t_data *data, int i)
{
	double	dx;
	double	dy;
	double	distance;

	dx = data->player.pos_x - data->map.sprites[i].x;
	dy = data->player.pos_y - data->map.sprites[i].y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < COIN_COLLECT_RANGE)
	{
		data->map.sprites[i].collected = 1;
		data->coins_collected++;
		ft_update_map_grid(data, i);
	}
}

void	ft_collect_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map.sprite_count)
	{
		if (!data->map.sprites[i].collected)
			ft_collect_single_sprite(data, i);
		i++;
	}
}

void	ft_update_sprites(t_data *data)
{
	int	i;

	if (!data || !data->map.sprites || data->map.sprite_count <= 0)
		return ;
	i = 0;
	while (i < data->map.sprite_count)
	{
		if (!data->map.sprites[i].collected)
		{
			ft_update_sprite_animation(&data->map.sprites[i]);
			ft_update_sprite_float(&data->map.sprites[i], data->frame);
			ft_calculate_sprite_distance(data, i);
		}
		i++;
	}
	ft_collect_sprites(data);
}

void	ft_calculate_sprite_distance(t_data *data, int i)
{
	double	dx;
	double	dy;

	dx = data->player.pos_x - data->map.sprites[i].x;
	dy = data->player.pos_y - data->map.sprites[i].y;
	data->map.sprites[i].distance = dx * dx + dy * dy;
	data->map.sprite_distance[i] = data->map.sprites[i].distance;
}
