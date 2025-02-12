/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:58:46 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:04:28 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	compare_coords(t_cord *cord1, t_cord *cord2)
{
	if (cord1->x == cord2->x && cord1->y == cord2->y)
		return (true);
	return (false);
}

void	check_enemy(t_map *map)
{	
	int i = 0;
	while (i < map->skel)
	{
		if (compare_coords(&map->enemy[i].cord, &map->player.cord))
			exit(0);
		i++;
	}
}

void	check_exit(t_map *map, int x, int y)
{	
	if (map->player.move == 'D' && map->map[y + 1][x] == 'E' && !map->nmb_coins)
		exit(0);
	else if (map->player.move == 'U' && map->map[y - 1][x] == 'E' && !map->nmb_coins)
		exit(0);
	else if (map->player.move == 'L' && map->map[y][x - 1] == 'E' && !map->nmb_coins)
		exit(0);
	else if (map->player.move == 'R' && map->map[y][x + 1] == 'E' && !map->nmb_coins)
		exit(0);
}

void	check_coin(t_map *map, int x, int y)
{
	int i = 0;
	while (i < map->items)
	{
		if (map->player.move == 'D' && map->coin[i].cord.x == x && map->coin[i].cord.y == y + 1 && map->coin[i].is_there)
		{
			map->coin[i].is_there = false;
			map->nmb_coins--;
			break;
		}
		else if (map->player.move == 'U' && map->coin[i].cord.x == x && map->coin[i].cord.y == y - 1 && map->coin[i].is_there)
		{
			map->coin[i].is_there = false;
			map->nmb_coins--;
			break;
		}
		else if (map->player.move == 'L' && map->coin[i].cord.x == x - 1 && map->coin[i].cord.y == y && map->coin[i].is_there)
		{
			map->coin[i].is_there = false;
			map->nmb_coins--;
			break;
		}
		else if (map->player.move == 'R' && map->coin[i].cord.x == x + 1 && map->coin[i].cord.y == y && map->coin[i].is_there)
		{
			map->coin[i].is_there = false;
			map->nmb_coins--;
			break;
		}
		i++;
	}
}
