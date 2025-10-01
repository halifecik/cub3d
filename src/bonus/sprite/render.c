/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:00:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 18:47:26 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static int	ft_calculate_tex_x(t_data *data, int sprite_idx, int stripe)
{
	int		tex_x;
	int		sprite_start;
	double	ratio;

	sprite_start = -data->map.sprites[sprite_idx].sprite_width / 2
		+ data->map.sprites[sprite_idx].sprite_screen_x;
	ratio = (double)(stripe - sprite_start)
		/ data->map.sprites[sprite_idx].sprite_width;
	tex_x = (int)(ratio * data->graphics.textures[data->map
			.sprites[sprite_idx].texture_index].width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= data->graphics.textures[data->map.sprites[sprite_idx]
			.texture_index].width)
		tex_x = data->graphics.textures[data->map.sprites[sprite_idx]
			.texture_index].width - 1;
	return (tex_x);
}

static void	ft_draw_sprite_stripe(t_data *data, int sprite_idx, int stripe,
		double *z_buffer)
{
	int			y;
	int			tex_x;
	int			tex_y;
	int			color;

	tex_x = ft_calculate_tex_x(data, sprite_idx, stripe);
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
