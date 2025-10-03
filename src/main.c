/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:42:01 by hademirc          #+#    #+#             */
/*   Updated: 2025/10/03 13:53:27 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_perror(char *msg)
{
	int	i;

	i = 0;
	write(1, RED "Error: " YELLOW, 21);
	while (msg[i])
		write(1, &msg[i++], 1);
	write(1, "\n" RESET, 5);
	if (msg[0] == 97)
		write(1, RED "Usage: " MAGENTA "./cub3d maps/map.cub\n", 43);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_perror("argc is not enough!"));
	if (ft_cub_extension(argv[1]))
		return (ft_perror("File must have .cub extension"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_perror("Failed to allocate t_data"));
	data->map_file = argv[1];
	data->frame = 0;
	data->coins_collected = 0;
	ft_bzero(&data->keys, sizeof(t_keys));
	if (ft_parse_map(data))
		return (ft_clean_map(&data->map), free(data), 1);
	if (ft_initialize_graphics(data))
		return (ft_perror("Failed to initialize graphics"));
	ft_initialize_sprites(data);
	mlx_loop_hook(data->graphics.mlx, ft_game_loop, data);
	mlx_hook(data->graphics.window, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->graphics.window, 3, 1L << 1, ft_key_release, data);
	mlx_hook(data->graphics.window, 6, 1L << 6, ft_mouse_move, data);
	mlx_hook(data->graphics.window, 17, 1L << 17, ft_close_window, data);
	mlx_loop(data->graphics.mlx);
	return (SUCCESS);
}
