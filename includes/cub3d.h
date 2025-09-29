/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:23:44 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 17:05:10 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "constants.h"
# include "structs.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

// game

// graphics
int		ft_game_loop(t_data *data);
int		ft_key_press(int keycode, t_data *data);
int		ft_key_release(int keycode, t_data *data);
int		ft_mouse_press(int button, int x, int y, t_data *data);
int		ft_mouse_move(int x, int y, t_data *data);

// movement
void	ft_move_forward(t_data *data);
void	ft_move_backward(t_data *data);
void	ft_strafe_left(t_data *data);
void	ft_strafe_right(t_data *data);
void	ft_rotate_left(t_data *data);
void	ft_rotate_right(t_data *data);

// init
void	ft_player_east(t_data *data);
void	ft_player_west(t_data *data);
void	ft_player_north(t_data *data);
void	ft_player_south(t_data *data);
void	ft_initialize_map(t_map *map);
void	ft_initialize_ray(t_data *data, int x);
void	ft_initialize_config(t_config *config);
int		ft_initialize_graphics(t_data *data);
int		ft_set_player_location(t_data *data, t_map *map);

void	ft_initialize_minimap(t_minimap *minimap);
int		ft_check_config_complete(t_config *config);
int		ft_set_config(t_map *map, t_config *config);

// parse
int		ft_check_map(t_map *map);
int		ft_parse_map(t_data *data);
int		ft_cub_extension(char *filename);
int		ft_parse_color_value(char *str, int *value);

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

// graphics
int		ft_initialize_graphics(t_data *data);

// game loop
int		ft_game_loop(t_data *data);

// utils
void	ft_rtrim(char *line);
int		ft_is_whitespace(char c);
void	ft_free_grid(char **grid);
int		ft_print_error(char *msg);
char	**ft_copy_map_lines(t_map *map, int *cpy_height);

//cleanup
void	ft_clean_map(t_map *map);
void	ft_clean_data(t_data *data);
int		ft_close_window(t_data *data);
void	ft_clean_config(t_config *config);
void	ft_clean_graphics(t_graphics *gfx);

// minimap
int		ft_tile_color(char tile);
void	ft_draw_minimap(t_data *data);
void	ft_draw_full_map(t_data *data);
void	ft_draw_pixel(t_data *data, int x, int y, int color);
void	ft_draw_cell(t_data *data, int start_x, int start_y, int size);
void	ft_draw_colored_cell(t_data *data, int start_x, int start_y, int color);
void	ft_draw_frame(t_data *data, int start_x, int start_y, int width);

// doors
void	ft_initialize_doors(t_map *map);
void	ft_update_doors(t_data *data);
void	ft_interact_with_door(t_data *data);
int		ft_door_at_position(t_data *data, int x, int y);
double	ft_get_door_animation_state(t_data *data, int x, int y);
t_door	*ft_find_closest_door(t_data *data);
int		ft_player_on_door(t_data *data, t_door *door);

#endif
