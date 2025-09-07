#include "cub3d.h"

static void	init_player(t_player *player)
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

static void	player_north(t_data *data)
{
	data->player.dir_x = -1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = 0.66;
}

static void	player_south(t_data *data)
{
	data->player.dir_x = 1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = -0.66;
}

static void	player_east(t_data *data)
{
	data->player.dir_x = 0.0;
	data->player.dir_y = 1.0;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0.0;
}

static void	player_west(t_data *data)
{
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0.0;
}

void	init_player_location(t_data *data, t_map *map)
{
	data->player.pos_x = map->player_x + 0.5;
	data->player.pos_y = map->player_y + 0.5;
	data->player.move_speed = MOVE_SPEED;
	data->player.rot_speed = ROT_SPEED;

	if (map->player_dir == 'N')
		player_north(data);
	else if (map->player_dir == 'S')
		player_south(data);
	else if (map->player_dir == 'E')
		player_east(data);
	else if (map->player_dir == 'W')
		player_west(data);
}
