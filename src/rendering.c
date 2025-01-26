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

void merge_images(t_image *dest, t_image *src, int start_x, int start_y, unsigned int transparent_color)
{
	int			y;
	int			x;
	unsigned	color;

	y = 0;
	while (y < src->height)
	{
		x = 0;
		while (x < src->width)
		{
			color = get_pixel_color(src, x, y);
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
			if (map->map[y][x] == 'C')
				merge_images(&map->tex.composite, &map->tex.coin, 70 * x, 70 * y, 0xFF000000);
			if (x == map->player_x && y == map->player_y)
				merge_images(&map->tex.composite, &map->tex.player, 70 * x, 70 * y, 0xFF000000);
			if (map->map[y][x] == 'E')
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
	if (map->map[map->player_y + n][map->player_x + z] != '1' 
		&& map->map[map->player_y + n][map->player_x + z] != 'E')
		return (true);
	if (map->map[map->player_y + n][map->player_x + z] == 'E' && !map->items)
		return (true);
	return (false);
}

int	key_press(int keycode, t_map *map)
{
 	int y = map->player_y;
	int	x = map->player_x;
	printf("\n-------key = %d", keycode);
	if (keycode == LF && is_valid_moove(map, 0, -1))
		map->player_x--;
	else if (keycode == UP && is_valid_moove(map, -1, 0))
		map->player_y--;
	else if (keycode == RG && is_valid_moove(map, 0, 1))
		map->player_x++;
	else if (keycode == DW && is_valid_moove(map, 1, 0))
		map->player_y++;
	draw_elements(map);
	if (x != map->player_x || y != map->player_y)
	{	
		if (map->map[map->player_y][map->player_x] == 'C')
			map->items--;
		if (map->map[map->player_y][map->player_x] == 'E')
			exit(0);
		map->map[map->player_y][map->player_x] = '0';
		merge_images(&map->tex.composite, &map->tex.grass, 70 * x, 70 * y, 0xFF000000);
	}
    mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
	printf(" x%d = X%zu, y%d = Y%zu\n",x, map->player_x, y, map->player_y);
	return (0);
}

int rendring(t_map *map) 
{
    map->mlx = mlx_init();
	if (!map || !map->map || !*(map->map))
		return (-1);
	int x = 70 * map->height;
	int	y = 70 * map->witdh;
    map->win = mlx_new_window(map->mlx, y, x, "so_long");
    map->tex.exit.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/exit.xpm", &map->tex.exit.width, &map->tex.exit.height);
    map->tex.exit.addr = mlx_get_data_addr(map->tex.exit.img, &map->tex.exit.bpp, &map->tex.exit.line_length, &map->tex.exit.endian);
    map->tex.coin.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/coin.xpm", &map->tex.coin.width, &map->tex.coin.height);
    map->tex.coin.addr = mlx_get_data_addr(map->tex.coin.img, &map->tex.coin.bpp, &map->tex.coin.line_length, &map->tex.coin.endian);
    map->tex.wall.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/rock1737713551.xpm", &map->tex.wall.width, &map->tex.wall.height);
    map->tex.wall.addr = mlx_get_data_addr(map->tex.wall.img, &map->tex.wall.bpp, &map->tex.wall.line_length, &map->tex.wall.endian);
    map->tex.grass.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/grass.xpm", &map->tex.grass.width, &map->tex.grass.height);
    map->tex.grass.addr = mlx_get_data_addr(map->tex.grass.img, &map->tex.grass.bpp, &map->tex.grass.line_length, &map->tex.grass.endian);
    map->tex.player.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/player_0.xpm", &map->tex.player.width, &map->tex.player.height);
    map->tex.player.addr = mlx_get_data_addr(map->tex.player.img, &map->tex.player.bpp, &map->tex.player.line_length, &map->tex.player.endian);
    map->tex.composite.img = mlx_new_image(map->mlx, y, x);
    map->tex.composite.addr = mlx_get_data_addr(map->tex.composite.img, &map->tex.composite.bpp, &map->tex.composite.line_length, &map->tex.composite.endian);
	map->tex.composite.width = y;
    map->tex.composite.height = x;
	fill_with_texture(&map->tex.composite, &map->tex.grass);
	draw_elements(map);
	printf(" y = %zu - x = %zu\n", map->player_y, map->player_x);
    mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
	//mlx_key_hook(map->win, key_press, map);
	mlx_hook(map->win, 2, 1L<<0, key_press, map);
	//mlx_loop_hook(map->mlx, game_loop, &map);
    // mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
    mlx_loop(map->mlx);
    return 0;
}
