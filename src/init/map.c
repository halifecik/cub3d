#include "cub3d.h"

void	ft_initialize_map(t_map *map)
{
    if (!map)
        return;
    map->grid = NULL;
    map->width = 0;
    map->height = 0;
    map->map_index = 0;
    map->player_x = -1;
    map->player_y = -1;
    map->player_dir = '\0';
}
