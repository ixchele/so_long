/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:08:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/01 15:17:26 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <bits/time.h>
#include <math.h>
#include <mlx.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	get_pixel_color(t_image *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(int *)pixel);
}

void	put_pixel(t_image *img, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(int *)pixel = color;
}

// void	animate_player(t_map *map)
// {
// 	static int  count;
//
// 	draw_elements(map);
// 	if (count % 25 == 0)
// 	{
// 		map->index++;
// 		if (map->index == 6)
// 		{
// 			map->index = 0;
// 			count = 0;
// 		}
// 	}
// 	count++;
// 	mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
// }

void merge_player_images(t_map *map, t_image *dest, t_image *src, int start_x, int start_y, unsigned int transparent_color)
{
	int			y;
	int			x;
	unsigned	color;

	y = 0;
	while (y < 70)
	{
		x = map->i_player * 70;
		int i = 0;
		while (x < 70 * (map->i_player + 1))
		{
			color = get_pixel_color(src, x, y); // x + 70 * pos_x
			if (color != transparent_color)
				put_pixel(dest, start_x + i, start_y + y, color);
			x++;
			i++;
		}
		y++;
	}
}

void merge_images(t_image *dest, t_image *src, int start_x, int start_y, unsigned int transparent_color)
{
	int			y;
	int			x;
	unsigned	color;

	y = 0;
	while (y < 70)
	{
		x = 0;
		while (x < 70)
		{
			color = get_pixel_color(src, x, y); // x + 70 * pos_x
			if (color != transparent_color)
				put_pixel(dest, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void	fill_with_texture(t_image *composite, t_image *texture)
{
	int	y;
	int	x;
	int	tex_y;
	int	tex_x;
	unsigned int	color;
	char	*src_pixel;
	char	*dst_pixel;

	y = 0;
	while (y < composite->height)
	{
		x = 0;
		while (x < composite->width)
		{
			tex_x = x % texture->width;
			tex_y = y % texture->height;
			src_pixel = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bpp / 8));
			color = *(unsigned int *)src_pixel;
			dst_pixel = composite->addr + (y * composite->line_length + x * (composite->bpp / 8));
			*(unsigned int *)dst_pixel = color;
			x++;
		}
		y++;
	}	
}

///// --> separer les animations - draw elem ne pose que les statiques elemetns - 

void	draw_coins(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'C')
			{
				merge_images(&map->tex.composite, &map->tex.grass, 70 * x, 70 * y, 0xFF000000);
				merge_images(&map->tex.composite, &map->tex.coin[map->i_coin], 70 * x, 70 * y, 0xFF000000);
			}
			x++;		 
		}
		y++;
	}
}

// void	draw_player(t_map *map, t_image *move)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (map->map[y])
// 	{
// 		x = 0;
// 		while (map->map[y][x])
// 		{
// 			if (x == map->player.cord.x && y == map->player.cord.y)
// 			{
// 				merge_images(&map->tex.composite, &map->tex.grass, 70 * x, 70 * y, 0xFF000000);
// 				merge_player_images(map,&map->tex.composite, move, 70 * map->player.cord.x, 70 * map->player.cord.y, 0xFF000000);
// 			}
// 			x++;		 
// 		}
// 		y++;
// 	}
// }

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
				merge_images(&map->tex.composite, &map->tex.wall, 70 * x, 70 * y, 0xFF000000);
			else if (map->map[y][x] == 'E')
				merge_images(&map->tex.composite, &map->tex.exit, 70 * x, 70 * y, 0xFF000000);
			else if (map->map[y][x] == 'P')	// NOTE: Remove after FIX
				merge_images(&map->tex.composite, &map->tex.player_idle, 70 * x, 70 * y, 0xFF000000);
			else if (map->map[y][x] == 'C')
				merge_images(&map->tex.composite, &map->tex.coin[0], 70 * x, 70 * y, 0xFF000000);
			x++;		 
		}
		y++;
	}
}

bool	is_valid_moove(t_map *map, int n, int z)
{
	map->anim = true;
	if (map->map[map->player.cord.y + n][map->player.cord.x + z] != '1' 
		&& map->map[map->player.cord.y + n][map->player.cord.x + z] != 'E')
		return (true);
	if (map->map[map->player.cord.y + n][map->player.cord.x + z] == 'E' && !map->items)
		return (true);
	map->anim = false;
	return (false);
}

void	moove_player(t_map *map)
{
	if (map->player.move == 'L')
		map->player.cord.x--;
	if (map->player.move == 'R')
		map->player.cord.x++;
	if (map->player.move == 'U')
		map->player.cord.y--;
	if (map->player.move == 'D')
		map->player.cord.y++;
}

int	key_press(int keycode, t_map *map)
{
 	int y = map->player.cord.y;
	int	x = map->player.cord.x;
	static int i = 1;

	if (keycode == ESC)
		exit(0);
	if (map->anim)
		return (0);
	if (keycode == LF && is_valid_moove(map, 0, -1))
		map->player.move = 'L';
	else if (keycode == UP && is_valid_moove(map, -1, 0))
		map->player.move = 'U';
	else if (keycode == RG && is_valid_moove(map, 0, 1))
		map->player.move = 'R';
	else if (keycode == DW && is_valid_moove(map, 1, 0))
		map->player.move = 'D';
	return (0);
}

void	animate_coin(t_map *map)
{
	static int	count = 0;
	
	if (count % 60 == 0)
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

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

void	choose_frame(t_image *frame, t_image *sprite, int frame_nbr)
{
	int y = 0;
	int color = 0;
	while (y < 70)
	{
		int x = 0;
		while (x < 70)
		{
			color = get_pixel_color(sprite, x + 70 * frame_nbr, y);
			if (!get_t(color))
				put_pixel(frame, x, y, color);
			x++;
		}
		y++;
	}
}
void clear_frame(t_image *frame, t_map *map)
{
	int x;

	int (y) = 0;
	while (y < 70)
	{
		x = 0;
		while (x < 70)
		{
			put_pixel(frame, x, y, get_pixel_color(&map->tex.grass, 0, 0));
			x++;
		}
		y++;
	}
}

void	animate_move(t_map *map, t_image *tex, int *frame_nmb, int *step, int coef_x, int coef_y)
{
	clear_frame(&map->tex.frame, map);
	map->frame_nmb %= 6;
	choose_frame(&map->tex.frame, tex, map->frame_nmb);
	// mlx_put_image_to_window(map->mlx, map->win, map->tex.frame.img, map->player.cord.x * 70 + coef_x * (map->step) , map->player.cord.y * 70 + (*step) * coef_y);
	merge_player_images(map, &map->tex.composite, &map->tex.frame, map->player.cord.x * 70 + coef_x * (map->step) , map->player.cord.y * 70 + (*step) * coef_y, 0xFF000000);
	map->step += 10;
	map->frame_nmb++;
	// clear_frame(&map->tex.frame, map);
}

void	animate_player(t_map *map)
{
	// if (map->player.move == 'R')
	// 	draw_player(map, &map->tex.player_right);
	// else
	// 	draw_player(map, &map->tex.player_idle);
	// map->count++;
	if (map->count % 50 == 0)
	{
		map->i_player++;
		if (map->i_player == 6)
		{
			map->i_player = 0;
			map->count = 0;
		}
	}
	if (map->step >= 70)
	{	
	 	int y = map->player.cord.y;
		int	x = map->player.cord.x;
		moove_player(map);
		if (x != map->player.cord.x || y != map->player.cord.y)
		{	
			if (map->map[map->player.cord.y][map->player.cord.x] == 'C')
				map->items--;
			if (map->map[map->player.cord.y][map->player.cord.x] == 'E')
				exit(0); // the end of the game 
			map->map[map->player.cord.y][map->player.cord.x] = '0';
			merge_images(&map->tex.composite, &map->tex.grass, 70 * x, 70 * y, 0xFF000000);
		}
		map->step = 0;
		map->player.move = 'I';
		map->anim = false;
	}
	map->dellay++;
	if (map->dellay % 30 == 0)
	{
		printf("%d\n", map->dellay);
		// mlx_put_image_to_window(map->mlx, map->win, map->tex.grass.img, map->player.cord.x * 70 , map->player.cord.y * 70);
		merge_images(&map->tex.composite, &map->tex.grass, 70 * map->player.cord.x, 70 * map->player.cord.y, 0xFF000000);
		if (map->player.move == 'R')
			animate_move(map, &map->tex.player_right, &map->frame_nmb, &map->step, 1, 0);
		else if (map->player.move == 'L')
			animate_move(map, &map->tex.player_left, &map->frame_nmb, &map->step, -1, 0);
		else if (map->player.move == 'U')
			animate_move(map, &map->tex.player_up, &map->frame_nmb, &map->step, 0, -1);
		else if (map->player.move == 'D')
			animate_move(map, &map->tex.player_down, &map->frame_nmb, &map->step, 0, 1);
		else if (map->player.move == 'I')
		{
			clear_frame(&map->tex.frame, map);
			choose_frame(&map->tex.frame, &map->tex.player_idle, map->i_player);
			// mlx_put_image_to_window(map->mlx, map->win, map->tex.frame.img, map->player.cord.x * 70, map->player.cord.y * 70);
			merge_player_images(map, &map->tex.composite, &map->tex.frame, 70 * map->player.cord.x, 70 * map->player.cord.y, 0xFF000000);
		}
	}
	map->count++;
}

int game_loop(t_map *map)
{
	animate_coin(map);
	animate_player(map);
	mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
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
}

int rendring(t_map *map) 
{	
    map->mlx = mlx_init();
	if (!map || !map->map || !*(map->map))
		return (-1);
	int x = 70 * map->cord.height;
	int	y = 70 * map->cord.witdh;
	map->count = 0;
	map->dellay = 0;
	map->frame_nmb = 0;
	map->step = 0;
	map->player.move = 'I';
	map->tex.frame.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/grass.xpm", &map->tex.frame.width, &map->tex.frame.height);
    map->tex.frame.addr = mlx_get_data_addr(map->tex.frame.img, &map->tex.frame.bpp, &map->tex.frame.line_length, &map->tex.frame.endian);
	map->tex.coin_.img = mlx_xpm_file_to_image(map->mlx, "../textures/coin.xpm", &map->tex.coin_.width, &map->tex.coin_.height);
    map->tex.coin_.addr = mlx_get_data_addr(map->tex.coin_.img, &map->tex.coin_.bpp, &map->tex.coin_.line_length, &map->tex.coin_.endian);
    map->win = mlx_new_window(map->mlx, y, x, "so_long");
    map->tex.exit.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/exit.xpm", &map->tex.exit.width, &map->tex.exit.height);
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
	//mlx_key_hook(map->win, key_press, map);
	mlx_hook(map->win, 2, 1L<<0, key_press, map);
	mlx_loop_hook(map->mlx, game_loop, map);
    // mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
    mlx_loop(map->mlx);
    return 0;
}
