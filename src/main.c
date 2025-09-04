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

int main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
		return (print_error("argc is not enough!"), 0);
}
