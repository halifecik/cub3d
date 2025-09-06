/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mugenan <mugenan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 23:00:34 by mugenan           #+#    #+#             */
/*   Updated: 2024/11/06 14:18:24 by mugenan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	into(char *str, int n, int len)
{
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	if (n > 9)
	{
		into(str, n / 10, len - 1);
		into(str, n % 10, len);
	}
	if (n < 10)
		str[len] = n + 48;
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = length(n);
	str = malloc((sizeof(char) * len) + 1);
	if (!str)
		return (NULL);
	into(str, n, len - 1);
	str[len] = '\0';
	return (str);
}
