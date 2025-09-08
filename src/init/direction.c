#include "cub3d.h"

void	ft_player_north(t_data *data)
{
	data->player.dir_x = -1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = 0.66;
}

void	ft_player_south(t_data *data)
{
	data->player.dir_x = 1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = -0.66;
}

void	ft_player_east(t_data *data)
{
	data->player.dir_x = 0.0;
	data->player.dir_y = 1.0;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0.0;
}

void	ft_player_west(t_data *data)
{
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0.0;
}
