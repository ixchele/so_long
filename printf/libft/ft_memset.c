/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:56:12 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/15 19:36:40 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*ptr;
	size_t				i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
		ptr[i++] = (unsigned char)c;
	return (s);
}
