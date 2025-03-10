/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_playable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 19:34:17 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/14 20:48:22 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include <stddef.h>

static void	flood_fill(char **flood_map, size_t x, size_t y)
{
	if (flood_map[y][x] != 'C' && flood_map[y][x] != '0'
		&& flood_map[y][x] != 'P')
		return ;
	flood_map[y][x] = '#';
	flood_fill(flood_map, x + 1, y);
	flood_fill(flood_map, x - 1, y);
	flood_fill(flood_map, x, y + 1);
	flood_fill(flood_map, x, y - 1);
}

static bool	exit_reachable(char **map, int i, int j)
{
	if (map[i][j + 1] != '#' && map[i][j - 1] != '#' && map[i + 1][j] != '#'
		&& map[i - 1][j] != '#')
		return (false);
	return (true);
}

static bool	check_flood_fill(t_map *map, char **flood_map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->cord.height)
	{
		j = 0;
		while (j < map->cord.witdh)
		{
			if (flood_map[i][j] == 'C' || (flood_map[i][j] == 'E'
					&& exit_reachable(flood_map, i, j) == false))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	is_playable(t_map *map)
{
	bool	ret;

	flood_fill(map->flood_map, map->player.cord.x, map->player.cord.y);
	ret = check_flood_fill(map, map->flood_map);
	return (ret);
}

void	is_valid(t_map *map)
{
	if (!check_walls(map))
		ft_error(map, "Map Not Surrounded by Walls!");
	if (!check_elements(map))
		ft_error(map, "Invalid Number of Element(s)!");
	if (!is_playable(map))
		ft_error(map, "Invalid Map Pathing!");
}
