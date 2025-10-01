/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:53 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 18:26:38 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

# ifdef BONUS
static int	ft_get_door_texture(t_data *data)
{
	t_raycast	*ray;
	double		door_state;
	int			frame;

	ray = &data->raycast;
	door_state = ft_get_door_animation_state(data, ray->map_x, ray->map_y);
	if (door_state <= 0.1)
	{
		if ((data->frame / DOOR_TEXTURE_FRAME_RATE) % 2 == 0)
			return (DOOR_TEX_BASE + 0);
		else
			return (DOOR_TEX_BASE + 1);
	}
	frame = (int)(door_state * (DOOR_FRAMES - 1));
	if (frame < 0)
		frame = 0;
	if (frame >= DOOR_FRAMES)
		frame = DOOR_FRAMES - 1;
	return (DOOR_TEX_BASE + frame);
}
# endif

static int	ft_get_wall_texture(t_data *data)
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

static int	ft_texture_number(t_data *data)
{
# ifdef BONUS
	t_raycast	*ray;
	char		cell;

	ray = &data->raycast;
	cell = data->map.grid[ray->map_y + data->map.map_index][ray->map_x];
	if (cell == 'D')
		return (ft_get_door_texture(data));
# endif
	return (ft_get_wall_texture(data));
}

void	ft_texture_coordinates(t_data *data)
{
	data->raycast.tex_num = ft_texture_number(data);
	ft_wall_x(data);
	ft_texture_x(data);
}

int	ft_texture_color(t_data *data, int tex_y)
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
