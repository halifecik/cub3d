#ifndef CUB3D_H
# define CUB3D_H

# include "constants.h"
# include "gnl/get_next_line.h"
# include "graphics.h"
# include "libft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

// game

// init
void	ft_player_east(t_data *data);
void	ft_player_west(t_data *data);
void	ft_player_north(t_data *data);
void	ft_player_south(t_data *data);
void	ft_initialize_player(t_player *player);
void	ft_initialize_player_location(t_data *data, t_map *map);
void	ft_initialize_ray(t_data *data, int x);
void    ft_initialize_map(t_map *map);
int		ft_initialize_game(t_data *data);

// parse
void	ft_flood_fill(t_map *map, int y, int x, int *valid);
void	ft_reset_flood_fill(t_map *map);
int		ft_is_identifier(char *line);
void	ft_parse_identifier(char *line, t_config *config);
int		ft_validate_map(t_map *map);

int		ft_parse_map(t_data *data, char *filename);

// raycast
void	ft_calculate_step(t_data *data);
void	ft_wall_distance(t_data *data);
void	ft_wall_x(t_data *data);
void	ft_texture_x(t_data *data);
void	ft_cast_ray(t_data *data, int x);
void	ft_texture_coordinates(t_data *data);
int		ft_texture_color(t_data *data, int tex_y);
void	ft_side_distance(t_data *data, double *side_dist_x,
			double *side_dist_y);

void	ft_render_frame(t_data *data);

// utils
int	ft_is_whitespace(char c);

#endif
