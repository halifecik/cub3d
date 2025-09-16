#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "structs.h"
# include "graphics.h"
# include "constants.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "../minilibx-linux/mlx.h"

// game

// graphics
int		ft_game_loop(t_data *data);
int		ft_key_press(int keycode, t_data *data);
int		ft_close_window(t_data *data);
void	ft_cleanup(t_data *data);

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
int		ft_initialize_graphics(t_data *data);
void	ft_initialize_config(t_config *config);

// parse
int	ft_cub_extension(char *filename);
int	ft_parse_map(t_data *data);
int	ft_check_map(t_map *map);

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
void	ft_calculate_side_dist(t_data *data, double *side_dist_x,
			double *side_dist_y);

void	ft_render_frame(t_data *data);

// graphics
int		ft_initialize_graphics(t_data *data);
void	ft_cleanup_graphics(t_data *data);

// game loop
int		ft_game_loop(t_data *data);
int		ft_handle_keypress(int keycode, t_data *data);
int		ft_handle_close(t_data *data);
void	ft_handle_keypress_2(int keycode, t_data *data);
void	ft_handle_rotation(int keycode, t_data *data);
int		ft_is_valid_position(t_data *data, double x, double y);

// utils
int	ft_is_whitespace(char c);
void	ft_rtrim(char *line);
int	is_line_empty(char *str);
char	**copy_grid(char **grid, int height);
void	free_grid(char **grid);
int	ft_print_error(char *msg);

#endif
