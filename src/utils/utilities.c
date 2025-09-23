/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:56 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/23 14:36:43 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	ft_rtrim(char *str)
{
	int	len;

	if (!str)
		return ;
	len = (int)ft_strlen(str) - 1;
	while (len >= 0 && ft_is_whitespace(str[len]))
	{
		str[len] = '\0';
		len--;
	}
}

void	ft_free_grid(char **grid)
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