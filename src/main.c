#include "cub3d.h"

int	ft_print_error(char *msg)
{
	int i = 0;

	write(1, "Error: ", 7);
	while (msg[i])
		write(1, &msg[i++], 1);
	write(1, "\n", 1);
	return (EXIT_FAILURE);
}

static int	ft_initiliaze_data(t_data *data, char *file)
{
	data = malloc(sizeof(t_data));
	if(!data)
		return (1);
	data->map_file = file;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc != 2)
		return (ft_print_error("argc is not enough!"));
	if (ft_cub_extension(argv[1]))
		return (ft_print_error("File must have .cub extension"));
	if (ft_initiliaze_data(data, argv[1]))
		return (ft_print_error("Failed to allocate t_data"));
	if (ft_parse_map(data))
		return (ft_print_error("Failed to parse .cub file"));
	ft_initialize_player_location(data, &data->map);
	if (ft_initialize_graphics(data))
		return (ft_print_error("Failed to initialize graphics"));
	mlx_loop_hook(data->graphics.mlx, ft_game_loop, data);
	mlx_hook(data->graphics.window, 2, 1L << 0, ft_key_press, data);
	mlx_hook(data->graphics.window, 17, 1L << 17, ft_close_window, data);
	mlx_loop(data->graphics.mlx);
	return (EXIT_SUCCESS);
}
