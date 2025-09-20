/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hademirc <hademirc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 00:00:00 by hademirc          #+#    #+#             */
/*   Updated: 2025/09/20 17:42:18 by hademirc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_print_error(char *msg)
{
	int	i;

	i = 0;
	write(1, RED "Error: " YELLOW, 21);
	while (msg[i])
		write(1, &msg[i++], 1);
	write(1, "\n" RESET, 5);
	if (msg[0] == 97)
	{
		write(1, RED "\n============================\n", 37);
		write(1, "Usage: " MAGENTA "./cub3d maps/map.cub\n", 36);
		write(1, RED "============================\n" RESET, 40);
	}
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (ft_print_error("argc is not enough!"));
	if (ft_cub_extension(argv[1]))
		return (ft_print_error("File must have .cub extension"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_print_error("Failed to allocate t_data"));
	data->map_file = argv[1];
	if (ft_parse_map(data))
		return (ft_print_error("Failed to parse .cub file"));
	if (ft_initialize_graphics(data))
		return (ft_print_error("Failed to initialize graphics"));
	mlx_loop_hook(data->graphics.mlx, ft_game_loop, data);
	mlx_hook(data->graphics.window, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->graphics.window, 17, 1L << 17, ft_close_window, data);
	mlx_loop(data->graphics.mlx);
	return (EXIT_SUCCESS);
}
