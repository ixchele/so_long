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
#include "../ft_printf/libft/libft.h"
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
	size_t		height;
	size_t		witdh;
	bool	is_there_exit;
	bool	is_there_player;
	int		items;
	size_t	player_x;
	size_t	player_y;
}	t_map;

void	get_player_inf(t_map *map, int i, int j)
{
	map->is_there_player = true;
	map->player_x = i;
	map->player_y = j;
}

bool	check_elements(t_map *map)
{
	int	(i), (j);
	i = 1;
	map->items = false;
	map->is_there_exit = false;
	map->is_there_player = false;
	while (i < map->height)
	{
		j = 0;
		while (j < map->witdh)
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
		if (i == map->height - 1 && ft_strlen(map->map[i]) != map->witdh)
			return (false);
		if (i != map->height - 1 && ft_strlen(map->map[i]) - 1 != map->witdh)
			return (false);
		i++;
	}
	return (true);
}

char **read_map(const char *file, t_map *map, char **flood_map)
{
	char	*line;

	int		(i), (fd), (capacity);
	i = 0;
	capacity = 10;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map->map = malloc(sizeof(char *) * capacity);
	if (!map->map)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (i >= capacity)
		{
			capacity *= 2;
			map->map = realloc(map->map, sizeof(char *) * capacity);
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

void	flood_fill(char **flood_map, size_t x, size_t y)
{
	if (!flood_map[x] || !flood_map[x][y])
		return ;
	if (flood_map[x][y] != 'C' && flood_map[x][y] != '0' && flood_map[x][y] != 'P')
		return ;
	flood_map[x][y] = '#';
	flood_fill(flood_map, x + 1, y);
	flood_fill(flood_map, x - 1, y);
	flood_fill(flood_map, x, y + 1);
	flood_fill(flood_map, x, y - 1);
}

bool	exit_reachable(char **map, int i, int j)
{
	for (int i = 0; map[i]; i++) {
		for (int j = 0; map[j]; j++) {
			printf("%c", map[i][j]);
		}
		printf("\n");
	}

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
	flood_map = malloc(sizeof(char *) * map->height);
	while (i < map->height)
	{
		j = 0;
		flood_map[i] = malloc(sizeof(char) * map->witdh);
		while (j < map->witdh)
		{
			flood_map[i][j] = map->map[i][j];
			j++;
		}
		i++;
	}
	flood_fill(flood_map, map->player_x, map->player_y);
	printf("\n\n");
	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < map->witdh; j++) {
			printf("%c", flood_map[i][j]);
		}
		printf("\n");
	}
	while (i < map->height)
	{
		j = 0;
		while (j < map->witdh)
		{
			if (flood_map[i][j] == 'C' || !exit_reachable(flood_map, i, j))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_valid(t_map *map)
{
	return (check_walls(map) && check_elements(map) && is_playebal(map));
}

int main(int ac , char **av)
{
	t_map map1;
	char	**flood_map;

	if (ac < 2)
		return (0);
	map1.map = NULL;
	char **map1_ = read_map(av[1], &map1, flood_map);
	if (!map1_)
		return (printf("erroor"),0);
	for (int i = 0; i < map1.height; i++)
	{
		for (int j = 0; map1_[i][j]; j++)
			printf("%c", map1_[i][j]);
	}
	//printf("\n%d = h, %d = w\n-is the wall check good = %d\n-is the map rectangular = %d\nis there all chars = %d\n",
	//	map1.height, map1.witdh, check_walls(&map1), check_rectangle(&map1), check_elements(&map1));
	printf("is it valid = %d", is_valid(&map1));
}
