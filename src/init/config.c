#include "cub3d.h"

void	ft_initialize_config(t_config *config)
{
	config->north_texture = NULL;
	config->south_texture = NULL;
	config->west_texture = NULL;
	config->east_texture = NULL;
	config->floor_color = 0;
	config->ceiling_color = 0;
}
