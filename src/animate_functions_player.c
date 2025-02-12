/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_functions_player.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 22:07:44 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:04:12 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	animate_move(t_map *map, t_image *tex, int coef_x, int coef_y)
{
	clear_frame(&map->tex.frame_player, map);
	map->frame_nmb_player %= 6;
	choose_frame(&map->tex.frame_player, tex, map->frame_nmb_player);
	merge_player_images(map, &map->tex.composite, &map->tex.frame_player, map->player.cord.x * SCALE + coef_x * (map->step_player) , map->player.cord.y * SCALE + coef_y * (map->step_player));
	map->step_player += 10;
	map->frame_nmb_player++;
}

void	animate_open_exit(t_map *map)
{
	static int	count = 0;
	static int flag = 0;
	if (!flag && count % map->rate == 0)
	{
		merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->exit.cord.x, SCALE * map->exit.cord.y, 0xFF000000);
		merge_exit_images(map, &map->tex.composite, &map->tex.exit, SCALE * map->exit.cord.x, SCALE * map->exit.cord.y);
		map->i_exit++;
		if (map->i_exit == 6)
		{
			flag = 1;
			return ;
		}
	}
	count++;
}

void	animate_player(t_map *map)
{
	int y = map->player.cord.y;
	int	x = map->player.cord.x;
	
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
	{	
		moove_player(map);
		if (x != map->player.cord.x || y != map->player.cord.y)
			remove_coin(map, x, y);
		map->step_player = 0;
		map->player.move = 'I';
		map->anim_player = false;
	}
	map->dellay_player += 1;
	if ((int)map->dellay_player % map->rate == 0)
	{
		merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->player.cord.x, SCALE * map->player.cord.y, 0xFF000000);
		if (map->player.move == 'R')
			animate_move(map, &map->tex.player_right, 1, 0);
		else if (map->player.move == 'L')
			animate_move(map, &map->tex.player_left, -1, 0);
		else if (map->player.move == 'U')
			animate_move(map, &map->tex.player_up, 0, -1);
		else if (map->player.move == 'D')
			animate_move(map, &map->tex.player_down, 0, 1);
		else if (map->player.move == 'I')
		{
			clear_frame(&map->tex.frame_player, map);
			choose_frame(&map->tex.frame_player, &map->tex.player_idle, map->i_player);
			merge_player_images(map, &map->tex.composite, &map->tex.frame_player, SCALE * map->player.cord.x, SCALE * map->player.cord.y);
		}
	}
	map->count_player++;
}
