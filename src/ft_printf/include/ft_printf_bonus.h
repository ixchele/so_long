/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:41:26 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/04 20:18:44 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

# include "libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h> 

typedef struct s_state
{
	va_list		args;
	const char	*fmt;
	size_t		i;
}	t_state;

typedef struct s_converters
{
	int	c;
	int	(*f)(va_list);
}	t_converters;

int		ft_printf(const char *buff, ...);

int		c_handler(va_list args);
int		s_handler(va_list args);
int		d_handler(va_list args);
int		p_handler(va_list args);
int		up_x_handler(va_list args);
int		x_handler(va_list args);
int		u_handler(va_list args);

void	ft_putunbr_fd(unsigned int nb, int fd);
int		digit_cnt(long n);
int		convert_base(unsigned int n, int mode);
int		convert_base_ptr(unsigned long long n);
void	ft_putunbr_fd(unsigned int nb, int fd);
int		parse_flags(t_state *state);
int		converter_1(char c, va_list args);

#endif
