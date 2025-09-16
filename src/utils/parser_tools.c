#include "cub3d.h"

#include <stdlib.h>
#include <string.h>

// ft_is_whitespace senin verdiğin fonksiyon
int	ft_is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

// Satırın sağındaki boşlukları kaldıran fonksiyon
void	ft_rtrim(char *str)
{
	int	len;

	if (!str)
		return;
	len = strlen(str) - 1;
	while (len >= 0 && ft_is_whitespace(str[len]))
	{
		str[len] = '\0';
		len--;
	}
}

int	is_line_empty(char *str)
{
	int	i;

	if (!str)
		return (0); // false
	i = 0;
	while (str[i])
	{
		if (!ft_is_whitespace(str[i]))
			return (0); // false
		i++;
	}
	return (1); // true
}
