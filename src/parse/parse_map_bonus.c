/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:37 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 18:27:58 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	ft_grid_append_line(t_map *map, char *line)
{
	char	**new_grid;
	int		i;

	map->height++;
	if ((int)ft_strlen(line) > map->width)
		map->width = ft_strlen(line);
	new_grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!new_grid)
	{
		free(line);
		return (ft_print_error("Malloc fail grid"));
	}
	i = 0;
	while (i < map->height - 1)
	{
		new_grid[i] = map->grid[i];
		i++;
	}
	new_grid[i++] = line;
	new_grid[i] = NULL;
	free(map->grid);
	map->grid = new_grid;
	return (0);
}

static int	ft_read_map_lines(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		ft_rtrim(line);
		if (ft_grid_append_line(map, line))
			return (1);
		line = get_next_line(fd);
	}
	if (!map->grid)
		return (1);
	return (0);
}

int	ft_parse_map(t_data *data)
{
	int	fd;

	ft_initialize_map(&data->map);
	fd = open(data->map_file, O_RDONLY);
	if (fd < 0)
		return (ft_print_error("Cannot open .cub file"));
	if (ft_read_map_lines(&data->map, fd))
		return (close(fd), ft_print_error("Map is empty"));
	close(fd);
	if (ft_check_map(&data->map))
		return (1);
	if (ft_set_player_location(data, &data->map))
		return (ft_print_error("Initialize player location error"));
	ft_initialize_config(&data->config);
	if (ft_set_config(&data->map, &data->config))
		return (ft_clean_config(&data->config), 1);
	if (ft_check_config_complete(&data->config))
		return (ft_clean_config(&data->config),
			ft_print_error("Missing argument config"));

	ft_initialize_doors(&data->map);

	return (0);
}
