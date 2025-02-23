/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 09:36:45 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/11 18:03:38 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	val_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static size_t	digit_cnt(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i = 1;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_inv(char *str)
{
	size_t		i;
	size_t		j;
	char		x;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	i--;
	while (i > j)
	{
		x = str[i];
		str[i] = str[j];
		str[j] = x;
		i--;
		j++;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	size_t		i;
	char		*ptr;
	int			n_index;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = 0;
	n_index = n;
	ptr = malloc(sizeof(char) * (digit_cnt(n) + 1));
	if (!ptr)
		return (NULL);
	while (n_index)
	{
		ptr[i] = val_abs(n_index % 10) + '0';
		n_index /= 10;
		i++;
	}
	if (n < 0)
		ptr[digit_cnt(n) - 1] = '-';
	ptr[digit_cnt(n)] = '\0';
	return (ft_inv(ptr));
}
