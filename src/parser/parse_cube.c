#include "cub3d.h"

static int	is_map_line(char *line)
{
	if (!line || *line == '\0')
		return (0);
	while (*line)
	{
		if (!ft_strchr("01NSEW ", *line))
			return (0);
		line++;
	}
	return (1);
}

static void	add_line_to_map(t_map *map, char *line)
{
	char	**new_grid;
	int		i;

	new_grid = malloc(sizeof(char *) * (map->height + 2));
	if (!new_grid)
		return ;
	i = -1;
	while (++i < map->height)
		new_grid[i] = map->grid[i];
	new_grid[i] = ft_strdup(line);
	if (!new_grid[i])
	{
		free(new_grid);
		return ;
	}
	map->height++;
	new_grid[map->height] = NULL;
	if (map->grid)
	{
		i = -1;
		while (++i < map->height - 1)
			free(map->grid[i]);
		free(map->grid);
	}
	map->grid = new_grid;
	if ((int)ft_strlen(line) > map->width)
		map->width = ft_strlen(line);
}

static int	read_file(int fd, t_data *data)
{
	char	*line;
	int		map_started;

	map_started = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!map_started)
		{
			if (is_identifier(line))
				parse_identifier(line, &data->config);
			else if (is_map_line(line))
			{
				map_started = 1;
				add_line_to_map(&data->map, line);
			}
		}
		else
			add_line_to_map(&data->map, line);
		free(line);
	}
	free(line);
	return (EXIT_SUCCESS);  // read_file başarılı tamamlandı
}

int	parse_cub(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE); // dosya açılamadı
	// free_old_grid(&data->map);
	if (read_file(fd, data) != EXIT_SUCCESS)
	{
		close(fd);
		return (EXIT_FAILURE); // okuma hatası
	}
	close(fd);
	if (!validate_map(&data->map))
		return (EXIT_FAILURE); // map validasyonu başarısız
	return (EXIT_SUCCESS); // her şey başarılı
}
