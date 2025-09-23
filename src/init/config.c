/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:31:23 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/23 17:32:21 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_initialize_config(t_config *config)
{
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
	config->floor_color = 0;
	config->ceiling_color = 0;
}

static int	ft_set_texture_path(char **dst, char *line)
{
	line += 2;
	while (*line && ft_is_whitespace(*line))
		line++;
	if (*dst != NULL)
		return (1);
	*dst = ft_strdup(line);
	if (!*dst)
		return (1);
	return (0);
}

static int	ft_set_rgb_color(int *dst, char *line)
{
	char	**color;
	int		r;
	int		g;
	int		b;

	if (*dst != 0)
		return (1);
	line++;
	while (*line && ft_is_whitespace(*line))
		line++;
	color = ft_split(line, ',');
	if (!color || !color[0] || !color[1] || !color[2])
		return (1);
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	ft_free_grid(color);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (1);
	*dst = (r << 16) | (g << 8) | b;
	return (0);
}

int	ft_set_config(t_map *map, t_config *config)
{
	int	i;

	i = -1;
	while (++i < map->map_index)
	{
		if (!ft_strncmp(map->grid[i], "NO", 2))
			if (ft_set_texture_path(&config->north_texture, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "SO", 2))
			if (ft_set_texture_path(&config->south_texture, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "WE", 2))
			if (ft_set_texture_path(&config->west_texture, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "EA", 2))
			if (ft_set_texture_path(&config->east_texture, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "F", 1))
			if (ft_set_rgb_color(&config->floor_color, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "C", 1))
			if (ft_set_rgb_color(&config->ceiling_color, map->grid[i]))
				return (1);
	}
	return (0);
}
