/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:45 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/26 19:24:01 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	ft_should_hit_door(t_data *data, int map_x, int map_y)
{
	double	door_state;
	double	hit_chance;

	door_state = ft_get_door_animation_state(data, map_x, map_y);
	if (door_state >= 0.98)
		return (0);
	hit_chance = 1.0 - door_state;
	return ((rand() % 100) < (int)(hit_chance * 100));
}

static int	ft_hit_wall_or_door(t_data *data, int map_x, int map_y)
{
	char	cell;

	if (map_x < 0 || map_y < 0 || map_x >= data->map.width
		|| map_y + data->map.map_index >= data->map.height)
		return (1);
	cell = data->map.grid[map_y + data->map.map_index][map_x];
	if (cell == '1')
		return (1);

	if (cell == 'D')
		return (ft_should_hit_door(data, map_x, map_y));

	return (0);
}

static void	ft_dda_algorithm(t_data *data)
{
	double		side_dist_x;
	double		side_dist_y;
	t_raycast	*ray;

	ray = &data->raycast;
	ft_calculate_step(data);
	ft_side_distance(data, &side_dist_x, &side_dist_y);
	while (ray->hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ft_hit_wall_or_door(data, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

void	ft_cast_ray(t_data *data, int x)
{
	ft_initialize_ray(data, x);
	ft_dda_algorithm(data);
	ft_wall_distance(data);
}
