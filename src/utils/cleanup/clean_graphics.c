/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_graphics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:08:53 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 17:09:10 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_clean_graphics(t_graphics *gfx)
{
	int	i;
	int	max_textures;

	if (!gfx)
		return ;
# ifdef BONUS
	max_textures = 12;
# else
	max_textures = 4;
# endif
	i = 0;
	while (i < max_textures)
	{
		if (gfx->textures[i].img)
			mlx_destroy_image(gfx->mlx, gfx->textures[i].img);
		i++;
	}
	if (gfx->img)
		mlx_destroy_image(gfx->mlx, gfx->img);
	if (gfx->window)
		mlx_destroy_window(gfx->mlx, gfx->window);
	if (gfx->mlx)
		mlx_destroy_display(gfx->mlx);
	free(gfx->mlx);
}
