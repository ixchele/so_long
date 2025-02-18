/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:49:54 by zbengued          #+#    #+#             */
/*   Updated: 2024/12/07 17:14:31 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free(&rest));
	rest = reader(fd, &rest);
	if (!rest)
		return (ft_free(&rest));
	line = extract_line(rest);
	if (!line)
		return (ft_free(&rest));
	rest = jump_line(&rest);
	return (line);
}

char	*ft_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*reader(int fd, char **rest)
{
	char	*buffer;
	ssize_t	b;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (ft_free(rest));
	b = 6;
	while (!ft_gnl_strchr(*rest, '\n') && b > 0)
	{
		b = read(fd, buffer, BUFFER_SIZE);
		if (b == -1)
		{
			free(buffer);
			return (ft_free(rest));
		}
		buffer[b] = '\0';
		*rest = ft_gnl_strjoin(*rest, buffer);
		if (!*rest)
			return (free(buffer), ft_free(rest));
	}
	free(buffer);
	return (*rest);
}

char	*jump_line(char **rest)
{
	char	*nl;

	nl = ft_gnl_strchr(*rest, '\n');
	if (nl)
		return (ft_gnl_memmove(*rest, nl + 1,
				ft_gnl_strlen(*rest) - (nl - *rest)));
	return (ft_free(rest));
}

char	*extract_line(char *rest)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!rest[i])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	str = malloc(i + 1 + (rest[i] == '\n'));
	if (!str)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
	{
		str[i] = rest[i];
		i++;
	}
	if (rest[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}
