/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:56 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/02 14:16:07 by hademirc         ###   ########.fr       */
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

char	*ft_str_whitespace(void)
{
	char	*str;

	str = malloc(7);
	if (!str)
		return (NULL);
	str[0] = ' ';
	str[1] = '\t';
	str[2] = '\n';
	str[3] = '\v';
	str[4] = '\f';
	str[5] = '\r';
	str[6] = '\0';
	return (str);
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
