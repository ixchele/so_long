/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:39:41 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/09 09:55:00 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	y;

	if (!to_find[0])
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			y = 0;
			while (to_find[y] && str[i + y] == to_find[y] && (i + y) < len)
				y++;
			if (!to_find[y])
				return ((char *)(str + i));
		}
		i++;
	}
	return (NULL);
}
