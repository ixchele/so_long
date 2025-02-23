/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:26:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/12 22:49:39 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	draw_enemy(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->skel)
	{
		if (map->enemy[i].is_there == true)
		{
			merge_images(&map->tex.composite, &map->tex.grass, (t_cord){
				SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y,
				0, 0});
			merge_enemy_images(map, &map->tex.e_i, (t_cord){
				SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y,
				0, 0}, i);
		}
		i++;
	}
}

static void	choose_coin(t_map *map, int y)
{
	if (map->coin[y].is_there == true)
	{
		merge_images(&map->tex.composite, &map->tex.grass, (t_cord){
			SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y,
			0, 0});
		merge_images(&map->tex.composite, &map->tex.coin[map->i_coin],
			(t_cord){SCALE * map->coin[y].cord.x,
			SCALE * map->coin[y].cord.y, 0, 0});
	}
	else if (map->coin[y].is_there == false && map->coin[y].taken == false)
	{
		merge_images(&map->tex.composite, &map->tex.grass, (t_cord){
			SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y,
			0, 0});
		merge_coin_images(&map->tex.composite, &map->tex.coin_, (t_cord){
			SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y,
			0, 0}, &map->coin[y].i_coin);
		if (map->coin[y].i_coin == 6)
			map->coin[y].taken = true;
	}
}

static void	choose_dr(t_map *map, int x, int y)
{
	if (map->map[y][x] == '1')
		merge_images(&map->tex.composite, &map->tex.wall, (t_cord){SCALE * x,
			SCALE * y, 0, 0});
	else if (map->map[y][x] == 'E')
		merge_images(&map->tex.composite, &map->tex.exit, (t_cord){SCALE * x,
			SCALE * y, 0, 0});
	else if (map->map[y][x] == 'P')
		merge_images(&map->tex.composite, &map->tex.p_i, (t_cord){SCALE
			* x, SCALE * y, 0, 0});
	else if (map->map[y][x] == 'C')
		merge_images(&map->tex.composite, &map->tex.coin[0], (t_cord){SCALE * x,
			SCALE * y, 0, 0});
	else if (map->map[y][x] == 'X')
		merge_images(&map->tex.composite, &map->tex.e_i, (t_cord){SCALE
			* x, SCALE * y, 0, 0});
}

void	draw_coins(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->items)
	{
		choose_coin(map, y);
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
			choose_dr(map, x, y);
			x++;
		}
		y++;
	}
}
