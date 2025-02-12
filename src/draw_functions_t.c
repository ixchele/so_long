/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions_t.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:53:27 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:04:40 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	remove_grass(t_map *map, int x, int y, int i)
{
	check_enemy(map);
	map->map[y][x] = '0';
	map->map[map->enemy[i].cord.y][map->enemy[i].cord.x] = 'X';
	merge_images(&map->tex.composite, &map->tex.grass, SCALE * x, SCALE * y, 0xFF000000);
}

void	remove_coin(t_map *map, int x, int y)
{
	static int i = 1;
	check_enemy(map);
	map->map[y][x] = '0';
	map->map[map->player.cord.y][map->player.cord.x] = 'P';
	merge_images(&map->tex.composite, &map->tex.grass, SCALE * x, SCALE * y, 0xFF000000);
	printf("Number of moves => %d\n", i++);
	printf("Number of coins => %d\n", map->nmb_coins);
}
