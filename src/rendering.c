/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:08:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:05:40 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define SCALE 70

void	enemy_loop(t_map *map)
{
	int i = 0;
	static int id = 0;
	srand(time(NULL) ^ (id * 12345));
	id++;
	while (i < map->skel)
	{
		if (map->enemy[i].is_there == true)
		{	
			if (get_distance(map->player.cord, map->enemy[i].cord) <= 5.0f && !map->enemy[i].anim_enemy)
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

int game_loop(t_map *map)
{
	animate_player(map);
	animate_coin(map);
	enemy_loop(map);
	if (map->nmb_coins == 0)
		animate_open_exit(map);
	mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
	mlx_string_put(map->mlx, map->win, 10, 10, 0xFF0000, "zakaria howa li kayn");
	return(1);
}

void	init_xpm(t_map	*map)
{
    map->tex.player_right.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Char_walk_right.xpm", &map->tex.player_right.width, &map->tex.player_right.height);
    map->tex.player_right.addr = mlx_get_data_addr(map->tex.player_right.img, &map->tex.player_right.bpp, &map->tex.player_right.line_length, &map->tex.player_right.endian);
    map->tex.player_left.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Char_walk_left.xpm", &map->tex.player_left.width, &map->tex.player_left.height);
    map->tex.player_left.addr = mlx_get_data_addr(map->tex.player_left.img, &map->tex.player_left.bpp, &map->tex.player_left.line_length, &map->tex.player_left.endian);
    map->tex.player_up.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Char_walk_up.xpm", &map->tex.player_up.width, &map->tex.player_up.height);
    map->tex.player_up.addr = mlx_get_data_addr(map->tex.player_up.img, &map->tex.player_up.bpp, &map->tex.player_up.line_length, &map->tex.player_up.endian);
    map->tex.player_down.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Char_walk_down.xpm", &map->tex.player_down.width, &map->tex.player_down.height);
    map->tex.player_down.addr = mlx_get_data_addr(map->tex.player_down.img, &map->tex.player_down.bpp, &map->tex.player_down.line_length, &map->tex.player_down.endian);
    map->tex.enemy_right.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_walk_right.xpm", &map->tex.enemy_right.width, &map->tex.enemy_right.height);
    map->tex.enemy_right.addr = mlx_get_data_addr(map->tex.enemy_right.img, &map->tex.enemy_right.bpp, &map->tex.enemy_right.line_length, &map->tex.enemy_right.endian);
    map->tex.enemy_left.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_walk_left.xpm", &map->tex.enemy_left.width, &map->tex.enemy_left.height);
    map->tex.enemy_left.addr = mlx_get_data_addr(map->tex.enemy_left.img, &map->tex.enemy_left.bpp, &map->tex.enemy_left.line_length, &map->tex.enemy_left.endian);
    map->tex.enemy_up.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_walk_up.xpm", &map->tex.enemy_up.width, &map->tex.enemy_up.height);
    map->tex.enemy_up.addr = mlx_get_data_addr(map->tex.enemy_up.img, &map->tex.enemy_up.bpp, &map->tex.enemy_up.line_length, &map->tex.enemy_up.endian);
    map->tex.enemy_down.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_walk_down.xpm", &map->tex.enemy_down.width, &map->tex.enemy_down.height);
    map->tex.enemy_down.addr = mlx_get_data_addr(map->tex.enemy_down.img, &map->tex.enemy_down.bpp, &map->tex.enemy_down.line_length, &map->tex.enemy_down.endian);
    map->tex.enemy_idle.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_idle_down.xpm", &map->tex.enemy_idle.width, &map->tex.enemy_idle.height);
    map->tex.enemy_idle.addr = mlx_get_data_addr(map->tex.enemy_idle.img, &map->tex.enemy_idle.bpp, &map->tex.enemy_idle.line_length, &map->tex.enemy_idle.endian);
}

int	ft_exit(int i)
{
	exit(i);
	return (0);
}

int rendring(t_map *map) 
{	
    map->mlx = mlx_init();
	if (!map || !map->map || !*(map->map))
		return (-1);
	int x = SCALE * map->cord.height;
	int	y = SCALE * map->cord.witdh;
	int i = 0;
	while (i < map->skel)
	{
		map->enemy[i].count_enemy = 0;
		map->enemy[i].dellay_enemy = 0;
		map->enemy[i].step_enemy = 0;
		map->enemy[i].frame_nmb_enemy = 0;
		map->enemy[i].i_enemy = 0;
		map->enemy[i].anim_enemy = false;
		map->tex.frame_enemy[i].img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/grass.xpm", &map->tex.frame_enemy[i].width, &map->tex.frame_enemy[i].height);
		map->tex.frame_enemy[i].addr = mlx_get_data_addr(map->tex.frame_enemy[i].img, &map->tex.frame_enemy[i].bpp, &map->tex.frame_enemy[i].line_length, &map->tex.frame_enemy[i].endian);
		i++;
	}
	map->count_player = 0;
	map->dellay_player = 0;
	map->frame_nmb_player = 0;
	map->step_player = 0;
	map->player.move = 'I';
	map->i_exit = 0;
	map->exit_flag = 0;
	map->nmb_coins = map->items;
	int size = (map->cord.height * map->cord.witdh);
 	map->rate = 24000 / size;
	map->tex.frame_player.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/grass.xpm", &map->tex.frame_player.width, &map->tex.frame_player.height);
    map->tex.frame_player.addr = mlx_get_data_addr(map->tex.frame_player.img, &map->tex.frame_player.bpp, &map->tex.frame_player.line_length, &map->tex.frame_player.endian);
	map->tex.coin_.img = mlx_xpm_file_to_image(map->mlx, "../textures/coin.xpm", &map->tex.coin_.width, &map->tex.coin_.height);
    map->tex.coin_.addr = mlx_get_data_addr(map->tex.coin_.img, &map->tex.coin_.bpp, &map->tex.coin_.line_length, &map->tex.coin_.endian);
    map->win = mlx_new_window(map->mlx, y, x, "so_long");
    map->tex.exit.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Chest.xpm", &map->tex.exit.width, &map->tex.exit.height);
    map->tex.exit.addr = mlx_get_data_addr(map->tex.exit.img, &map->tex.exit.bpp, &map->tex.exit.line_length, &map->tex.exit.endian);
    map->tex.coin[0].img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/coin/coin_0.xpm", &map->tex.coin[0].width, &map->tex.coin[0].height);
    map->tex.coin[1].img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/coin/coin_1.xpm", &map->tex.coin[1].width, &map->tex.coin[1].height);
    map->tex.coin[2].img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/coin/coin_2.xpm", &map->tex.coin[2].width, &map->tex.coin[2].height);
    map->tex.coin[3].img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/coin/coin_3.xpm", &map->tex.coin[3].width, &map->tex.coin[3].height);
    map->tex.coin[4].img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/coin/coin_4.xpm", &map->tex.coin[4].width, &map->tex.coin[4].height);
    map->tex.coin[5].img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/coin/coin_5.xpm", &map->tex.coin[5].width, &map->tex.coin[5].height);
    map->tex.coin[0].addr = mlx_get_data_addr(map->tex.coin[0].img, &map->tex.coin[0].bpp, &map->tex.coin[0].line_length, &map->tex.coin[0].endian);
    map->tex.coin[1].addr = mlx_get_data_addr(map->tex.coin[1].img, &map->tex.coin[1].bpp, &map->tex.coin[1].line_length, &map->tex.coin[1].endian);
    map->tex.coin[2].addr = mlx_get_data_addr(map->tex.coin[2].img, &map->tex.coin[2].bpp, &map->tex.coin[2].line_length, &map->tex.coin[2].endian);
    map->tex.coin[3].addr = mlx_get_data_addr(map->tex.coin[3].img, &map->tex.coin[3].bpp, &map->tex.coin[3].line_length, &map->tex.coin[3].endian);
    map->tex.coin[4].addr = mlx_get_data_addr(map->tex.coin[4].img, &map->tex.coin[4].bpp, &map->tex.coin[4].line_length, &map->tex.coin[4].endian);
    map->tex.coin[5].addr = mlx_get_data_addr(map->tex.coin[5].img, &map->tex.coin[5].bpp, &map->tex.coin[5].line_length, &map->tex.coin[5].endian);
    map->tex.wall.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/rock1737713551.xpm", &map->tex.wall.width, &map->tex.wall.height);
    map->tex.wall.addr = mlx_get_data_addr(map->tex.wall.img, &map->tex.wall.bpp, &map->tex.wall.line_length, &map->tex.wall.endian);
    map->tex.grass.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/grass.xpm", &map->tex.grass.width, &map->tex.grass.height);
    map->tex.grass.addr = mlx_get_data_addr(map->tex.grass.img, &map->tex.grass.bpp, &map->tex.grass.line_length, &map->tex.grass.endian);
    map->tex.player_idle.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Char_idle_down.xpm", &map->tex.player_idle.width, &map->tex.player_idle.height);
    map->tex.player_idle.addr = mlx_get_data_addr(map->tex.player_idle.img, &map->tex.player_idle.bpp, &map->tex.player_idle.line_length, &map->tex.player_idle.endian);
	init_xpm(map);
    map->tex.composite.img = mlx_new_image(map->mlx, y, x);
    map->tex.composite.addr = mlx_get_data_addr(map->tex.composite.img, &map->tex.composite.bpp, &map->tex.composite.line_length, &map->tex.composite.endian);
	map->tex.composite.width = y;
    map->tex.composite.height = x;
	fill_with_texture(&map->tex.composite, &map->tex.grass);
	draw_static_elements(map);
	printf(" y = %du - x = %du\n", map->player.cord.y, map->player.cord.x);
    mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
	mlx_hook(map->win, 2, 1L<<0, key_press, map);
	mlx_hook(map->win, 17, 0, ft_exit, 0); 
	mlx_loop_hook(map->mlx, game_loop, map);
    mlx_loop(map->mlx);
    return 0;
}
