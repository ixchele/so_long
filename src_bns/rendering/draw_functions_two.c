/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions_tow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 22:04:46 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:04:52 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

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

void	choose_frame(t_image *frame, t_image *sprite, int frame_nbr)
{
	int				y;
	unsigned int	color;
	int				x;

	y = 0;
	color = 0;
	while (y < SCALE)
	{
		x = 0;
		while (x < SCALE)
		{
			color = get_pixel_color(sprite, x + (SCALE * frame_nbr), y);
			if (color != 0xFF000000)
				put_pixel(frame, x, y, color);
			x++;
		}
		y++;
	}
}

void	clear_frame(t_image *frame, t_map *map)
{
	int	x;

	int (y) = 0;
	while (y < SCALE)
	{
		x = 0;
		while (x < SCALE)
		{
			put_pixel(frame, x, y, get_pixel_color(&map->tex.grass, 0, 0));
			x++;
		}
		y++;
	}
}

void	fill_with_texture(t_image *composite, t_image *texture)
{
	static t_cord		cord = {0, 0, 0, 0};
	unsigned int		color;
	char				*src_pixel;
	char				*dst_pixel;

	int (tex_y), (tex_x);
	cord.y = 0;
	while (cord.y < composite->height)
	{
		cord.x = 0;
		while (cord.x < composite->width)
		{
			tex_x = cord.x % texture->width;
			tex_y = cord.y % texture->height;
			src_pixel = texture->addr + (tex_y * texture->line_length + tex_x
					* (texture->bpp / 8));
			color = *(unsigned int *)src_pixel;
			dst_pixel = composite->addr + (cord.y * composite->line_length
					+ cord.x * (composite->bpp / 8));
			*(unsigned int *)dst_pixel = color;
			cord.x++;
		}
		cord.y++;
	}
}
