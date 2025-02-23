/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:05:03 by zbengued          #+#    #+#             */
/*   Updated: 2024/12/01 20:05:34 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
