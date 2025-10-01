/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 18:23:46 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 18:26:44 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

// ========== Keys ============
typedef struct s_keys
{
	int			w;
	int			a;
	int			s;
	int			d;
	int			l;
	int			esc;
	int			left;
	int			right;
}				t_keys;

// ========== Map ===========
typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	int			map_index;
	char		player_dir;
}				t_map;

// ======== Player ===========
typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
}				t_player;

// ======== Texture ===========
typedef struct s_texture
{
	void		*img;
	char		*data;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_texture;

// ======= Graphics ===========
typedef struct s_graphics
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_texture	textures[4];
}				t_graphics;

// ======== Raycast ===========
typedef struct s_raycast
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
}				t_raycast;

// ===== Configuration =======
typedef struct s_config
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*wspc;
	int			floor_color;
	int			ceiling_color;
}				t_config;

// ======= Game Data ==========
typedef struct s_data
{
	t_map		map;
	t_keys		keys;
	int			frame;
	t_player	player;
	t_config	config;
	t_raycast	raycast;
	t_graphics	graphics;
	char		*map_file;
}				t_data;

#endif