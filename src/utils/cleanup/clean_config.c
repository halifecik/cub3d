#include "cub3d.h"

void	ft_clean_config(t_config *config)
{
	if (!config)
		return ;
	if (config->north_texture)
		free(config->north_texture);
	if (config->south_texture)
		free(config->south_texture);
	if (config->west_texture)
		free(config->west_texture);
	if (config->east_texture)
		free(config->east_texture);
}
