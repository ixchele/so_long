/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 09:42:23 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/14 11:56:34 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "get_next_line/get_next_line.h"

typedef struct	s_map
{
	char	**map;
	int		height;
	int		witdh;
	bool	exit_pos;
	bool	player_pos;
	int		items;
}	t_map;

bool	check_map_elements(t_map *map)
{
	int (i), (j);
	i = 1;
	map->items = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->witdh)
		{
			if (map->map[i][j] == 'E' && map->exit_pos == true)
				return (false);
			if (map->map[i][j] == 'P' && map->player_pos == true)
				return (false);
			else if (map->map[i][j] == 'E' && map->exit_pos == false)
				map->exit_pos = true;
			else if (map->map[i][j] == 'P' && map->player_pos == false)
				map->player_pos = true;
			else if (map->map[i][j] == 'C')
				map->items++;
			else if (map->map[i][j] != '1' && map->map[i][j] != '0')
				return (false);
			j++;
		}
		i++;
	}
	return (map->items == false || map->player_pos == false || map->exit_pos == false);
}

bool check_walls(t_map *map)
{
	int (i) = 0;
	while (i < map->witdh)
	{
		if (map->map[0][i] != '1' || map->map[map->height - 1][i] != '1')
			return (false);
		i++;
	}
	i = 1;
	while (i < map->height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->witdh - 1] != '1')
			return (false);
		if (ft_strlen(map->map[i]) - 1 != map->witdh)// check if the map is rectangular 
			return (false);
		i++;
	}
	return (true);
}

char **read_map(const char *file, t_map *map)
{
	char	*line;

	int		(i), (fd), (capacity);
	i = 0;
	capacity = 10;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	map->map = malloc(sizeof(char *) * capacity);
	if (!map->map)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (i >= capacity)
		{
			capacity *= 2;
			map->map = realloc(map, sizeof(char *) * capacity);
			if (!map->map)
				return (free(map->map), close(fd), NULL);
		}
		map->map[i++] = line;
	}
	map->map[i] = NULL;
	map->height = i;
	map->witdh = ft_strlen(map->map[0]) - 1;
	map->map= realloc(map->map, sizeof(char *) * (i + 1));
	if (!map->map)
		return (free(map->map),close(fd),NULL);
	close(fd);
	return (map->map);
}

bool	is_valid(t_map *map)
{
	return (check_walls(map) && check_map_elements(map));
}

int main(int ac , char **av)
{
	t_map map1;

	char **map1_ = read_map(av[1], &map1);
	if (!map1_)
		return (printf("error"),0);
	for (int i = 0; i < map1.height; i++)
	{
		for (int j = 0; map1_[i][j]; j++) 
			printf("%c", map1_[i][j]);
	}
	printf("is it valid = %d", is_valid(&map1));
}
