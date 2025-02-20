/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:08:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/19 16:41:27 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include <stdio.h>

#define SCALE 70

void	enemy_loop(t_map *map)
{
	static int	id = 0;

	int (i) = 0;
	srand(time(NULL) ^ (id * 12345));
	id++;
	while (i < map->skel)
	{
		if (map->enemy[i].is_there == true)
		{
			if (get_distance(map->player.cord, map->enemy[i].cord) <= 5.0f
				&& !map->enemy[i].anim_enemy)
			{
				map->enemy[i].move = get_best_move(map, i, 0);
				animate_enemy(map, i++);
				continue ;
			}
			else if (!map->enemy[i].anim_enemy)
				map->enemy[i].move = get_random_move();
			validate_move(map, i);
			animate_enemy(map, i);
		}
		i++;
	}
}

int	game_loop(t_map *map)
{
	map->nmb_of_steps = ft_itoa(map->nmb_steps_player);
	animate_player(map);
	animate_coin(map);
	enemy_loop(map);
	if (map->nmb_coins == 0)
		animate_open_exit(map);
	mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
	mlx_set_font(map->mlx, map->win, "rk24");
	mlx_string_put(map->mlx, map->win, 3,
		map->cord.height * SCALE + 30, 0x000000, "NUMBER OF STEPS : ");
	//mlx_string_put(map->mlx, map->win,
	// 	10, map->cord.height * SCALE + 10, 0x000000, "simo howa li kayn");
	mlx_string_put(map->mlx, map->win, SCALE * 5,
		map->cord.height * SCALE + 30, 0x000000, map->nmb_of_steps);
	free(map->nmb_of_steps);
	map->nmb_of_steps = NULL;
	return (1);
}

int	mlx_exit(t_map *map)
{
	ft_exit(map, 0);
	return (0);
}

int	rendring(t_map *map)
{
	int (x), (y);
	if (!map || !map->map || !*(map->map))
		return (-1);
	map->mlx = mlx_init();
	x = SCALE * map->cord.height + 45;
	y = SCALE * map->cord.witdh;
	init_struct(map);
	init_enemy(map);
	map->rate = 24000 / (map->cord.height * map->cord.witdh);
	map->win = mlx_new_window(map->mlx, y, x, "so_long");
	init_all_xpms(map);
	init_all_xpms_adds(map);
	map->tex.composite.img = mlx_new_image(map->mlx, y, x);
	map->tex.composite.addr = mlx_get_data_addr(map->tex.composite.img,
			&map->tex.composite.bpp, &map->tex.composite.line_length,
			&map->tex.composite.endian);
	map->tex.composite.width = y;
	map->tex.composite.height = x;
	init_composit_image(map);
	mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
	mlx_hook(map->win, 2, 1L << 0, key_press, map);
	mlx_hook(map->win, 17, 0, mlx_exit, map);
	mlx_loop_hook(map->mlx, game_loop, map);
	mlx_loop(map->mlx);
	return (0);
}
