#include "cub3d.h"

static void	init_player(t_player *p)
{
	p->pos_x = -1;
	p->pos_y = -1;
	p->dir_x = 0;
	p->dir_y = 0;
	p->plane_x = 0;
	p->plane_y = 0;
	p->move_speed = 0.08;
	p->rot_speed = 0.05;
}

static void	init_map(t_map *m)
{
	m->grid = NULL;
	m->width = 0;
	m->height = 0;
	m->player_x = -1;
	m->player_y = -1;
	m->player_dir = '\0';
}

static void	init_config(t_config *c)
{
	c->north_texture = NULL;
	c->south_texture = NULL;
	c->west_texture = NULL;
	c->east_texture = NULL;
	c->floor_color = -1;
	c->ceiling_color = -1;
}

static void	init_graphics(t_graphics *g)
{
    int i;

	i = 0;
    g->mlx = NULL;
	g->window = NULL;
	g->img = NULL;
	g->img_data = NULL;
	g->bits_per_pixel = 0;
	g->line_length = 0;
	g->endian = 0;

	while (i < 4)
	{
		g->textures[i].img = NULL;
		g->textures[i].data = NULL;
		g->textures[i].width = 0;
		g->textures[i].height = 0;
		g->textures[i].bits_per_pixel = 0;
		g->textures[i].line_length = 0;
		g->textures[i].endian = 0;
		i++;
	}
}

static void	init_raycast(t_raycast *r)
{
	r->camera_x = 0;
	r->ray_dir_x = 0;
	r->ray_dir_y = 0;
	r->map_x = 0;
	r->map_y = 0;
	r->delta_dist_x = 0;
	r->delta_dist_y = 0;
	r->perp_wall_dist = 0;
	r->step_x = 0;
	r->step_y = 0;
	r->hit = 0;
	r->side = 0;
	r->line_height = 0;
	r->draw_start = 0;
	r->draw_end = 0;
	r->tex_num = 0;
	r->wall_x = 0;
	r->tex_x = 0;
}

int	init_data(t_data *data)
{
	if (!data)
		return (1);
	init_player(&data->player);
	init_map(&data->map);
	init_config(&data->config);
	init_graphics(&data->graphics);
	init_raycast(&data->raycast);
	return (0);
}
