#ifndef CUB3D_H
# define CUB3D_H

# include "constants.h"
# include "structures.h"
# include "graphics.h"

/* utils/initiliaze */
int	init_data(t_data *data);

/* parser/parse_identifier */
int     is_identifier(char *line);
void    parse_identifier(char *line, t_config *config);

/* parser/parse_cube */
int	parse_cub(t_data *data, char *filename);

#endif
