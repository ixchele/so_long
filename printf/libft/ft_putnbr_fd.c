/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:15:27 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/15 19:16:16 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	glb(char *tab, size_t i, int fd)
{
	while (i > 0)
	{
		i--;
		ft_putchar_fd(tab[i], fd);
	}
}

void	ft_putnbr_fd(int nb, int fd)
{
	char		tab[666];
	size_t		i;
	long int	num;

	i = 0;
	num = (long int)nb;
	if (num == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num = -num;
	}
	while (num > 0)
	{
		tab[i] = num % 10 + '0';
		num = num / 10;
		i++;
	}
	glb(tab, i, fd);
}
