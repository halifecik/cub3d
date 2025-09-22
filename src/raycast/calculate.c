/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 19:37:43 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 21:24:48 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calculate_step(t_data *data)
{
	t_raycast	*ray;

	ray = &data->raycast;
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

void	ft_side_distance(t_data *data, double *side_dist_x, double *side_dist_y)
{
	t_raycast	*ray;

	ray = &data->raycast;
	if (ray->ray_dir_x < 0)
		*side_dist_x = (data->player.pos_x - ray->map_x) * ray->delta_dist_x;
	else
		*side_dist_x = (ray->map_x + 1.0 - data->player.pos_x)
			* ray->delta_dist_x;
	if (ray->ray_dir_y < 0)
		*side_dist_y = (data->player.pos_y - ray->map_y) * ray->delta_dist_y;
	else
		*side_dist_y = (ray->map_y + 1.0 - data->player.pos_y)
			* ray->delta_dist_y;
}

void	ft_calculate_side_dist(t_data *data, double *side_dist_x,
	double *side_dist_y)
{
	ft_side_distance(data, side_dist_x, side_dist_y);
}

void	ft_wall_distance(t_data *data)
{
	t_raycast	*ray;

	ray = &data->raycast;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.pos_x + (1
					- ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.pos_y + (1
					- ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(VIEWPORT_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + VIEWPORT_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + VIEWPORT_HEIGHT / 2;
	if (ray->draw_end >= VIEWPORT_HEIGHT)
		ray->draw_end = VIEWPORT_HEIGHT - 1;
}

void	ft_wall_x(t_data *data)
{
	t_raycast	*ray;

	ray = &data->raycast;
	if (ray->side == 0)
		ray->wall_x = data->player.pos_y + ray->perp_wall_dist
			* ray->ray_dir_y;
	else
		ray->wall_x = data->player.pos_x + ray->perp_wall_dist
			* ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}

void	ft_texture_x(t_data *data)
{
	int			tex_width;
	t_raycast	*ray;

	ray = &data->raycast;
	tex_width = data->graphics.textures[ray->tex_num].width;
	ray->tex_x = (int)(ray->wall_x * (double)tex_width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = tex_width - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = tex_width - ray->tex_x - 1;
}