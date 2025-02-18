/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:56:17 by zbengued          #+#    #+#             */
/*   Updated: 2024/12/07 17:16:32 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>

char	*ft_free(char **ptr);
char	*ft_gnl_strdup(char *s);
size_t	ft_gnl_strlen(char *s);
char	*ft_gnl_strchr(char *s, int c);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*jump_line(char **rest);
char	*reader(int fd, char **rest);
char	*extract_line(char *rest);
void	*ft_gnl_memmove(void *dest, void *src, size_t n);

#endif
