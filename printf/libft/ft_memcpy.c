/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 09:45:05 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/14 16:51:51 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptrs;
	unsigned char	*ptrd;

	if (!dest && !src)
		return (NULL);
	if (dest == src)
		return (dest);
	ptrs = (unsigned char *)src;
	ptrd = (unsigned char *)dest;
	i = 0;
	while (i++ < n)
		ptrd[i - 1] = ptrs[i - 1];
	return (dest);
}
