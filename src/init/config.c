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

static int	set_texture_path(char **dst, char *line)
{
	line += 2;
	while (*line && ft_is_whitespace(*line))
		line++;
	*dst = ft_strdup(line);
	if (!*dst)
		return (ft_print_error("Malloc fail in texture_path"));
	return (0);
}

static int	set_rgb_color(int *dst, char *line)
{
	char	**color;
	int		r;
	int		g;
	int		b;

	line++;
	while (*line && ft_is_whitespace(*line))
		line++;
	color = ft_split(line, ',');
	if (!color || !color[0] || !color[1] || !color[2])
	{
		if (color)
			free_grid(color);
		return (ft_print_error("Invalid color format"));
	}
	r = ft_atoi(color[0]);
	g = ft_atoi(color[1]);
	b = ft_atoi(color[2]);
	free_grid(color);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_print_error("RGB value out of range"));
	*dst = (r << 16) | (g << 8) | b;
	return (0);
}

int	ft_set_config(t_map *map, t_config *config)
{
	int		i;

	i = -1;
	while (++i < map->map_index)
	{
		if (!ft_strncmp(map->grid[i], "NO", 2))
			if (set_texture_path(&config->north_texture, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "SO", 2))
			if (set_texture_path(&config->south_texture, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "WE", 2))
			if (set_texture_path(&config->west_texture, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "EA", 2))
			if (set_texture_path(&config->east_texture, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "F", 1))
			if (set_rgb_color(&config->floor_color, map->grid[i]))
				return (1);
		if (!ft_strncmp(map->grid[i], "C", 1))
			if (set_rgb_color(&config->ceiling_color, map->grid[i]))
				return (1);
	}
	return (0);
}
