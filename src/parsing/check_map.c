/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:57:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/14 20:49:06 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static char	*map_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	ret = NULL;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (printf("Malloc Failed\n"), NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	free(s1);
	return (ret);
}

static void	check_map(t_map *map, char *str)
{
	int (i) = 0;
	map->cord.height = 1;
	map->cord.witdh = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (!str[i + 1])	
			{
				free(str);
				ft_error(map, "New Line at End of Map");
			}
			if (str[i + 1] == '\n')
			{
				free(str);
				ft_error(map, "Consecutive New Lines in Map");
			}
			map->cord.height++;
			if (!map->cord.witdh)
				map->cord.witdh = i;
		}
		i++;
	}
	if (map->cord.height > 29 || map->cord.witdh > 55)
	{
		free(str);
		ft_error(map, "Map is Too Big! ( Max 29x55 )");
	}
}

static char	*read_loop(t_map *map, int fd)
{
	char	*tmp;
	char	*ret;

	ret = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (!tmp)
			break ;
		ret = map_join(ret, tmp);
		if (!ret)
			{
				close(fd);
				ft_error(map, "StrJoin Failed!");
			}
		free(tmp);
	}
	return (ret);
}

void	read_(const char *file, t_map *map)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(map, "Open Failed!");
	line = read_loop(map, fd);
	close(fd);
	if (!line)
		ft_error(map, "Map Read Failed!");;
	check_map(map, line);
	map->map = ft_split(line, '\n');
	map->flood_map = ft_split(line, '\n');
	free(line);
	if (!map->map || !map->flood_map)
		ft_error(map, "Split Failed!");;
}
