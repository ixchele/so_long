/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:57:19 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/04 20:18:10 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"
#include "libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

int	converter_1(char c, va_list args)
{
	size_t				i;
	static t_converters	func_tab[] = {
	{'c', c_handler},	
	{'s', s_handler},	
	{'d', d_handler},	
	{'p', p_handler},	
	{'x', x_handler},	
	{'X', up_x_handler},
	{'u', u_handler},
	{'i', d_handler},
	{'\0', NULL}};

	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	i = 0;
	while (func_tab[i].c)
	{
		if (func_tab[i].c == c)
			return (func_tab[i].f(args));
		i++;
	}
	return (0);
}

int	parse_flags(t_state *state)
{
	int (n) = va_arg(state->args, int);
	if (state->fmt[state->i] == '+')
	{
		while (state->fmt[state->i] == '+')
			state->i++;
		if (n >= 0)
			return (write(1, "+", 1));
	}
	else if (state->fmt[state->i] == '#')
	{
		while (state->fmt[state->i] == '#')
			state->i++;
		if (n == 0)
			return (0);
		if (state->fmt[state->i] == 'x' || state->fmt[state->i] == 'X')
			return (write(1, "0", 1) + write(1, &state->fmt[state->i], 1));
	}
	else if (state->fmt[state->i] == ' ')
	{
		while (state->fmt[state->i] == ' ')
			state->i++;
		if (n >= 0)
			return (write(1, " ", 1));
	}
	return (0);
}

void	init(t_state *s, const char *b, va_list *args)
{
	s->fmt = b;
	s->i = 0;
	va_copy(s->args, *args);
}

int	ft_printf(const char *buff, ...)
{
	va_list	args;
	t_state	state;

	int (chr_cnt) = 0;
	if (!buff)
		return (-1);
	va_start(args, buff);
	init(&state, buff, &args);
	while (state.fmt[state.i])
	{
		if (state.fmt[state.i] == '%')
		{
			state.i++;
			chr_cnt += parse_flags(&state);
			chr_cnt += converter_1(state.fmt[state.i++], args);
		}
		else
		{
			ft_putchar_fd(state.fmt[state.i++], 1);
			chr_cnt += 1;
		}
	}
	return (chr_cnt);
}
