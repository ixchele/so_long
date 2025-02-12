/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_functions_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 22:13:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:04:17 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_coin(t_map *map)
{
	static int	count = 0;

	if (count % (int)(map->rate * 0.78f) == 0)
	{
		draw_coins(map);
		map->i_coin++;
		if (map->i_coin == 6)
		{
			map->i_coin = 0;
			count = 0;
		}
	}
	count++;
}

void	animate_move_enemy(t_map *map, t_image *tex, int coef_x, int coef_y, int i)
{
	clear_frame(&map->tex.frame_enemy[i], map);
	map->enemy[i].frame_nmb_enemy %= 6;
	choose_frame(&map->tex.frame_enemy[i], tex, map->enemy[i].frame_nmb_enemy);
	merge_enemy_images(map, &map->tex.frame_enemy[i], map->enemy[i].cord.x * SCALE + coef_x * (map->enemy[i].step_enemy) , map->enemy[i].cord.y * SCALE + coef_y * (map->enemy[i].step_enemy), i);
	map->enemy[i].step_enemy += 7;
	map->enemy[i].frame_nmb_enemy++;
}

void	animate_enemy(t_map *map, int i)
{
	int y = map->enemy[i].cord.y;
	int	x = map->enemy[i].cord.x;
	
	if (map->enemy[i].count_enemy % 50 == 0)
	{
		map->enemy[i].i_enemy++;
		if (map->enemy[i].i_enemy == 1)
		{
			map->enemy[i].i_enemy = 0;
			map->enemy[i].count_enemy = 0;
		}
	}
	if (map->enemy[i].step_enemy >= SCALE)
	{	
		move_enemy(&map->enemy[i]);
		if (x != map->enemy[i].cord.x || y != map->enemy[i].cord.y)
			remove_grass(map, x, y, i);
		map->enemy[i].step_enemy = 0;
		//map->enemy[i].move = 'I';
		map->enemy[i].anim_enemy = false;
	}
	map->enemy[i].dellay_enemy += 1;
	if ((int)map->enemy[i].dellay_enemy % map->rate == 0)
	{
		merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, 0xFF000000);
		if (map->enemy[i].move == 'R')
			animate_move_enemy(map, &map->tex.enemy_right, 1, 0, i);
		else if (map->enemy[i].move == 'L')
			animate_move_enemy(map, &map->tex.enemy_left, -1, 0, i);
		else if (map->enemy[i].move == 'U')
			animate_move_enemy(map, &map->tex.enemy_up, 0, -1, i);
		else if (map->enemy[i].move == 'D')
			animate_move_enemy(map, &map->tex.enemy_down, 0, 1, i);
		else if (map->enemy[i].move == 'I')
		{
			clear_frame(&map->tex.frame_enemy[i], map);
			choose_frame(&map->tex.frame_enemy[i], &map->tex.enemy_idle, map->enemy[i].i_enemy);
			merge_enemy_images(map, &map->tex.frame_enemy[i], SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, i);
		}
	}
	map->enemy[i].count_enemy++;
}

void	animate_idle_enemy(t_map *map, int i)
{
	static int	count = 0;

	if (count % map->rate == 0)
	{
		draw_enemy(map);
		map->enemy[i].i_enemy++;
		if (map->enemy[i].i_enemy == 6)
		{
			map->enemy[i].i_enemy = 0;
			count = 0;
		}
	}
	count++;
}

