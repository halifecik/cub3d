/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:30:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/29 22:02:42 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_draw_text_background(t_data *data, int x, int y, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < 25)
	{
		j = 0;
		while (j < width)
		{
			ft_put_pixel(data, x + j, y + i, 0x000000);
			j++;
		}
		i++;
	}
}

static char	*ft_create_coin_text(int coins_collected)
{
	char	*coins_str;
	char	*temp;
	char	*result;

	coins_str = ft_itoa(coins_collected);
	if (!coins_str)
		return (NULL);
	temp = ft_strjoin("Coins Collected: ", coins_str);
	free(coins_str);
	if (!temp)
		return (NULL);
	result = ft_strdup(temp);
	free(temp);
	return (result);
}

void	ft_draw_coin_counter(t_data *data)
{
	char	*coin_text;
	int		text_x;
	int		text_y;
	int		text_width;

	coin_text = ft_create_coin_text(data->coins_collected);
	if (!coin_text)
		return ;
	text_width = ft_strlen(coin_text) * 8;
	text_x = SCREEN_WIDTH - text_width - 20;
	text_y = 20;
	ft_draw_text_background(data, text_x - 5, text_y - 5, text_width + 10);
	mlx_string_put(data->graphics.mlx, data->graphics.window,
		text_x, text_y + 15, WHITE_PIXEL, coin_text);
	free(coin_text);
}
