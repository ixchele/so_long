/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparence.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:08:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/22 17:10:22 by zbengued         ###   ########.fr       */
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


static int i;

unsigned int	get_pixel_color(t_image *img, int x, int y)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)pixel);
}

void	put_pixel(t_image *img, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
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
		x = map->index * 70;
		int i = 0;
		while (x < 70 * (map->index + 1))
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

// void	player_idle(t_map *map)
// {
// 	
// }


///// --> separer les animations - draw elem ne pose que les statiques elemetns - 

void	draw_elements(t_map *map)
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
			else if (map->map[y][x] == 'C')
			{
				merge_images(&map->tex.composite, &map->tex.grass, 70 * x, 70 * y, 0xFF000000);
				merge_images(&map->tex.composite, &map->tex.coin[map->index], 70 * x, 70 * y, 0xFF000000);
			}
			else if (x == map->player.cord.x && y == map->player.cord.y)
			{
				//merge_images(&map->tex.composite, &map->tex.grass, 70 * x, 70 * y, 0xFF000000);
				merge_player_images(map,&map->tex.composite, &map->tex.player_idle, 70 * map->player.cord.x, 70 * map->player.cord.y, 0xFF000000);
			}
			else if (map->map[y][x] == 'E')
				merge_images(&map->tex.composite, &map->tex.exit, 70 * x, 70 * y, 0xFF000000);
			x++;		 
		}
		y++;
	}
}

// int	des_win(int keycode, t_map *map)
// {
// 	if ()
// 		mlx_destroy_window(map->mlx, map);
// 	return (0);
// }

bool	is_valid_moove(t_map *map, int n, int z)
{
	if (map->map[map->player.cord.y + n][map->player.cord.x + z] != '1' 
		&& map->map[map->player.cord.y + n][map->player.cord.x + z] != 'E')
		return (true);
	if (map->map[map->player.cord.y + n][map->player.cord.x + z] == 'E' && !map->items)
		return (true);
	return (false);
}

// void	reset_player_pos(t_map *map)
// {
// 	map.player_action = 0;
// }

int	key_press(int keycode, t_map *map)
{
 	int y = map->player.cord.y;
	int	x = map->player.cord.x;
	//printf("\n-------key = %d", keycode);
	if (keycode == LF && is_valid_moove(map, 0, -1))
		map->player.cord.x--;
	else if (keycode == UP && is_valid_moove(map, -1, 0))
		map->player.cord.y--;
	else if (keycode == RG && is_valid_moove(map, 0, 1))
		map->player.cord.x++;
	else if (keycode == DW && is_valid_moove(map, 1, 0))
		map->player.cord.y++;
	if (x != map->player.cord.x || y != map->player.cord.y)
	{	
		if (map->map[map->player.cord.y][map->player.cord.x] == 'C')
			map->items--;
		if (map->map[map->player.cord.y][map->player.cord.x] == 'E')
			exit(0);
		map->map[map->player.cord.y][map->player.cord.x] = '0';
		//merge_images(&map->tex.composite, &map->tex.grass, 70 * x, 70 * y, 0xFF000000);
		i++;
		printf(" ##### ==> i = %d", i);
	}
	return (0);
}

void	animate_coin(t_map *map)
{
	static int  count;

	draw_elements(map);
	if (count % 30 == 0)
	{
		map->index++;
		if (map->index == 6)
		{
			map->index = 0;
			count = 0;
		}
	}
	count++;
	mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
}


int game_loop(t_map *map)
{
	animate_coin(map);
	return(1);
}


int rendring(t_map *map) 
{	
    map->mlx = mlx_init();
	if (!map || !map->map || !*(map->map))
		return (-1);
	int x = 70 * map->cord.height;
	int	y = 70 * map->cord.witdh;
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
    map->tex.player_right.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/player_walk_right.xpm", &map->tex.player_right.width, &map->tex.player_right.height);
    map->tex.player_right.addr = mlx_get_data_addr(map->tex.player_right.img, &map->tex.player_right.bpp, &map->tex.player_right.line_length, &map->tex.player_right.endian);
    map->tex.composite.img = mlx_new_image(map->mlx, y, x);
    map->tex.composite.addr = mlx_get_data_addr(map->tex.composite.img, &map->tex.composite.bpp, &map->tex.composite.line_length, &map->tex.composite.endian);
	map->tex.composite.width = y;
    map->tex.composite.height = x;
	fill_with_texture(&map->tex.composite, &map->tex.grass);
	draw_elements(map);
	printf(" y = %zu - x = %zu\n", map->player.cord.y, map->player.cord.x);
    mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
	//mlx_key_hook(map->win, key_press, map);
	mlx_hook(map->win, 2, 1L<<0, key_press, map);
	mlx_loop_hook(map->mlx, game_loop, map);
    // mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
    mlx_loop(map->mlx);
    return 0;
}
