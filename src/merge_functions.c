/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:26:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:05:02 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void merge_player_images(t_map *map, t_image *dest, t_image *src, int start_x, int start_y)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	i;
	unsigned		color;

	y = 0;
	while (y < SCALE)
	{
		x = map->i_player * SCALE;
		i = 0;
		while (x < SCALE * (map->i_player + 1))
		{
			color = get_pixel_color(src, x, y); // x + SCALE * pos_x
			if (color != 0xFF000000)
				put_pixel(dest, start_x + i, start_y + y, color);
			else
				put_pixel(dest, start_x + i, start_y + y, get_pixel_color(&map->tex.grass, 0, 0));
			x++;
			i++;
		}
		y++;
	}
}

void merge_exit_images(t_map *map, t_image *dest, t_image *src, int start_x, int start_y)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	i;
	unsigned		color;

	y = 0;
	while (y < SCALE)
	{
		x = map->i_exit * SCALE;
		i = 0;
		while (x < SCALE * (map->i_exit + 1))
		{
			color = get_pixel_color(src, x, y); // x + SCALE * pos_x
			if (color != 0xFF000000)
				put_pixel(dest, start_x + i, start_y + y, color);
			else
				put_pixel(dest, start_x + i, start_y + y, get_pixel_color(&map->tex.grass, 0, 0));
			x++;
			i++;
		}
		y++;
	}
}

void merge_coin_images(t_image *dest, t_image *src, int start_x, int start_y, unsigned int *index_x)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	i;
	unsigned		color;

	y = SCALE;
	int j = 0;
	while (y < SCALE * 2)
	{
		x = *index_x * SCALE;
		i = 0;
		while (x < SCALE * (*index_x + 1))
		{
			color = get_pixel_color(src, x, y); // x + SCALE * pos_x
			//printf("j = %d, i = %d\n", j, i);
			if (color != 0xFF000000)
				put_pixel(dest, start_x + i, start_y + j, color);
			x++;
			i++;
		}
		j++;
		y++;
	}
	*index_x += 1;
}

void merge_images(t_image *dest, t_image *src, int start_x, int start_y, unsigned int transparent_color)
{
	int			y;
	int			x;
	unsigned	color;

	y = 0;
	while (y < SCALE)
	{
		x = 0;
		while (x < SCALE)
		{
			color = get_pixel_color(src, x, y); // x + SCALE * pos_x
			if (color != transparent_color) //0xFF000000
				put_pixel(dest, start_x + x, start_y + y, color);
			x++;
		}
		y++;
	}
}

void merge_enemy_images(t_map *map, t_image *src, int start_x, int start_y, int ind)
{
	int			y;
	int			x;
	unsigned	color;

	y = 0;
	while (y < 70)
	{
		x = map->enemy[ind].i_enemy * 70;
		int i = 0;
		while (x < 70 * (map->enemy[ind].i_enemy + 1))
		{
			color = get_pixel_color(src, x, y); // x + 70 * pos_x
			if (color != 0xFF000000)
				put_pixel(&map->tex.composite, start_x + i, start_y + y, color);
			x++;
			i++;
		}
		y++;
	}
}
