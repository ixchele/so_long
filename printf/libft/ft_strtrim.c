/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 08:58:46 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/11 09:38:27 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	jump_start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j] && s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				i++;
				break ;
			}
			else
				j++;
		}
	}
	return (i);
}

static int	jump_end(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] && s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				i--;
				break ;
			}
			else
				j++;
		}
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		l;
	int		i;
	int		j;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	i = jump_start(s1, set);
	j = jump_end(s1, set);
	l = 0;
	if (i > j)
		return (ft_strdup(""));
	ptr = malloc(sizeof(char) * (j - i + 2));
	if (!ptr)
		return (NULL);
	while (i <= j)
		ptr[l++] = s1[i++];
	ptr[l] = '\0';
	return (ptr);
}
