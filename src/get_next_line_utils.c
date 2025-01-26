/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:57:40 by zbengued          #+#    #+#             */
/*   Updated: 2024/12/06 16:36:37 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"

size_t	ft_gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_gnl_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[ft_gnl_strlen(s)]);
	while (s[i] != '\0')
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_gnl_strjoin(char *rest, char *buff)
{
	size_t	l;
	size_t	i;
	size_t	j;
	char	*str;

	if (!rest && buff)
		return (ft_gnl_strdup(buff));
	if (!rest || !buff)
		return (free(rest), NULL);
	l = ft_gnl_strlen(rest) + ft_gnl_strlen(buff);
	str = malloc(l + 1);
	if (str == NULL)
		return (free(rest), NULL);
	i = -1;
	j = 0;
	while (rest[++i] != '\0')
		str[i] = rest[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[l] = '\0';
	return (free(rest), str);
}

char	*ft_gnl_strdup(char *s)
{
	size_t	i;
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = malloc(ft_gnl_strlen(s) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	*ft_gnl_memmove(void *dest, void *src, size_t n)
{
	size_t			i;
	size_t			j;
	size_t			ind_x;
	char			*ptrs;
	char			*ptrd;

	if (!dest && !src)
		return (NULL);
	i = 0;
	j = 1;
	ind_x = 0;
	ptrs = (char *)src;
	ptrd = (char *)dest;
	if (dest > src)
	{
		j = -1;
		ind_x = n - 1;
	}
	while (i < n)
	{
		ptrd[ind_x] = ptrs[ind_x];
		ind_x += j;
		i++;
	}
	return (dest);
}
