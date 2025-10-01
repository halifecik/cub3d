/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:30:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 18:47:31 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	ft_build_sprite_path(char *sprite_path, int i)
{
	char	*num_str;
	char	*temp;

	num_str = ft_itoa(i);
	if (!num_str)
		return (ERROR);
	temp = ft_strjoin("./textures/sprite/coin_", num_str);
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
