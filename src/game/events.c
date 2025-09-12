#include "cub3d.h"

void	ft_move_forward(t_data *data);
void	ft_move_backward(t_data *data);
void	ft_strafe_left(t_data *data);
void	ft_strafe_right(t_data *data);
void	ft_rotate_left(t_data *data);
void	ft_rotate_right(t_data *data);

int	ft_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_close_window(data);
	else if (keycode == KEY_W)
		ft_move_forward(data);
	else if (keycode == KEY_S)
		ft_move_backward(data);
	else if (keycode == KEY_A)
		ft_strafe_left(data);
	else if (keycode == KEY_D)
		ft_strafe_right(data);
	else if (keycode == KEY_LEFT)
		ft_rotate_left(data);
	else if (keycode == KEY_RIGHT)
		ft_rotate_right(data);
	return (0);
}
