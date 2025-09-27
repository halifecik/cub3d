#include "cub3d.h"

static  void	ft_door_action_logic(t_door *door)
{
	if (door->animation_state <= DOOR_CLOSED + 0.1)
	{
		door->is_opening = 1;
		door->is_closing = 0;
	}
	else if (door->animation_state >= DOOR_OPEN - 0.1)
	{
		door->is_closing = 1;
		door->is_opening = 0;
	}
	else
	{
		if (door->animation_state < 0.5)
		{
			door->is_opening = 1;
			door->is_closing = 0;
		}
		else
		{
			door->is_closing = 1;
			door->is_opening = 0;
		}
	}
}

void	ft_interact_with_door(t_data *data)
{
	t_door	*door;

	door = ft_find_closest_door(data);
	if (!door)
		return ;
	if (ft_is_player_on_door(data, door))
		return ;
	if (door->is_opening || door->is_closing)
		return ;
	ft_door_action_logic(door);
}

int	ft_is_door_at_position(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		if (data->map.doors[i].x == x && data->map.doors[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

double	ft_get_door_animation_state(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->map.door_count)
	{
		if (data->map.doors[i].x == x && data->map.doors[i].y == y)
			return (data->map.doors[i].animation_state);
		i++;
	}
	return (DOOR_CLOSED);
}
