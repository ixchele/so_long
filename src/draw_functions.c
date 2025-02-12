/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:26:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:04:35 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}


void	draw_enemy(t_map *map)
{
	int i;

	i = 0;
	while (i < map->skel)
	{
		if (map->enemy[i].is_there == true)
		{
			merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, 0xFF000000);
			merge_enemy_images(map, &map->tex.enemy_idle, SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, i);
		}
		i++;
	}
}

void	draw_coins(t_map *map)
{
	int y;

	y = 0;
	while (y < map->items)
	{
		if (map->coin[y].is_there == true)
		{
			merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y, 0xFF000000);
			merge_images(&map->tex.composite, &map->tex.coin[map->i_coin], SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y, 0xFF000000);
		}
		else if (map->coin[y].is_there == false && map->coin[y].taken == false)
		{
			merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y, 0xFF000000);
			merge_coin_images(&map->tex.composite, &map->tex.coin_, SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y, &map->coin[y].i_coin);
			if (map->coin[y].i_coin == 6)
				map->coin[y].taken = true;
		}
		y++;
	}
}

void	draw_static_elements(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == '1')
				merge_images(&map->tex.composite, &map->tex.wall, SCALE * x, SCALE * y, 0xFF000000);
			else if (map->map[y][x] == 'E')
				merge_images(&map->tex.composite, &map->tex.exit, SCALE * x, SCALE * y, 0xFF000000);
			else if (map->map[y][x] == 'P')	// NOTE: Remove after FIX
				merge_images(&map->tex.composite, &map->tex.player_idle, SCALE * x, SCALE * y, 0xFF000000);
			else if (map->map[y][x] == 'C')
				merge_images(&map->tex.composite, &map->tex.coin[0], SCALE * x, SCALE * y, 0xFF000000);
			else if (map->map[y][x] == 'X')
				merge_images(&map->tex.composite, &map->tex.enemy_idle, SCALE * x, SCALE * y, 0xFF000000);
			x++;		 
		}
		y++;
	}
}
