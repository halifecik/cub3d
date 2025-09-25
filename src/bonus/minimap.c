#include "cub3d.h"

void    ft_initialize_minimap(t_minimap *minimap)
{
    minimap->cell_size = 10;
    minimap->visible_cells = 9;
    minimap->width = minimap->cell_size * minimap->visible_cells;
    minimap->height = minimap->width;
}