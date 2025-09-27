#include "cub3d.h"

static int	ft_is_player_on_door(t_data *data, t_door *door)
{
	double px = data->player.pos_x;
	double py = data->player.pos_y;

	// Kapının sınırları: kapı kare merkezinden 0.5 birim yarıçap
	if (px >= door->x - 0.2 && px <= door->x + 1.2 &&
		py >= door->y - 0.2 && py <= door->y + 1.2)
		return (1); // Player kapının kare alanında
	return (0);
}

static double	ft_distance_to_door(t_data *data, int door_x, int door_y)
{
	double	dx;
	double	dy;

	dx = data->player.pos_x - door_x - 0.5;
	dy = data->player.pos_y - door_y - 0.5;
	return (sqrt(dx * dx + dy * dy));
}

static t_door	*ft_find_closest_door(t_data *data)
{
	int		i;
	double	min_distance;
	double	distance;
	t_door	*closest_door;

	if (data->map.door_count == 0)
		return (NULL);
	closest_door = NULL;
	min_distance = DOOR_INTERACTION_RANGE + 1.0;
	i = 0;
	while (i < data->map.door_count)
	{
		distance = ft_distance_to_door(data, data->map.doors[i].x,
				data->map.doors[i].y);
		if (distance < min_distance && distance <= DOOR_INTERACTION_RANGE)
		{
			min_distance = distance;
			closest_door = &data->map.doors[i];
		}
		i++;
	}
	return (closest_door);
}
