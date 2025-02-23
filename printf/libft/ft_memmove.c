/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:09:21 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/15 19:28:37 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest > src)
		while (n-- > 0)
			*(unsigned char *)(dest + n) = *(unsigned char *)(src + n);
	else if (dest < src)
	{
		i = -1;
		while (++i < n)
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
	}
	return (dest);
}
