#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "structs.h"

/* graphics/graphics_init.c */
int		load_textures(t_data *data);

/* raycasting/raycast_core.c */
void	cast_ray(t_data *data, int x);

/* raycasting/texture_calc.c */
void	calculate_texture_coordinates(t_data *data);
int		get_texture_color(t_data *data, int tex_y);

/* raycasting/render.c */
void	render_frame(t_data *data);

/* game/input_handler.c */
int		key_press(int keycode, t_data *data);

/* game/game_loop.c */
int		game_loop(t_data *data);
int		start_game(t_data *data);
int		exit_game(t_data *data);

#endif
