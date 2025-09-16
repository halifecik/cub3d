#include "cub3d.h"

#include <stdlib.h>
#include <string.h>

// ft_is_whitespace senin verdiğin fonksiyon
int	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

// Satırın sağındaki boşlukları kaldıran fonksiyon
void	ft_rtrim(char *str)
{
	int	len;

	if (!str)
		return;
	len = strlen(str) - 1;
	while (len >= 0 && ft_is_whitespace(str[len]))
	{
		str[len] = '\0';
		len--;
	}
}

int	is_line_empty(char *str)
{
	int	i;

	if (!str)
		return (0); // false
	i = 0;
	while (str[i])
	{
		if (!ft_is_whitespace(str[i]))
			return (0); // false
		i++;
	}
	return (1); // true
}

char	**copy_grid(char **grid, int height)
{
	char	**cpy;
	int		i;

	cpy = malloc(sizeof(char *) * (height + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		cpy[i] = ft_strdup(grid[i]);
		if (!cpy[i])
		{
			while (i-- > 0)
				free(cpy[i]);
			free(cpy);
			return (NULL);
		}
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	free_grid(char **grid)
{
	int	i;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
static int	is_map_line(char *line)
{
	int	j;
	int	valid;

	if (!line)
		return (0);
	j = 0;
	valid = 0;
	while (line[j])
	{
		if (line[j] == '0' || line[j] == '1' || line[j] == 'N' ||
			line[j] == 'S' || line[j] == 'E' || line[j] == 'W')
			valid = 1;
		else if (!ft_is_whitespace(line[j]))
			return (0);
		j++;
	}
	return (valid);
}

static int	find_map_start(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		if (is_map_line(map->grid[i]))
			return (i);
		i++;
	}
	return (-1);
}

char	**copy_map_lines(t_map *map, int *cpy_height)
{
	char	**copy;
	int		start;
	int		i;
	int		j;

	if (!map || !map->grid)
		return (NULL);
	start = find_map_start(map);
	if (start == -1)
		return (NULL);
	*cpy_height = map->height - start;
	copy = ft_calloc(*cpy_height + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = start;
	j = 0;
	while (i < map->height)
		copy[j++] = ft_strdup(map->grid[i++]);
	copy[j] = NULL;
	return (copy);
}
