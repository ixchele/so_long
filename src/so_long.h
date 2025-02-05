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
#include "../ft_printf/include/ft_printf.h"
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
#define ESC 65307

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
	t_image	coin[6];
	t_image	coin_;
    t_image player_idle;
    t_image player_up;
    t_image player_down;
    t_image player_left;
    t_image player_right;
	t_image	enemy_idle;
	t_image	enemy_up;
	t_image	enemy_down;
	t_image	enemy_left;
	t_image	enemy_right;
    t_image composite;
	t_image	frame;
}	t_textures;

typedef struct	s_cord
{
	int	x;
	int	y;
	size_t		height;
	size_t		witdh;
}	t_cord;

typedef struct s_player
{
	char	move;
	char 	*state;
	t_cord	cord;	
}	t_player;

typedef struct s_coin
{	
	bool	is_there;
	t_cord	cord;
}	t_coin;

typedef struct s_exit
{	
	bool	is_there;
	t_cord	cord;
}	t_exit;

typedef struct	s_enemy
{
	bool	is_there;
	char	move;
	t_cord	cord;
}	t_enemy;

typedef struct	s_map
{
	void	*mlx;
	void	*win;
	char	**map;
	bool	is_there_exit;
	bool	is_there_player;
	int		items;
	int		skel; // index of enemy nmb
	int		nmb_coins;
	int		i_player;
	int		i_coin;
	int		i_exit;
	int		i_enemy;
	int		exit_flag;
	t_player	player;
	t_exit		exit;
	t_coin		*coin;
	t_enemy		*enemy;
	t_cord		cord;
	t_textures	tex;
	int		count;
	int		dellay;
	int		frame_nmb;
	int		step;
	bool	anim;
	int 	rate;

}	t_map;

void	window_displayer(t_map *map);
int 	rendring(t_map *map);

#endif // !SO_LONG_H
