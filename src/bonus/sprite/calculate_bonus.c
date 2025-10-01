/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:30:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 18:47:17 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_calculate_sprite_dimensions(t_data *data, int i)
{
	data->map.sprites[i].sprite_screen_x = (int)((SCREEN_WIDTH / 2)
			* (1 + data->map.sprites[i].transform_x
				/ data->map.sprites[i].transform_y));
	data->map.sprites[i].sprite_height = abs((int)(SCREEN_HEIGHT
				/ data->map.sprites[i].transform_y)) / 3;
	data->map.sprites[i].sprite_width = data->map.sprites[i].sprite_height;
	data->map.sprites[i].draw_start_y = -data->map.sprites[i].sprite_height / 2
		+ SCREEN_HEIGHT / 2 + (int)data->map.sprites[i].float_offset;
	if (data->map.sprites[i].draw_start_y < 0)
		data->map.sprites[i].draw_start_y = 0;
	data->map.sprites[i].draw_end_y = data->map.sprites[i].sprite_height / 2
		+ SCREEN_HEIGHT / 2 + (int)data->map.sprites[i].float_offset;
	if (data->map.sprites[i].draw_end_y >= SCREEN_HEIGHT)
		data->map.sprites[i].draw_end_y = SCREEN_HEIGHT - 1;
}

void	ft_calculate_sprite_transform(t_data *data, int i)
{
	double	inv_det;

	data->map.sprites[i].transform_x = (data->player.dir_y
			* (data->map.sprites[i].x - data->player.pos_x)
			- data->player.dir_x * (data->map.sprites[i].y
				- data->player.pos_y));
	data->map.sprites[i].transform_y = (-data->player.plane_y
			* (data->map.sprites[i].x - data->player.pos_x)
			+ data->player.plane_x * (data->map.sprites[i].y
				- data->player.pos_y));
	inv_det = 1.0 / (data->player.plane_x * data->player.dir_y
			- data->player.dir_x * data->player.plane_y);
	data->map.sprites[i].transform_x *= inv_det;
	data->map.sprites[i].transform_y *= inv_det;
	ft_calculate_sprite_dimensions(data, i);
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

void	ft_calculate_sprite_bounds(t_data *data, int sprite_idx)
{
	data->map.sprites[sprite_idx].draw_end_y
		= data->map.sprites[sprite_idx].sprite_height / 2
		+ SCREEN_HEIGHT / 2 + (int)data->map.sprites[sprite_idx].float_offset;
	if (data->map.sprites[sprite_idx].draw_end_y >= SCREEN_HEIGHT)
		data->map.sprites[sprite_idx].draw_end_y = SCREEN_HEIGHT - 1;
	data->map.sprites[sprite_idx].draw_start_x
		= -data->map.sprites[sprite_idx].sprite_width / 2
		+ data->map.sprites[sprite_idx].sprite_screen_x;
	if (data->map.sprites[sprite_idx].draw_start_x < 0)
		data->map.sprites[sprite_idx].draw_start_x = 0;
	data->map.sprites[sprite_idx].draw_end_x
		= data->map.sprites[sprite_idx].sprite_width / 2
		+ data->map.sprites[sprite_idx].sprite_screen_x;
	if (data->map.sprites[sprite_idx].draw_end_x >= SCREEN_WIDTH)
		data->map.sprites[sprite_idx].draw_end_x = SCREEN_WIDTH - 1;
}

int	ft_calculate_tex_y(t_data *data, int sprite_idx, int y, t_texture *texture)
{
	int	d;
	int	tex_y;

	d = (y - (int)data->map.sprites[sprite_idx].float_offset) * 256
		- SCREEN_HEIGHT * 128 + data->map.sprites[sprite_idx]
		.sprite_height * 128;
	tex_y = ((d * texture->height)
			/ data->map.sprites[sprite_idx].sprite_height) / 256;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (tex_y);
}
