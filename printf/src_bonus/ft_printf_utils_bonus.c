/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:40:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/04 20:17:53 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

void	ft_putunbr_fd(unsigned int nb, int fd)
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
	while (num > 0)
	{
		tab[i] = num % 10 + '0';
		num = num / 10;
		i++;
	}
	while (i > 0)
	{
		i--;
		ft_putchar_fd(tab[i], fd);
	}
}

// mode == 1 ; hexa lower form | mode == 0 ; hexa uper form
int	convert_base_ptr(unsigned long long n)
{
	char	*hexa_lo;
	char	buff[19];
	int		i;
	int		chr_cnt;

	i = 0;
	if (n == 0)
		return (ft_putstr_fd("(nil)", 1), 5);
	hexa_lo = "0123456789abcdef";
	while (n > 0)
	{
		buff[i++] = hexa_lo[n % 16];
		n /= 16;
	}
	chr_cnt = i + 2;
	ft_putstr_fd("0x", 1);
	while (--i >= 0)
		ft_putchar_fd(buff[i], 1);
	return (chr_cnt);
}

int	convert_base(unsigned int n, int mode)
{
	char	*hexa_up;
	char	*hexa_lo;
	char	buff[19];
	int		i;
	int		chr_cnt;

	i = 0;
	if (n == 0)
		return (ft_putchar_fd('0', 1), 1);
	hexa_lo = "0123456789abcdef";
	hexa_up = "0123456789ABCDEF";
	while (n > 0)
	{
		if (mode)
			buff[i++] = hexa_lo[n % 16];
		else
			buff[i++] = hexa_up[n % 16];
		n /= 16;
	}
	chr_cnt = i;
	while (--i >= 0)
		ft_putchar_fd(buff[i], 1);
	return (chr_cnt);
}

int	digit_cnt(long n)
{
	int	i;

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
