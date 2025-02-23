/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:46:36 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/15 19:05:28 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *des, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i])
		i++;
	while (j < size - 1 && src[j])
	{
		des[j] = src[j];
		j++;
	}
	des[j] = '\0';
	return (i);
}
