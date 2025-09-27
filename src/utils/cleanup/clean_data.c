#include "cub3d.h"

void	clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->map.grid || data->map.doors)
		clean_map(&data->map);
	clean_config(&data->config);
	clean_graphics(&data->graphics);
}

int    ft_close_window(t_data *data)
{
	clean_data(data);
	exit(EXIT_SUCCESS);
    return (0);
}
