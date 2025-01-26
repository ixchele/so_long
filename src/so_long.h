/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:26:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/22 17:04:11 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include "../ft_printf/libft/libft.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "get_next_line/get_next_line.h"

#define LF 65361
#define UP 65362
#define RG 65363
#define DW 65364

typedef struct s_image
{
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;
    int width;
    int height;
}	t_image;

typedef struct	s_textures 
{
	t_image	exit;
    t_image grass;
	t_image	wall;
	t_image	coin;
    t_image player;
    t_image composite;
}	t_textures;

typedef struct	s_map
{
	void	*mlx;
	void	*win;
	char	**map;
	size_t		height;
	size_t		witdh;
	bool	is_there_exit;
	bool	is_there_player;
	int		items;
	size_t	player_x;
	size_t	player_y;
	t_textures	tex;
}	t_map;

void	window_displayer(t_map *map);
int 	rendring(t_map *map);

#endif // !SO_LONG_H
