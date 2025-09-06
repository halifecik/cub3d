#include "cub3d.h"

int	print_error(char *msg)
{
	int i = 0;

	write(1, "Error\n", 6);
	while (msg[i])
		write(1, &msg[i++], 1);
	write(1, "\n", 1);
	return (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (print_error("argc is not enough!"));
	if (!has_cub_extension(argv[1]))
		return (print_error("File must have .cub extension"));
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("Failed to allocate t_data"));
	data->map_file = argv[1];
	if (init_data(data))
		return (print_error("Failed to initialize data"));
	if (parse_cub(data->map_file, data))
		return (print_error("Failed to parse .cub file"));
	return (EXIT_SUCCESS);
}
