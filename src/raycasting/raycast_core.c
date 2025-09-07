#include "cub3d.h"

static void	init_ray(t_data *data, int x)
{
	t_raycast	*ray;

	ray = &data->raycast;
	ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
	ray->ray_dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
	ray->map_x = (int)data->player.pos_x;
	ray->map_y = (int)data->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

static void	calculate_step_and_sidedist(t_data *data, double *side_dist_x,
	double *side_dist_y)
{
	t_raycast	*ray;

	ray = &data->raycast;
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		*side_dist_x = (data->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		*side_dist_x = (ray->map_x + 1.0 - data->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		*side_dist_y = (data->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		*side_dist_y = (ray->map_y + 1.0 - data->player.pos_y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_data *data)
{
	double	side_dist_x;
	double	side_dist_y;

	calculate_step_and_sidedist(data);
	if (data->raycast.ray_dir_x < 0)
		side_dist_x = (data->player.pos_x - data->raycast.map_x) * data->raycast.delta_dist_x;
	else
		side_dist_x = (data->raycast.map_x + 1.0 - data->player.pos_x) * data->raycast.delta_dist_x;
	if (data->raycast.ray_dir_y < 0)
		side_dist_y = (data->player.pos_y - data->raycast.map_y) * data->raycast.delta_dist_y;
	else
		side_dist_y = (data->raycast.map_y + 1.0 - data->player.pos_y) * data->raycast.delta_dist_y;
	while (data->raycast.hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += data->raycast.delta_dist_x;
			data->raycast.map_x += data->raycast.step_x;
			data->raycast.side = 0;
		}
		else
		{
			side_dist_y += data->raycast.delta_dist_y;
			data->raycast.map_y += data->raycast.step_y;
			data->raycast.side = 1;
		}
		if (data->map.grid[data->raycast.map_y][data->raycast.map_x] == '1')
			data->raycast.hit = 1;
	}
}

static void	calculate_wall_distance(t_data *data)
{
	if (data->raycast.side == 0)
		data->raycast.perp_wall_dist = (data->raycast.map_x - data->player.pos_x + (1 - data->raycast.step_x) / 2) / data->raycast.ray_dir_x;
	else
		data->raycast.perp_wall_dist = (data->raycast.map_y - data->player.pos_y + (1 - data->raycast.step_y) / 2) / data->raycast.ray_dir_y;
	data->raycast.line_height = (int)(SCREEN_HEIGHT / data->raycast.perp_wall_dist);
	data->raycast.draw_start = -data->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->raycast.draw_start < 0)
		data->raycast.draw_start = 0;
	data->raycast.draw_end = data->raycast.line_height / 2 + SCREEN_HEIGHT / 2;
	if (data->raycast.draw_end >= SCREEN_HEIGHT)
		data->raycast.draw_end = SCREEN_HEIGHT - 1;
}

void	cast_ray(t_data *data, int x)
{
	init_ray(data, x);
	perform_dda(data);
	calculate_wall_distance(data);
}
