#include "cub3d.h"

static int	ft_is_map_line(char *line)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (!ft_strchr("01NSEW", *line) && !ft_is_whitespace(*line))
			return (0);
		line++;
	}
	return (1);
}

static char	*ft_clean_line_with_check(char *line)
{
	int		i;

	if (!line)
		return (NULL);
	i = -1;
	while (line[i])
		if (!ft_strchr("01NSEW", line[i]) && !ft_is_whitespace(line[i]))
			return (NULL);
	return (ft_strdup(line));
}

static int	ft_add_line_to_map(t_map *map, char *line)
{
	char	**new_grid;
	char	*clean;
	int		i;

	clean = ft_clean_line_with_check(line);
	if (!clean)
		return (EXIT_FAILURE);
	new_grid = malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
	{
		free(clean);
		return (EXIT_FAILURE);
	}
	i = -1;
	while (++i < map->height)
		new_grid[i] = map->grid[i];
	new_grid[i] = clean;
	map->height++;
	new_grid[map->height] = NULL;
	if (map->grid)
		free(map->grid);
	map->grid = new_grid;
	if ((int)ft_strlen(clean) > map->width)
		map->width = (int)ft_strlen(clean);
	return (EXIT_SUCCESS);
}

static int	ft_read_line(int fd, t_data *data, int *map_started)
{
	char	*line;
	int		status;

	line = get_next_line(fd);
	if (!line)
		return (0);
	status = 0;
	if (!*map_started)
	{
		if (ft_is_identifier(line))
			ft_parse_identifier(line, &data->config);
		else if (ft_is_map_line(line))
		{
			*map_started = 1;
			status = ft_add_line_to_map(&data->map, line);
		}
	}
	else
	{
		if (!ft_is_map_line(line))
			return (free(line), EXIT_FAILURE);
		status = ft_add_line_to_map(&data->map, line);
	}
	free(line);
	return (status);
}

int	ft_parse_map(t_data *data, char *filename)
{
	int	fd;
	int	map_started;
	int	status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	map_started = 0;
	while (1)
	{
		status = ft_read_line(fd, data, &map_started);
		if (status == 0)
			break ;
		if (status != EXIT_SUCCESS)
		{
			close(fd);
			return (EXIT_FAILURE);
		}
	}
	close(fd);
	return (EXIT_SUCCESS);
}
