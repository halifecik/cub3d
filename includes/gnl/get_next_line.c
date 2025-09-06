/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 18:44:32 by mugenan           #+#    #+#             */
/*   Updated: 2025/02/22 20:58:26 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*returnline;
	static char	*getline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	getline = get_read(getline, fd);
	if (!getline)
	{
		free(getline);
		return (NULL);
	}
	returnline = get_swap(getline);
	getline = get_update(getline);
	if (!getline || getline[0] == '\0' || getline[0] == '\n')
	{
		free(getline);
		getline = NULL;
	}
	return (returnline);
}

char	*get_read(char *getline, int fd)
{
	char	*keeper;
	int		check;

	keeper = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!keeper)
		return (NULL);
	check = 1;
	while (!ft_strchr(getline, '\n') && check != 0)
	{
		check = read(fd, keeper, BUFFER_SIZE);
		if (check == -1)
		{
			free(keeper);
			free(getline);
			return (NULL);
		}
		keeper[check] = '\0';
		getline = ft_strjoin(getline, keeper);
	}
	free(keeper);
	return (getline);
}

char	*get_swap(char *getline)
{
	char	*returnline;
	int		i;

	i = 0;
	if (!getline[i])
		return (NULL);
	while (getline[i] != '\0' && getline[i] != '\n')
		i++;
	returnline = malloc(sizeof(char) * (i + 2));
	if (!returnline)
		return (NULL);
	i = 0;
	while (getline[i] != '\n' && getline[i] != '\0')
	{
		returnline[i] = getline[i];
		i++;
	}
	if (getline[i] == '\n')
	{
		returnline[i] = '\n';
		i++;
	}
	returnline[i] = '\0';
	return (returnline);
}

char	*get_update(char *getline)
{
	char	*buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (getline[i] != '\0' && getline[i] != '\n')
		i++;
	if (!getline[i])
	{
		free(getline);
		return (NULL);
	}
	buffer = malloc(sizeof(char) * (ft_strlen(getline) - i));
	if (!buffer)
		return (NULL);
	i++;
	while (getline[i + j] != '\0')
	{
		buffer[j] = getline[i + j];
		j++;
	}
	buffer[j] = '\0';
	free(getline);
	return (buffer);
}
