/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:42:23 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/21 11:21:48 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line/get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	get_player_inf(t_map *map, int i, int j)
{
	map->is_there_player = true;
	map->player.cord.x = j;
	map->player.cord.y = i;
}

bool	check_elements(t_map *map)
{
	int	(i), (j);
	i = 1;
	map->items = false;
	map->is_there_exit = false;
	map->is_there_player = false;
	while (i < map->cord.height)
	{
		j = 0;
		while (j < map->cord.witdh)
		{
			if (map->map[i][j] == 'E' && map->is_there_exit == true)
				return (false);
			if (map->map[i][j] == 'P' && map->is_there_player == true)
				return (false);
			else if (map->map[i][j] == 'E' && map->is_there_exit == false)
				map->is_there_exit = true;
			else if (map->map[i][j] == 'P' && map->is_there_player == false)
				get_player_inf(map, i, j);
			else if (map->map[i][j] == 'C')
				map->items++;
			else if (map->map[i][j] != '1' && map->map[i][j] != '0')
				return (false);
			j++;
		}
		i++;
	}
	return (map->items && map->is_there_player && map->is_there_exit);
}

bool check_walls(t_map *map)
{
	int (i) = 0;
	while (i < map->cord.witdh)
	{
		if (map->map[0][i] != '1' || map->map[map->cord.height - 1][i] != '1')
			return (false);
		i++;
	}
	i = 1;
	while (i < map->cord.height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->cord.witdh - 1] != '1')
			return (false);
		if (i == map->cord.height && ft_strlen(map->map[i]) != map->cord.witdh)
			return (false);
		if (i != map->cord.height && ft_strlen(map->map[i])  != map->cord.witdh)
			return (false);
		i++;
	}
	return (true);
}

char *map_join(char *s1, char *s2)
{
	int		i;
	int 	j;
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
	return (ret);
}

void	check_map(t_map *map, char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\n')
	{
		printf("Empty Line at Start of map\n");
		return ;
	}
	map->cord.height = 1;
	map->cord.witdh = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (!str[i + 1])
			{
				printf("New Line at End of Map\n");
				return ;
			}
			if (str[i + 1] == '\n')
			{
				printf("Consecutive New Lines in Map\n");
				return ;
			}
			map->cord.height++;
			if (!map->cord.witdh)
				map->cord.witdh = i;
		}
		i++;
	}
}

char **read_(const char *file, t_map *map)
{
	char **map_arr;
	char *line;
	char *tmp;
	int i, fd;

	map_arr = NULL;
	line = NULL;
	tmp = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("error, cant open file"), NULL);
	tmp = malloc(sizeof(char));
		if (!tmp)
			return (printf("malloc Failed\n"), NULL);
	tmp[0] = '\0';
	while ((tmp = get_next_line(fd)))
	{	
		if (!tmp)
			break;
		line = map_join(line, tmp);
		if (!line)
			return (printf("strjoin Failed\n"), NULL);
		free(tmp);
	}
	check_map(map, line);
	map_arr = ft_split(line, '\n');
	if (!map_arr)
		return (printf("split Failed\n"), free(line), NULL);
	close(fd);
	return (map_arr);
}

void	flood_fill(char **flood_map, size_t x, size_t y)
{
	if (flood_map[y][x] != 'C' && flood_map[y][x] != '0' && flood_map[y][x] != 'P')
		return ;
	flood_map[y][x] = '#';
	flood_fill(flood_map, x + 1, y);
	flood_fill(flood_map, x - 1, y);
	flood_fill(flood_map, x, y + 1);
	flood_fill(flood_map, x, y - 1);
}

bool	exit_reachable(char **map, int i, int j)
{
	if (map[i][j + 1] != '#' &&  map[i][j - 1] != '#' 
		&& map[i + 1][j] != '#' && map[i - 1][j] != '#')
		return (false);
	return (true);
}

bool	is_playebal(t_map *map)
{
	char	**flood_map;
	size_t	i;
	size_t	j;

	i = 0;
	flood_map = malloc(sizeof(char *) * map->cord.height);
	while (i < map->cord.height)
	{
		j = 0;
		flood_map[i] = malloc(sizeof(char) * map->cord.witdh);
		while (j < map->cord.witdh)
		{
			flood_map[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
	flood_fill(flood_map, map->player.cord.x , map->player.cord.y);
	i = 0;
	while (i < map->cord.height)
	{
		j = 0;
		while (j < map->cord.witdh)
		{
			if (flood_map[i][j] == 'C' || (flood_map[i][j] == 'E' && exit_reachable(flood_map, i, j) == false))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_valid(t_map *map)
{
	if (!check_walls(map))
	{
		printf("wall error");
		return false;
	}
	if (!check_elements(map))
	{
		printf("elements error");
		return false;
	}
	if (!is_playebal(map))
	{
		printf("flood error\n");
		return false;
	}
	return true;
}

int main(int ac , char **av)
{
	t_map map1;
	char	**flood_map;

	if (ac < 2)
		return (0);
	map1.index = 0;
	map1.map = NULL;
	map1.map = read_(av[1], &map1);
	if (!map1.map)
		return (printf("error"),1);
	int map_valid = is_valid(&map1);
	printf("is it valid = %d\n",map_valid);
	if (map_valid == false)
		return (perror("eroor"),1);
	rendring(&map1);
}
