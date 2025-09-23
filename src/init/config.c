/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:31:23 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/23 22:51:53 by mugenan          ###   ########.fr       */
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

int ft_check_config_complete(t_config *config)
{
    if (!config->north_texture || !config->south_texture
        || !config->west_texture || !config->east_texture)
        return (1);
    if (config->floor_color == 0 && config->ceiling_color == 0)
        return (1);
    if (config->floor_color == 0)
        return (1);
    if (config->ceiling_color == 0)
        return (1);
    return (0);
}

static int	ft_set_texture_path(char **dst, char *line)
{
	int		fd;

	line += 2;
	while (*line && ft_is_whitespace(*line))
		line++;
	if (*dst != NULL)
		return (ft_print_error("Duplicate texture definition"));
	if (*line == '\0')
		return (ft_print_error("Missing texture path"));
	if (!ft_strnstr(line, ".xpm", ft_strlen(line)))
		return (ft_print_error("Texture must be a .xpm file"));
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (ft_print_error("Texture file not found"));
	close(fd);
	*dst = ft_strdup(line);
	if (!*dst)
		return (ft_print_error("Malloc fail in texture_path"));
	return (0);
}

static int	ft_set_rgb_color(int *dst, char *line)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	line += 1;
	while (*line && ft_is_whitespace(*line))
		line++;
	split = ft_split(line, ',');
	if (!split)
		return (ft_print_error("Malloc fail in rgb"));
	if (!split[0] || !split[1] || !split[2] || split[3])
		return (ft_free_grid(split), ft_print_error("Invalid RGB format"));
	if (ft_parse_color_value(split[0], &r)
		|| ft_parse_color_value(split[1], &g)
		|| ft_parse_color_value(split[2], &b))
		return (ft_free_grid(split),
			ft_print_error("RGB values must be numbers between 0 and 255"));
	*dst = (r << 16) | (g << 8) | b;
	ft_free_grid(split);
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
