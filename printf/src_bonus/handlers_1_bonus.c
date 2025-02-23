/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_1_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:41:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/04 20:17:35 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	c_handler(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar_fd(c, 1);
	return (1);
}

int	s_handler(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		return (ft_putstr_fd("(null)", 1), 6);
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	d_handler(va_list args)
{
	int	n;

	n = va_arg(args, int);
	ft_putnbr_fd(n, 1);
	return (digit_cnt(n));
}

int	u_handler(va_list args)
{
	unsigned int	n;

	n = (unsigned int)va_arg(args, int);
	ft_putunbr_fd(n, 1);
	return (digit_cnt(n));
}

int	p_handler(va_list args)
{
	void	*ptr;

	ptr = va_arg(args, void *);
	return (convert_base_ptr((unsigned long long)ptr));
}
