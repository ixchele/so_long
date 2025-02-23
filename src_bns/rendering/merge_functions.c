/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 21:26:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/12 21:59:42 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	merge_player_images(t_map *map, t_image *dest, t_image *src,
		t_cord start)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	i;
	unsigned int	color;

	y = 0;
	while (y < SCALE)
	{
		x = map->i_player * SCALE;
		i = 0;
		while (x < SCALE * (map->i_player + 1))
		{
			color = get_pixel_color(src, x, y);
			if (color != 0xFF000000)
				put_pixel(dest, start.x + i, start.y + y, color);
			else
				put_pixel(dest, start.x + i, start.y + y,
					get_pixel_color(&map->tex.grass, 0, 0));
			x++;
			i++;
		}
		y++;
	}
}

void	merge_exit_images(t_map *map, t_image *dest, t_image *src, t_cord start)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	i;
	unsigned int	color;

	y = 0;
	while (y < SCALE)
	{
		x = map->i_exit * SCALE;
		i = 0;
		while (x < SCALE * (map->i_exit + 1))
		{
			color = get_pixel_color(src, x, y);
			if (color != 0xFF000000)
				put_pixel(dest, start.x + i, start.y + y, color);
			else
				put_pixel(dest, start.x + i, start.y + y,
					get_pixel_color(&map->tex.grass, 0, 0));
			x++;
			i++;
		}
		y++;
	}
}

void	merge_coin_images(t_image *dest, t_image *src, t_cord start,
					int *index_x)
{
	unsigned int	y;
	unsigned int	x;
	unsigned int	i;
	unsigned int	color;
	int				j;

	y = SCALE;
	j = 0;
	while (y < SCALE * 2)
	{
		x = *index_x * SCALE;
		i = 0;
		while (x < SCALE * (unsigned int)(*index_x + 1))
		{
			color = get_pixel_color(src, x, y);
			if (color != 0xFF000000)
				put_pixel(dest, start.x + i, start.y + j, color);
			x++;
			i++;
		}
		j++;
		y++;
	}
	*index_x += 1;
}

void	merge_images(t_image *dest, t_image *src, t_cord start)
{
	int				y;
	int				x;
	unsigned int	color;

	y = 0;
	while (y < SCALE)
	{
		x = 0;
		while (x < SCALE)
		{
			color = get_pixel_color(src, x, y);
			if (color != 0xFF000000)
				put_pixel(dest, start.x + x, start.y + y, color);
			x++;
		}
		y++;
	}
}

void	merge_enemy_images(t_map *map, t_image *src, t_cord start, int ind)
{
	int				y;
	int				x;
	unsigned int	color;
	int				i;

	y = 0;
	while (y < 70)
	{
		x = map->enemy[ind].i_enemy * 70;
		i = 0;
		while (x < 70 * (map->enemy[ind].i_enemy + 1))
		{
			color = get_pixel_color(src, x, y);
			if (color != 0xFF000000)
				put_pixel(&map->tex.composite, start.x + i, start.y + y, color);
			x++;
			i++;
		}
		y++;
	}
}
