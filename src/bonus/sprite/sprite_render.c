/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:00:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 22:25:12 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_calculate_sprite_bounds(t_data *data, int sprite_idx)
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

static int	ft_get_sprite_pixel_color(t_data *data, int sprite_idx, int tex_x,
		int tex_y)
{
	t_texture	*texture;
	int			offset;
	int			color;

	texture = &data->graphics.textures[data->map.sprites[sprite_idx]
		.texture_index];
	if (tex_x < 0 || tex_x >= texture->width || tex_y < 0
		|| tex_y >= texture->height)
		return (0);
	offset = tex_y * texture->line_length + tex_x
		* (texture->bits_per_pixel / 8);
	color = *(int *)(texture->data + offset);
	return (color);
}

static int	ft_calculate_tex_y(t_data *data, int sprite_idx, int y,
		t_texture *texture)
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

static void	ft_draw_sprite_stripe(t_data *data, int sprite_idx, int stripe,
		double *z_buffer)
{
	int			y;
	int			tex_x;
	int			tex_y;
	int			color;

	tex_x = (int)(256 * (stripe - (-data->map.sprites[sprite_idx]
				.sprite_width / 2 + data->map.sprites[sprite_idx]
				.sprite_screen_x)) * data->graphics.textures[data->map
			.sprites[sprite_idx].texture_index].width
			/ data->map.sprites[sprite_idx].sprite_width) / 256;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= data->graphics.textures[data->map.sprites[sprite_idx]
		.texture_index].width)
		tex_x = data->graphics.textures[data->map.sprites[sprite_idx]
			.texture_index].width - 1;
	if (data->map.sprites[sprite_idx].transform_y > 0 && stripe > 0
		&& stripe < SCREEN_WIDTH && data->map.sprites[sprite_idx]
		.transform_y < z_buffer[stripe])
	{
		y = data->map.sprites[sprite_idx].draw_start_y;
		while (y < data->map.sprites[sprite_idx].draw_end_y)
		{
			tex_y = ft_calculate_tex_y(data, sprite_idx, y,
					&data->graphics.textures[data->map.sprites[sprite_idx]
					.texture_index]);
			color = ft_get_sprite_pixel_color(data, sprite_idx, tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
				ft_put_pixel(data, stripe, y, color);
			y++;
		}
	}
}

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
	double	sprite_x;
	double	sprite_y;
	double	determinant;

	sprite_x = data->map.sprites[i].x - data->player.pos_x;
	sprite_y = data->map.sprites[i].y - data->player.pos_y;
	determinant = data->player.plane_x * data->player.dir_y
		- data->player.dir_x * data->player.plane_y;
	if (determinant == 0.0)
		return ;
	inv_det = 1.0 / determinant;
	data->map.sprites[i].transform_x = (double)(inv_det * (data->player.dir_y
				* sprite_x - data->player.dir_x * sprite_y));
	data->map.sprites[i].transform_y = (double)(inv_det
			* (-data->player.plane_y * sprite_x
				+ data->player.plane_x * sprite_y));
	if (data->map.sprites[i].transform_y <= 0)
		return ;
	ft_calculate_sprite_dimensions(data, i);
}

void	ft_draw_sprite(t_data *data, int sprite_idx, double *z_buffer)
{
	int			stripe;
	t_texture	*texture;

	if (data->map.sprites[sprite_idx].transform_y <= 0
		|| data->map.sprites[sprite_idx].sprite_width <= 0
		|| data->map.sprites[sprite_idx].sprite_height <= 0)
		return ;
	texture = &data->graphics.textures[data->map.sprites[sprite_idx]
		.texture_index];
	ft_calculate_sprite_bounds(data, sprite_idx);
	stripe = data->map.sprites[sprite_idx].draw_start_x;
	while (stripe < data->map.sprites[sprite_idx].draw_end_x)
	{
		ft_draw_sprite_stripe(data, sprite_idx, stripe, z_buffer);
		stripe++;
	}
}

void	ft_render_sprites(t_data *data, double *z_buffer)
{
	int	i;
	int	sprite_idx;

	if (!data || !data->map.sprites || !z_buffer || data->map.sprite_count <= 0)
		return ;
	ft_sort_sprites(data);
	i = 0;
	while (i < data->map.sprite_count)
	{
		sprite_idx = data->map.sprite_order[i];
		if (!data->map.sprites[sprite_idx].collected)
		{
			ft_calculate_sprite_transform(data, sprite_idx);
			ft_draw_sprite(data, sprite_idx, z_buffer);
		}
		i++;
	}
}
