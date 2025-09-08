#include "cub3d.h"

static int	ft_hit_wall(t_data *data, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_x >= data->map.width
		|| map_y >= data->map.height)
		return (1);
	if (data->map.grid[map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	ft_dda_algorithm(t_data *data)
{
	double		side_dist_x;
	double		side_dist_y;
	t_raycast	*ray;

	ray = &data->raycast;
	ft_calculate_step(data);
	ft_calculate_side_dist(data, &side_dist_x, &side_dist_y);
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
		if (ft_hit_wall(data, ray->map_x, ray->map_y))
			ray->hit = 1;
	}
}

void	ft_cast_ray(t_data *data, int x)
{
	ft_initialize_ray(data, x);
	ft_dda_algorithm(data);
	ft_wall_distance(data);
}
