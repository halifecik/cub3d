#include "cub3d.h"

/* map satırı mı, geçersiz karakter varsa fail */
static int	is_map_line(char *line)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (!ft_strchr("01NSEW", *line) && !is_whitespace(*line))
			return (0);
		line++;
	}
	return (1);
}

/* sadece geçersiz karakterleri kontrol et, spaces/tab map içinde korunacak */
static char	*clean_line_with_check(char *line)
{
	char	*result;
	int		i;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01NSEW", line[i]) && !is_whitespace(line[i]))
			return (NULL); // geçersiz karakter
		i++;
	}
	return (ft_strdup(line)); // tüm satır olduğu gibi korunuyor
}

/* map’e satır ekleme, width güncellemesi */
static int	add_line_to_map(t_map *map, char *line)
{
	char	**new_grid;
	char	*clean;
	int		i;

	clean = clean_line_with_check(line);
	if (!clean)
		return (EXIT_FAILURE); // geçersiz karakter
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
	if (ft_strlen(clean) > map->width)
		map->width = ft_strlen(clean);
	return (EXIT_SUCCESS);
}

/* GNL ile satır oku ve işleme */
static int	read_line(int fd, t_data *data, int *map_started)
{
	char	*line;
	int		status;

	if (get_next_line(fd, &line) <= 0)
		return (0);
	status = 0;
	if (!*map_started)
	{
		if (is_identifier(line))
			parse_identifier(line, &data->config);
		else if (is_map_line(line))
		{
			*map_started = 1;
			status = add_line_to_map(&data->map, line);
		}
	}
	else
	{
		if (!is_map_line(line))
			return (free(line), EXIT_FAILURE); // map başladıktan sonra geçersiz karakter
		status = add_line_to_map(&data->map, line);
	}
	free(line);
	return (status);
}

#include "cub3d.h"

/* Dosyayı aç, GNL ile oku ve map oluştur */
int	parse_map(t_data *data, char *filename)
{
	int		fd;
	int		map_started;
	int		status;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (EXIT_FAILURE);
	map_started = 0;
	while (1)
	{
		status = read_line(fd, data, &map_started);
		if (status == 0)       // EOF
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
