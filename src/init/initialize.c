#include "cub3d.h"

int	ft_initialize_game(t_data *data)
{
	if (!data)
		return (1);
	ft_initialize_map(&data->map);
	ft_initialize_player(&data->player);
	ft_initialize_config(&data->config);
	return (0);
}
