/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:31:23 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/03 20:00:13 by mugenan          ###   ########.fr       */
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
	config->wspc = ft_str_whitespace();
}

static int	ft_set_texture_path(char **dst, char *line)
{
	int		fd;

	line += 2;
	if (!ft_is_whitespace(*line))
		return (ft_perror("Missing space after texture identifier"));
	while (*line && ft_is_whitespace(*line))
		line++;
	if (*dst != NULL)
		return (ft_perror("Duplicate texture definition"));
	if (*line == '\0')
		return (ft_perror("Missing texture path"));
	if (!ft_strnstr(line, ".xpm", ft_strlen(line)))
		return (ft_perror("Texture must be a .xpm file"));
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (ft_perror("Texture file not found"));
	close(fd);
	*dst = ft_strdup(line);
	if (!*dst)
		return (ft_perror("Malloc fail in texture_path"));
	return (0);
}

static int	ft_set_rgb_color(int *dst, char *line)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	if (*dst != 0)
		return (ft_perror("Duplicate color definition"));
	line += 1;
	if (!ft_is_whitespace(*line))
		return (ft_perror("Missing space after color identifier"));
	while (*line && ft_is_whitespace(*line))
		line++;
	split = ft_split(line, ',');
	if (!split)
		return (ft_perror("Malloc fail in rgb"));
	if (!split[0] || !split[1] || !split[2] || split[3])
		return (ft_perror("Invalid RGB format"));
	if (ft_parse_color_value(split[0], &r)
		|| ft_parse_color_value(split[1], &g)
		|| ft_parse_color_value(split[2], &b))
		return (ft_free_grid(split),
			ft_perror("RGB values must be numbers between 0 and 255"));
	*dst = (r << 16) | (g << 8) | b;
	ft_free_grid(split);
	return (0);
}

static int	ft_check_line(char *line, t_config *config)
{
	if (!ft_strncmp(line, "NO", 2))
		return (ft_set_texture_path(&config->north_texture, line));
	if (!ft_strncmp(line, "SO", 2))
		return (ft_set_texture_path(&config->south_texture, line));
	if (!ft_strncmp(line, "WE", 2))
		return (ft_set_texture_path(&config->west_texture, line));
	if (!ft_strncmp(line, "EA", 2))
		return (ft_set_texture_path(&config->east_texture, line));
	if (!ft_strncmp(line, "F", 1))
		return (ft_set_rgb_color(&config->floor_color, line));
	if (!ft_strncmp(line, "C", 1))
		return (ft_set_rgb_color(&config->ceiling_color, line));
	return (0);
}

int	ft_set_config(t_map *map, t_config *config)
{
	int		i;
	char	*trimmed;

	i = -1;
	while (++i < map->map_index)
	{
		if (map->grid[i] && map->grid[i][0] != '\0')
		{
			trimmed = ft_strtrim(map->grid[i], config->wspc);
			if (!trimmed)
				return (1);
			if (ft_check_line(trimmed, config))
			{
				free(trimmed);
				return (1);
			}
			free(trimmed);
		}
	}
	return (0);
}
