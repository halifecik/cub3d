/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:04:40 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/03 13:37:37 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_map_line(char *line)
{
	int	i;
	int	valid;

	if (!line)
		return (0);
	i = 0;
	valid = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W' || line[i] == 'D'
			|| line[i] == 'X')
			valid = 1;
		else if (!ft_is_whitespace(line[i]))
			return (0);
		i++;
	}
	return (valid);
}

int	ft_check_config_complete(t_config *config)
{
	if (!config->north_texture || !config->south_texture
		|| !config->west_texture || !config->east_texture)
		return (1);
	if (!config->floor_color || !config->ceiling_color)
		return (1);
	return (0);
}

int	ft_parse_color_value(char *str, int *value)
{
	int	i;
	int	start;
	int	end;

	if (!str || !*str)
		return (1);
	start = 0;
	while (str[start] && ft_is_whitespace(str[start]))
		start++;
	if (!str[start])
		return (1);
	end = ft_strlen(str) - 1;
	while (end >= start && ft_is_whitespace(str[end]))
		end--;
	i = start;
	while (i <= end)
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	*value = ft_atoi(str + start);
	if (*value < 0 || *value > 255)
		return (1);
	return (0);
}

int	ft_find_map_start(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return (-1);
	i = 0;
	while (i < map->height)
	{
		if (ft_map_line(map->grid[i]))
			return (i);
		i++;
	}
	return (-1);
}
