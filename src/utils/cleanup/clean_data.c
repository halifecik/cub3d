/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:08:58 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 20:16:11 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_mandatory.h"

void	ft_clean_data(t_data *data)
{
	if (!data)
		return ;
		ft_clean_map(&data->map);
	ft_clean_config(&data->config);
	ft_clean_graphics(&data->graphics);
}

int	ft_close_window(t_data *data)
{
	ft_clean_data(data);
	exit(SUCCESS);
	return (0);
}
