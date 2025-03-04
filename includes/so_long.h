/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:07:19 by zbengued          #+#    #+#             */
/*   Updated: 2025/03/04 04:44:36 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

# define SCALE 70

# define LF 65361
# define UP 65362
# define RG 65363
# define DW 65364
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100

typedef struct s_image
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct s_textures
{
	t_image			tr_im;
	t_image			exit;
	t_image			grass;
	t_image			wall;
	t_image			coin[6];
	t_image			coin_;
	t_image			p_i;
	t_image			p_u;
	t_image			p_d;
	t_image			p_l;
	t_image			p_r;
	t_image			e_i;
	t_image			e_u;
	t_image			e_d;
	t_image			e_l;
	t_image			e_r;
	t_image			win;
	t_image			lose;
	t_image			composite;
	t_image			frame_player;
	t_image			frame_enemy[100];
}					t_textures;

typedef struct s_cord
{
	int				x;
	int				y;
	int				height;
	int				witdh;
}					t_cord;

typedef struct s_player
{
	char			move;
	char			*state;
	t_cord			cord;
}					t_player;

typedef struct s_coin
{
	bool			is_there;
	t_cord			cord;
	int				i_coin;
	bool			taken;
}					t_coin;

typedef struct s_exit
{
	bool			is_there;
	t_cord			cord;
}					t_exit;

typedef struct s_enemy
{
	bool			is_there;
	char			move;
	int				stuned;
	int				i_enemy;
	int				frame_nmb_enemy;
	int				step_enemy;
	int				count_enemy;
	bool			anim_enemy;
	float			dellay_enemy;
	t_cord			cord;
}					t_enemy;

typedef struct s_map
{
	void			*mlx;
	void			*win;
	char			*line;
	char			**map;
	char			**flood_map;
	bool			is_there_exit;
	bool			is_there_player;
	int				items;
	int				skel;
	int				nmb_coins;
	unsigned int	i_player;
	int				i_coin;
	unsigned int	i_exit;
	int				exit_flag;
	t_player		player;
	t_exit			exit;
	t_coin			*coin;
	t_enemy			*enemy;
	t_cord			cord;
	t_textures		tex;
	int				frame_nmb_player;
	int				step_player;
	int				nmb_steps_player;
	char			*nmb_of_steps;
	int				count_player;
	double			dellay_player;
	int				frame_nmb;
	bool			anim_player;
	int				rate;
	int				new_rate;
	int				line_length;
	int				new_line_length;

}					t_map;

void				safe_free(void *obj);
void				safe_destroy(t_map *map, void *obj);
void				destroy_images(t_map *map);
void				free_array(char **arr);
void				ft_error(t_map *map, char *str);
void				ft_exit(t_map *map, int code);
int					mlx_exit(t_map *map);
void				valid_file_name(t_map *map, char *file);

void				get_player_inf(t_map *map, int i, int j);
void				get_coin_inf(t_map *map, int i, int j);
void				get_enemy_inf(t_map *map, int i, int j);
void				get_exit_inf(t_map *map, int i, int j);

void				read_(const char *file, t_map *map);
void				is_valid(t_map *map);
bool				is_playable(t_map *map);
bool				check_elements(t_map *map);
bool				check_walls(t_map *map);

int					get_pixel_color(t_image *img, int x, int y);
void				put_pixel(t_image *img, int x, int y, unsigned int color);
int					get_t(int trgb);

void				merge_player_images(t_map *map, t_image *dest, t_image *src,
						t_cord start);
void				merge_exit_images(t_map *map, t_image *dest, t_image *src,
						t_cord start);
void				merge_coin_images(t_image *dest, t_image *src, t_cord start,
						int *index_x);
void				merge_images(t_image *dest, t_image *src, t_cord start);
void				merge_enemy_images(t_map *map, t_image *src, t_cord start,
						int ind);
void				init_all_xpms_adds(t_map *map);
void				draw_enemy(t_map *map);
void				draw_coins(t_map *map);
void				draw_static_elements(t_map *map);
void				fill_with_texture(t_image *composite, t_image *texture);
void				remove_grass(t_map *map, int x, int y, int i);
void				remove_coin(t_map *map, int x, int y);
void				choose_frame(t_image *frame, t_image *sprite,
						int frame_nbr);
void				clear_frame(t_image *frame, t_map *map);

void				animate_player(t_map *map);
void				animate_coin(t_map *map);
void				animate_move(t_map *map, t_image *tex, int coef_x,
						int coef_y);
void				animate_open_exit(t_map *map);
void				animate_enemy(t_map *map, int i);
void				animate_move_enemy(t_map *map, t_image *tex, t_cord coef,
						int i);
void				animate_idle_enemy(t_map *map, int i);

double				get_distance(t_cord cord_p, t_cord cord_e);
void				move_enemy(t_enemy *enemy);
void				moove_player(t_map *map);
char				get_random_move(void);
char				get_best_move(t_map *map, int i, int offset);
void				validate_move(t_map *map, int i);
bool				is_valid_move_enemy(t_map *map, int n, int z, int i);
bool				is_valid_move_player(t_map *map, int n, int z);
int					key_press(int keycode, t_map *map);

bool				compare_coords(t_cord *cord1, t_cord *cord2);
void				check_enemy(t_map *map);
void				check_exit(t_map *map, int x, int y);
void				check_coin(t_map *map, int x, int y);
void				enemy_loop(t_map *map);
int					game_loop(t_map *map);
int					rendring(t_map *map);

void				init_xpm_1(t_map *map);
void				init_xpm_2(t_map *map);
void				init_xpm_3(t_map *map);
void				init_xpm_4(t_map *map);
void				init_xpm_5(t_map *map);

void				init_enemy(t_map *map);
void				init_struct(t_map *map);
void				init_composit_image(t_map *map);
void				init_all_xpms(t_map *map);

void				win_loop(t_map *map);
void				lose_loop(t_map *map);
int					you_win(t_map *map);
int					you_lose(t_map *map);

#endif // !SO_LONG_H
