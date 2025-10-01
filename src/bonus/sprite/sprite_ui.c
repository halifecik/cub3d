/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 21:30:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/01 17:53:47 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	ft_draw_bold_text(t_data *data, int x, int y, char *text)
{
	int	color;
	int	i;
	int	j;

	color = WHITE_PIXEL;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			mlx_string_put(data->graphics.mlx, data->graphics.window,
				x + i, y + j, color, text);
			j++;
		}
		i++;
	}
}

void	ft_draw_coin_counter(t_data *data)
{
	char	*coin_text;
	char	*total_text;
	int		text_x;
	int		text_y;

	coin_text = ft_create_coin_text(data->coins_collected);
	total_text = ft_strjoin("Total Coins: ", ft_itoa(data->map.sprite_count));
	if (!coin_text)
		return ;
	text_x = 5;
	text_y = 20;
	ft_draw_bold_text(data, text_x, text_y, coin_text);
	ft_draw_bold_text(data, 5, 40, total_text);
	free(coin_text);
	free(total_text);
}
