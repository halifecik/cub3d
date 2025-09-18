#include "cub3d.h"

static int	ft_grid_append_line(t_map *map, char *line)
{
	char	**new_grid;
	int	i;

	map->height++;
	if ((int)ft_strlen(line) > map->width)
		map->width = ft_strlen(line);
	new_grid = ft_calloc(map->height + 1, sizeof(char *));
	if (!new_grid)
	{
		free(line);
		return (ft_print_error("Malloc fail"));
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
		if (!is_line_empty(line))
		{
			ft_rtrim(line);
			if (ft_grid_append_line(map, line))
				return (1);
		}
		else
			free(line);
		line = get_next_line(fd);
	}
	if (!map->grid)
		return (ft_print_error("Empty map"));
	return (0);
}

int	ft_parse_map(t_data *data)
{
	int	fd;

	fd = open(data->map_file, O_RDONLY);
	if (fd < 0)
		return (ft_print_error("Cannot open .cub file"));
	ft_initialize_map(&data->map);
	if (ft_read_map_lines(&data->map, fd))
		return (close(fd), 1);
	close(fd);
	if (ft_check_map(&data->map))
		return (1);
	if (ft_initialize_player_location(data, &data->map))
		return (ft_print_error("Initialize player location error"));
	if (ft_set_config(&data->map, &data->config))
		return (ft_print_error("Config textures error"));
	return (0);
}
