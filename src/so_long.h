/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:26:24 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/06 07:03:39 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

#include <mlx.h>
#include "../ft_printf/include/ft_printf.h"
#include <fcntl.h>
#include <time.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "get_next_line/get_next_line.h"

#define SCALE 70

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
	t_image	frame_player;
	t_image	frame_enemy[100];
}	t_textures;

typedef struct	s_cord
{
	int	x;
	int	y;
	int		height;
	int		witdh;
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
	unsigned 	i_coin;
	bool	taken;
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
	int		i_enemy;
    int		frame_nmb_enemy;
	int		step_enemy;
	int		count_enemy;
	bool	anim_enemy;
	float		dellay_enemy;
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
	int		skel;
	int				nmb_coins;
	unsigned int	i_player;
	int		i_coin;
	unsigned int		i_exit;
	int		exit_flag;
	t_player	player;
	t_exit		exit;
	t_coin		*coin;
	t_enemy		*enemy;
	t_cord		cord;
	t_textures	tex;
	int	frame_nmb_player;
    int	step_player;
	int		count_player;
	double		dellay_player;
	int		frame_nmb;
	bool	anim_player;
	int 	rate;
	int		new_rate;

}	t_map;

int		get_pixel_color(t_image *img, int x, int y);
void	put_pixel(t_image *img, int x, int y, unsigned int color);
int		get_t(int trgb);

void	merge_player_images(t_map *map, t_image *dest, t_image *src, int x, int y);
void 	merge_exit_images(t_map *map, t_image *dest, t_image *src, int start_x, int start_y);
void 	merge_coin_images(t_image *dest, t_image *src, int start_x, int start_y, unsigned int *index_x);
void 	merge_images(t_image *dest, t_image *src, int start_x, int start_y, unsigned int transparent_color);
void 	merge_enemy_images(t_map *map, t_image *src, int start_x, int start_y, int ind);

void	draw_enemy(t_map *map);
void	draw_coins(t_map *map);
void	draw_static_elements(t_map *map);
void	fill_with_texture(t_image *composite, t_image *texture);
void	remove_grass(t_map *map, int x, int y, int i);
void	remove_coin(t_map *map, int x, int y);
void	choose_frame(t_image *frame, t_image *sprite, int frame_nbr);
void 	clear_frame(t_image *frame, t_map *map);

void	animate_player(t_map *map);
void	animate_coin(t_map *map);
void	animate_move(t_map *map, t_image *tex, int coef_x, int coef_y);
void	animate_open_exit(t_map *map);
void	animate_enemy(t_map *map, int i);
void	animate_move_enemy(t_map *map, t_image *tex, int coef_x, int coef_y, int i);
void	animate_idle_enemy(t_map *map, int i);

double	get_distance(t_cord cord_p, t_cord cord_e);
void	move_enemy(t_enemy *enemy);
void	moove_player(t_map *map);
char	get_random_move();
char 	get_best_move(t_map *map, int i, int offset);
void	validate_move(t_map *map, int i);
bool	is_valid_move_enemy(t_map *map, int n, int z, int i);
bool	is_valid_move_player(t_map *map, int n, int z);
int		key_press(int keycode, t_map *map);

bool	compare_coords(t_cord *cord1, t_cord *cord2);
void	check_enemy(t_map *map);
void	check_exit(t_map *map, int x, int y);
void	check_coin(t_map *map, int x, int y);
void	enemy_loop(t_map *map);
int 	game_loop(t_map *map);
int		ft_exit(int i);
int 	rendring(t_map *map);



#endif // !SO_LONG_H
