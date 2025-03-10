/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_functions_player.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 22:07:44 by zbengued          #+#    #+#             */
/*   Updated: 2025/03/04 03:06:54 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	animate_move(t_map *map, t_image *tex, int coef_x, int coef_y)
{
	clear_frame(&map->tex.frame_player, map);
	map->frame_nmb_player %= 6;
	choose_frame(&map->tex.frame_player, tex, map->frame_nmb_player);
	merge_player_images(map, &map->tex.composite, &map->tex.frame_player,
		(t_cord){map->player.cord.x * SCALE + coef_x * map->step_player,
		map->player.cord.y * SCALE + coef_y * map->step_player, 0, 0});
	map->step_player += 10;
	map->frame_nmb_player++;
}

static void	one_step_player(t_map *map, int x, int y)
{
	moove_player(map);
	if (x != map->player.cord.x || y != map->player.cord.y)
		remove_coin(map, x, y);
	map->step_player = 0;
	map->player.move = 'I';
	map->anim_player = false;
}

static void	choose_animation(t_map *map)
{
	static int	i_count;

	if (i_count % 6 == 0)
		i_count = 0;
	merge_images(&map->tex.composite, &map->tex.grass, (t_cord){SCALE
		* map->player.cord.x, SCALE * map->player.cord.y, 0, 0});
	if (map->player.move == 'R')
		animate_move(map, &map->tex.p_r, 1, 0);
	else if (map->player.move == 'L')
		animate_move(map, &map->tex.p_l, -1, 0);
	else if (map->player.move == 'U')
		animate_move(map, &map->tex.p_u, 0, -1);
	else if (map->player.move == 'D')
		animate_move(map, &map->tex.p_d, 0, 1);
	else if (map->player.move == 'I')
	{
		clear_frame(&map->tex.frame_player, map);
		choose_frame(&map->tex.frame_player, &map->tex.p_i,
			i_count);
		merge_player_images(map, &map->tex.composite, &map->tex.frame_player,
			(t_cord){SCALE * map->player.cord.x, SCALE * map->player.cord.y,
			0, 0});
	}
	i_count++;
}

void	animate_player(t_map *map)
{
	int	y;
	int	x;

	y = map->player.cord.y;
	x = map->player.cord.x;
	check_exit(map, x, y);
	check_coin(map, x, y);
	if (map->count_player % 50 == 0)
	{
		map->i_player++;
		if (map->i_player == 1)
		{
			map->i_player = 0;
			map->count_player = 0;
		}
	}
	if (map->step_player >= SCALE)
		one_step_player(map, x, y);
	map->dellay_player += 1;
	if ((int)map->dellay_player % map->rate == 0)
		choose_animation(map);
	map->count_player++;
}
