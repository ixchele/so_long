/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:45:26 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/11 18:02:56 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	ptr_size;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s2 && s1)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	ptr_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = malloc(sizeof(char) * (ptr_size));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, ptr_size);
	ft_strlcat(ptr, s2, ptr_size);
	return (ptr);
}
