#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include "constants.h"
# include "structs.h"
# include "graphics.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"

// game

// init
void	ft_player_east(t_data *data);
void	ft_player_west(t_data *data);
void	ft_player_north(t_data *data);
void	ft_player_south(t_data *data);
void	ft_initialize_player(t_player *player);
void	ft_initialize_player_location(t_data *data, t_map *map);
void	ft_initialize_ray(t_data *data, int x);

int	ft_initialize_game(t_data *data);

// parse

// raycast

// utils



#endif
