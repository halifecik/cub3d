#include "cub3d.h"

int	ft_is_identifier(char *line)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static int	ft_atoi_color(char *str)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(str);
	if (r < 0 || r > 255)
		return (-1);
	while (*str && *str != ',')
		str++;
	if (*str == ',')
		str++;
	g = ft_atoi(str);
	if (g < 0 || g > 255)
		return (-1);
	while (*str && *str != ',')
		str++;
	if (*str == ',')
		str++;
	b = ft_atoi(str);
	if (b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

void	ft_parse_identifier(char *line, t_config *config)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		config->north_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		config->south_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		config->west_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		config->east_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		config->floor_color = ft_atoi_color(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		config->ceiling_color = ft_atoi_color(line + 2);
}
