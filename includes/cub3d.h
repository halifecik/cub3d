#ifndef CUB3D_H
# define CUB3D_H

# include "constants.h"
# include "structures.h"
# include "graphics.h"
# include "gnl/get_next_line.h"

/* init/init_structs */
int     init_data(t_data *data);

/* init/init_player */
void	init_player_location(t_data *data, t_map *map);

/* parser/parse_identifier */
int     is_identifier(char *line);
void    parse_identifier(char *line, t_config *config);

/* parser/parse_cube */
int     parse_map(t_data *data, char *filename);

/* parser/flood_fill */
void	reset_flood_fill(t_map *map);
void	flood_fill(t_map *map, int y, int x, int *valid);

/* parser/validate_map */
int	validate_map(t_map *map);

/* utils/parser_tools */
int	is_whitespace(char c);

/* main.c */
int     print_error(char *msg);

#endif
