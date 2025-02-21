/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:21:55 by zbengued          #+#    #+#             */
/*   Updated: 2024/11/14 11:58:01 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

void	*freer(char **tab, size_t i)
{
	while (i > 0)
		free(tab[--i]);
	free(tab);
	return (NULL);
}

static char	**splinter(char **tab, char const *s, size_t i, char c)
{
	size_t	start;
	size_t	word_len;
	size_t	j;

	j = 0;
	while (j < count_word(s, c))
	{
		word_len = 0;
		while (s[i] == c && s[i])
			i++;
		start = i;
		while (s[i] != c && s[i])
		{
			i++;
			word_len++;
		}
		tab[j] = ft_substr(s, start, word_len);
		if (!tab[j])
			return (freer(tab, j));
		j++;
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	tab = ft_calloc(count_word(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	tab = splinter(tab, s, i, c);
	return (tab);
}
