#include "cub3d.h"

void	print_error(char *msg)
{
	int i;

	i = -1;
	write(1, "Error\n", 6);
	while(msg[++i])
		write(1, msg[i], 1);
	write(1, '\n', 1);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (print_error("argc is not enough!"), EXIT_FAILURE);
	if (!has_cub_extension(argv[1]))
		return (print_error("File must have .cub extension"), EXIT_FAILURE);
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error("Failed to allocate t_data"), EXIT_FAILURE);
	data->map_file = argv[1];
	if (init_data(data))
		return (print_error("Failed to initialize data"), EXIT_FAILURE);
	if (parse_cub(data->map_file, data))
		return (print_error("Failed to parse .cub file"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
