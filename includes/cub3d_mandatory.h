/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:23:44 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 20:33:32 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "constants.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// ========= Cleanup ==========
void	ft_clean_map(t_map *map);
void	ft_clean_data(t_data *data);
int		ft_close_window(t_data *data);
void	ft_clean_config(t_config *config);
void	ft_clean_graphics(t_graphics *gfx);

// ======== Game Loop =========
int		ft_game_loop(t_data *data);
int		ft_key_press(int keycode, t_data *data);
int		ft_key_release(int keycode, t_data *data);

// ========= Graphics =========
int		ft_initialize_graphics(t_data *data);
void	ft_put_pixel(t_data *data, int x, int y, int color);
int		ft_load_texture(t_data *data, char *path, int tex_index);

// =========== Init ===========
void	ft_player_east(t_data *data);
void	ft_player_west(t_data *data);
void	ft_player_north(t_data *data);
void	ft_player_south(t_data *data);
void	ft_initialize_map(t_map *map);
void	ft_initialize_ray(t_data *data, int x);
void	ft_initialize_config(t_config *config);
int		ft_check_config_complete(t_config *config);
int		ft_set_config(t_map *map, t_config *config);
int		ft_set_player_location(t_data *data, t_map *map);

// ========= Movement ==========
void	ft_strafe_left(t_data *data);
void	ft_rotate_left(t_data *data);
void	ft_move_forward(t_data *data);
void	ft_strafe_right(t_data *data);
void	ft_rotate_right(t_data *data);
void	ft_move_backward(t_data *data);

// ========== Parse ===========
int		ft_check_map(t_map *map);
int		ft_parse_map(t_data *data);
int		ft_cub_extension(char *filename);

// ========= Raycast ==========
void	ft_wall_x(t_data *data);
void	ft_texture_x(t_data *data);
void	ft_render_frame(t_data *data);
void	ft_wall_distance(t_data *data);
void	ft_calculate_step(t_data *data);
void	ft_cast_ray(t_data *data, int x);
void	ft_texture_coordinates(t_data *data);
int		ft_texture_color(t_data *data, int tex_y);
void	ft_side_distance(t_data *data, double *side_dist_x,
			double *side_dist_y);

// ========== Utils ===========
void	ft_rtrim(char *line);
int		ft_is_whitespace(char c);
char	*ft_str_whitespace(void);
void	ft_free_grid(char **grid);
int		ft_print_error(char *msg);
int		ft_parse_color_value(char *str, int *value);
char	**ft_copy_map_lines(t_map *map, int *cpy_height);

#endif