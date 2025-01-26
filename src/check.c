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
	map->player_x = j;
	map->player_y = i;
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
	printf("Width = %zu, Height = %zu\n", map->witdh, map->height);
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
		if (i == map->height && ft_strlen(map->map[i]) != map->witdh)
			return (false);
		if (i != map->height && ft_strlen(map->map[i])  != map->witdh)
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
	map->height = 1;
	map->witdh = 0;
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
			map->height++;
			if (!map->witdh)
				map->witdh = i;
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
			return (printf("tmp Failed\n"), NULL);
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
		return (printf("split Failed\n"), NULL);
	close(fd);
	return (map_arr);
}

// char **read_map(const char *file, t_map *map)
// {
// 	char	*line;
// 	int line_len = -1;
// 	int		(i), (fd), (capacity);
// 	i = 0;
// 	capacity = 10;
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	map->map = malloc(sizeof(char *) * capacity);
// 	if (!map->map)
// 		return (NULL);
// 	while ((line = get_next_line(fd)))
// 	{
// 		if (i >= capacity)
// 		{
// 			capacity *= 2;
// 			map->map = realloc(map->map, sizeof(char *) * capacity);
// 			if (!map->map)
// 				return (free(map->map), close(fd), NULL);
// 		}
// 		if (line_len == -1)
// 			line_len = strlen(line);
// 		if (line[line_len - 1] != 0)
// 			line[line_len - 1] = 0;
// 		map->map[i++] = line;
// 	}
// 	map->map[i] = NULL;
// 	map->height = i;
// 	map->witdh = ft_strlen(map->map[0]);
// 	map->map= realloc(map->map, sizeof(char *) * (i + 1));
// 	if (!map->map)
// 		return (free(map->map),close(fd),NULL);
// 	close(fd);
// 	return (map->map);
// }

// char **read_map(const char *file, t_map *map)
// {
// 	char	*line;
//
// 	int		(i), (fd), (capacity);
// 	i = 0;
// 	capacity = 10;
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	map->map = malloc(sizeof(char *) * capacity);
// 	if (!map->map)
// 		return (NULL);
// 	while ((line = get_next_line(fd)))
// 	{
// 		if (i >= capacity)
// 		{
// 			capacity *= 2;
// 			map->map = realloc(map, sizeof(char *) * capacity);
// 			if (!map->map)
// 				return (free(map->map), close(fd), NULL);
// 		}
// 		map->map[i++] = line;
// 	}
// 	map->map[i] = NULL;
// 	map->height = i;
// 	map->witdh = ft_strlen(map->map[0]) - 1;
// 	map->map= realloc(map->map, sizeof(char *) * (i + 1));
// 	if (!map->map)
// 		return (free(map->map),close(fd),NULL);
// 	close(fd);
// 	return (map->map);
// }

void	flood_fill(char **flood_map, size_t x, size_t y)
{
	// if (!flood_map[x] || !flood_map[x][y])
	// 	return ;
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
	printf("\n--avant--\n");
	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < map->witdh; j++) {
			printf("%c", flood_map[i][j]);
		}
		printf("\n");
	}
	flood_fill(flood_map, map->player_x , map->player_y);
	printf("\n--apres--\n");
	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < map->witdh; j++) {
			printf("%c", flood_map[i][j]);
		}
		printf("\n");
	}
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->witdh)
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
	map1.map = NULL;
	map1.map = read_(av[1], &map1);
	if (!map1.map)
		return (printf("error"),1);
	int map_valid = is_valid(&map1);
	printf("x = %d, y = %d\n",map1.player_x, map1.player_y);
	printf("is it valid = %d\n",map_valid);
	if (map_valid == false)
		return (perror("eroor"),1);
	rendring(&map1);
}
