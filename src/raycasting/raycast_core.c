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

static int	is_wall_hit(t_data *data, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= data->map.width || map_y < 0
		|| map_y >= data->map.height)
		return (1);
	if (data->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	perform_dda(t_data *data)
{
	double		side_dist_x;
	double		side_dist_y;
	t_raycast	*ray;

	ray = &data->raycast;
	calculate_step_and_sidedist(data, &side_dist_x, &side_dist_y);
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
		if (is_wall_hit(data, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

static void	calculate_wall_distance(t_data *data)
{
	t_raycast	*ray;

	ray = &data->raycast;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - data->player.pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - data->player.pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	cast_ray(t_data *data, int x)
{
	init_ray(data, x);
	perform_dda(data);
	calculate_wall_distance(data);
}
