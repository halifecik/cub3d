#ifndef STRUCTURES_H
# define STRUCTURES_H

/* Forward declarations */
typedef struct s_texture	t_texture;
typedef struct s_player		t_player;
typedef struct s_map		t_map;
typedef struct s_config		t_config;
typedef struct s_graphics	t_graphics;
typedef struct s_raycast	t_raycast;
typedef struct s_game		t_game;

/* Texture structure */
struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

/* Player structure */
struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
};

/* Map structure */
struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
};

/* Configuration structure */
struct s_config
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
};

/* Graphics structure */
struct s_graphics
{
	void		*mlx;
	void		*window;
	void		*img;
	char		*img_data;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_texture	textures[4];
};

/* Raycasting structure */
struct s_raycast
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
};

/* Main game structure */
struct s_game
{
	t_player	player;
	t_map		map;
	t_graphics	graphics;
	t_config	config;
	t_raycast	raycast;
};

#endif
