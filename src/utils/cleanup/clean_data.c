#include "cub3d.h"

void	ft_clean_data(t_data *data)
{
	if (!data)
		return ;
	if (data->map.grid || data->map.doors)
		ft_clean_map(&data->map);
	ft_clean_config(&data->config);
	ft_clean_graphics(&data->graphics);
}

int    ft_close_window(t_data *data)
{
	ft_clean_data(data);
	exit(EXIT_SUCCESS);
    return (0);
}
