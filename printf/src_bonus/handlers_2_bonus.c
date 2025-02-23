/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:05:03 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/04 20:17:15 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	x_handler(va_list args)
{
	unsigned int	n;

	n = (unsigned int)va_arg(args, int);
	return (convert_base(n, 1));
}

int	up_x_handler(va_list args)
{
	unsigned int	n;

	n = (unsigned int)va_arg(args, int);
	return (convert_base(n, 0));
}
