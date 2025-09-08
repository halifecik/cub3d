#include "cub3d.h"

void	ft_initialize_player(t_player *player)
{
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->move_speed = MOVE_SPEED;
	player->rot_speed = ROT_SPEED;
}

void	ft_initialize_player_location(t_data *data, t_map *map)
{
	data->player.pos_x = map->player_x + 0.5;
	data->player.pos_y = map->player_y + 0.5;
	data->player.move_speed = MOVE_SPEED;
	data->player.rot_speed = ROT_SPEED;
	if (map->player_dir == 'N')
		ft_player_north(data);
	else if (map->player_dir == 'S')
		ft_player_south(data);
	else if (map->player_dir == 'E')
		ft_player_east(data);
	else if (map->player_dir == 'W')
		ft_player_west(data);
}
