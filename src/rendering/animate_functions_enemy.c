/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_functions_enemy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 22:13:02 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/12 22:28:48 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	animate_move_enemy(t_map *map, t_image *tex, t_cord coef, int i)
{
	clear_frame(&map->tex.frame_enemy[i], map);
	map->enemy[i].frame_nmb_enemy %= 6;
	choose_frame(&map->tex.frame_enemy[i], tex, map->enemy[i].frame_nmb_enemy);
	merge_enemy_images(map, &map->tex.frame_enemy[i],
		(t_cord){map->enemy[i].cord.x * SCALE + coef.x
		* (map->enemy[i].step_enemy), map->enemy[i].cord.y * SCALE + coef.y
		* (map->enemy[i].step_enemy), 0, 0}, i);
	map->enemy[i].step_enemy += 5;
	map->enemy[i].frame_nmb_enemy++;
}

static void	one_step_enemy(t_map *map, int i, int x, int y)
{
	move_enemy(&map->enemy[i]);
	if (x != map->enemy[i].cord.x || y != map->enemy[i].cord.y)
		remove_grass(map, x, y, i);
	map->enemy[i].step_enemy = 0;
	map->enemy[i].anim_enemy = false;
}

static void	choose_animation(t_map *map, int i)
{
	merge_images(&map->tex.composite, &map->tex.grass, (t_cord){SCALE
		* map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, 0, 0});
	if (map->enemy[i].move == 'R')
		animate_move_enemy(map, &map->tex.e_r, (t_cord){1, 0, 0, 0}, i);
	else if (map->enemy[i].move == 'L')
		animate_move_enemy(map, &map->tex.e_l, (t_cord){-1, 0, 0, 0}, i);
	else if (map->enemy[i].move == 'U')
		animate_move_enemy(map, &map->tex.e_u, (t_cord){0, -1, 0, 0}, i);
	else if (map->enemy[i].move == 'D')
		animate_move_enemy(map, &map->tex.e_d, (t_cord){0, 1, 0, 0}, i);
	else if (map->enemy[i].move == 'I')
	{
		clear_frame(&map->tex.frame_enemy[i], map);
		choose_frame(&map->tex.frame_enemy[i],
			&map->tex.e_i,
			map->enemy[i].i_enemy);
		merge_enemy_images(map, &map->tex.frame_enemy[i], (t_cord){SCALE
			* map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, 0, 0}, i);
	}
}

void	animate_enemy(t_map *map, int i)
{
	int	y;
	int	x;

	x = map->enemy[i].cord.x;
	y = map->enemy[i].cord.y;
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
		one_step_enemy(map, i, x, y);
	map->enemy[i].dellay_enemy += 1;
	if ((int)map->enemy[i].dellay_enemy % map->rate == 0)
		choose_animation(map, i);
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
