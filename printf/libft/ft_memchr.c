/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:00:41 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/09 09:44:28 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	chr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	chr = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == chr)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
