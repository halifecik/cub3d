/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:00:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 22:25:12 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_swap_sprites(int *order, double *distance, int i, int j)
{
	int		temp_order;
	double	temp_distance;

	temp_order = order[i];
	temp_distance = distance[i];
	order[i] = order[j];
	distance[i] = distance[j];
	order[j] = temp_order;
	distance[j] = temp_distance;
}

void	ft_sort_sprites(t_data *data)
{
	int	i;
	int	j;

	if (!data || !data->map.sprites || !data->map.sprite_order
		|| !data->map.sprite_distance || data->map.sprite_count <= 0)
		return ;
	i = 0;
	while (i < data->map.sprite_count)
	{
		data->map.sprite_order[i] = i;
		i++;
	}
	i = 0;
	while (i < data->map.sprite_count - 1)
	{
		j = 0;
		while (j < data->map.sprite_count - i - 1)
		{
			if (data->map.sprite_distance[j] < data->map.sprite_distance[j + 1])
				ft_swap_sprites(data->map.sprite_order,
					data->map.sprite_distance, j, j + 1);
			j++;
		}
		i++;
	}
}
