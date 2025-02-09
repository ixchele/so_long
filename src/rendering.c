/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_t.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:08:09 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/06 07:06:06 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define SCALE 70


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

void	draw_enemy(t_map *map)
{
	int i;

	i = 0;
	while (i < map->skel)
	{
		if (map->enemy[i].is_there == true)
		{
			merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, 0xFF000000);
			merge_enemy_images(map, &map->tex.composite, &map->tex.enemy_idle, SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, i);
		}
		i++;
	}
}

void	draw_coins(t_map *map)
{
	int y;

	y = 0;
	while (y < map->items)
	{
		if (map->coin[y].is_there == true)
		{
			merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y, 0xFF000000);
			merge_images(&map->tex.composite, &map->tex.coin[map->i_coin], SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y, 0xFF000000);
		}
		else if (map->coin[y].is_there == false && map->coin[y].taken == false)
		{
			merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y, 0xFF000000);
			merge_coin_images(&map->tex.composite, &map->tex.coin_, SCALE * map->coin[y].cord.x, SCALE * map->coin[y].cord.y, &map->coin[y].i_coin);
			if (map->coin[y].i_coin == 6)
				map->coin[y].taken = true;
		}
		y++;
	}
}

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
				merge_images(&map->tex.composite, &map->tex.wall, SCALE * x, SCALE * y, 0xFF000000);
			else if (map->map[y][x] == 'E')
				merge_images(&map->tex.composite, &map->tex.exit, SCALE * x, SCALE * y, 0xFF000000);
			else if (map->map[y][x] == 'P')	// NOTE: Remove after FIX
				merge_images(&map->tex.composite, &map->tex.player_idle, SCALE * x, SCALE * y, 0xFF000000);
			else if (map->map[y][x] == 'C')
				merge_images(&map->tex.composite, &map->tex.coin[0], SCALE * x, SCALE * y, 0xFF000000);
			else if (map->map[y][x] == 'X')
				merge_images(&map->tex.composite, &map->tex.enemy_idle, SCALE * x, SCALE * y, 0xFF000000);
			x++;		 
		}
		y++;
	}
}

bool	is_valid_move_enemy(t_map *map, int n, int z, int i)
{
	map->enemy[i].anim_enemy = true;
	if (map->map[map->enemy[i].cord.y + n][map->enemy[i].cord.x + z] != '1' 
		&& map->map[map->enemy[i].cord.y + n][map->enemy[i].cord.x + z] != 'E'
		&& map->map[map->enemy[i].cord.y + n][map->enemy[i].cord.x + z] != 'X'
		&& map->map[map->enemy[i].cord.y + n][map->enemy[i].cord.x + z] != 'C')
		return (true);
	map->enemy[i].anim_enemy = false;
	return (false);
}

bool	is_valid_move_player(t_map *map, int n, int z)
{
	map->anim_player = true;
	if (map->map[map->player.cord.y + n][map->player.cord.x + z] != '1' 
		&& map->map[map->player.cord.y + n][map->player.cord.x + z] != 'E')
		return (true);
	if (map->map[map->player.cord.y + n][map->player.cord.x + z] == 'E' && !map->nmb_coins)
		return (true);
	map->anim_player = false;
	return (false);
}

void	moove_player(t_map *map)
{
	if (map->player.move == 'L')
		map->player.cord.x--;
	else if (map->player.move == 'R')
		map->player.cord.x++;
	else if (map->player.move == 'U')
		map->player.cord.y--;
	else if (map->player.move == 'D')
		map->player.cord.y++;
}

int	key_press(int keycode, t_map *map)
{
	if (keycode == ESC)
		exit(0);
	if (map->anim_player)
		return (0);
	if (keycode == LF && is_valid_move_player(map, 0, -1))
		map->player.move = 'L';
	else if (keycode == UP && is_valid_move_player(map, -1, 0))
		map->player.move = 'U';
	else if (keycode == RG && is_valid_move_player(map, 0, 1))
		map->player.move = 'R';
	else if (keycode == DW && is_valid_move_player(map, 1, 0))
		map->player.move = 'D';
	return (0);
}

void	animate_coin(t_map *map)
{
	static int	count = 0;

	if (count % (int)(map->rate * 0.78f) == 0)
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

void	animate_idle_enemy(t_map *map, int i)
{
	static int	count = 0;

	if (count % map->rate == 0)
	{
		draw_enemy(map);
		map->enemy[i].i_enemy++;
		if (map->enemy[i].i_enemy == 6)
		{
			map->enemy[i].i_enemy = 0;
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
	while (y < SCALE)
	{
		int x = 0;
			while (x < SCALE)
		{
			color = get_pixel_color(sprite, x + (SCALE * frame_nbr), y);
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

void	animate_move(t_map *map, t_image *tex, int coef_x, int coef_y)
{
	clear_frame(&map->tex.frame_player, map);
	map->frame_nmb_player %= 6;
	choose_frame(&map->tex.frame_player, tex, map->frame_nmb_player);
	merge_player_images(map, &map->tex.composite, &map->tex.frame_player, map->player.cord.x * SCALE + coef_x * (map->step_player) , map->player.cord.y * SCALE + coef_y * (map->step_player), map->i_player);
	map->step_player += 10;
	map->frame_nmb_player++;
}

void	animate_move_enemy(t_map *map, t_image *tex, int coef_x, int coef_y, int i)
{
	clear_frame(&map->tex.frame_enemy[i], map);
	map->enemy[i].frame_nmb_enemy %= 6;
	choose_frame(&map->tex.frame_enemy[i], tex, map->enemy[i].frame_nmb_enemy);
	merge_player_images(map, &map->tex.composite, &map->tex.frame_enemy[i], map->enemy[i].cord.x * SCALE + coef_x * (map->enemy[i].step_enemy) , map->enemy[i].cord.y * SCALE + coef_y * (map->enemy[i].step_enemy), map->enemy[i].i_enemy);
	map->enemy[i].step_enemy += 10;
	map->enemy[i].frame_nmb_enemy++;
}


bool	compare_coords(t_cord *cord1, t_cord *cord2)
{
	if (cord1->x == cord2->x && cord1->y == cord2->y)
		return (true);
	return (false);
}

void	check_enemy(t_map *map)
{	
	int i = 0;
	while (i < map->skel)
	{
		if (compare_coords(&map->enemy[i].cord, &map->player.cord))
			exit(0);
		i++;
	}
}

void	remove_grass(t_map *map, int x, int y, int i)
{
	check_enemy(map);
	map->map[y][x] = '0';
	map->map[map->enemy[i].cord.y][map->enemy[i].cord.x] = 'X';
	merge_images(&map->tex.composite, &map->tex.grass, SCALE * x, SCALE * y, 0xFF000000);
}

void	remove_coin(t_map *map, int x, int y)
{
	static int i = 1;
	check_enemy(map);
	map->map[y][x] = '0';
	map->map[map->player.cord.y][map->player.cord.x] = 'P';
	merge_images(&map->tex.composite, &map->tex.grass, SCALE * x, SCALE * y, 0xFF000000);
	printf("Number of moves => %d\n", i++);
}

void	animate_open_exit(t_map *map)
{
	static int	count = 0;
	static int flag = 0;
	if (!flag && count % map->rate == 0)
	{
		merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->exit.cord.x, SCALE * map->exit.cord.y, 0xFF000000);
		merge_player_images(map, &map->tex.composite, &map->tex.exit, SCALE * map->exit.cord.x, SCALE * map->exit.cord.y, map->i_exit);
		map->i_exit++;
		if (map->i_exit == 6)
		{
			flag = 1;
			return ;
		}
	}
	count++;
}

void	check_exit(t_map *map, int x, int y)
{	
	if (map->player.move == 'D' && map->map[y + 1][x] == 'E' && !map->nmb_coins)
		exit(0);
	else if (map->player.move == 'U' && map->map[y - 1][x] == 'E' && !map->nmb_coins)
		exit(0);
	else if (map->player.move == 'L' && map->map[y][x - 1] == 'E' && !map->nmb_coins)
		exit(0);
	else if (map->player.move == 'R' && map->map[y][x + 1] == 'E' && !map->nmb_coins)
		exit(0);
}

void	check_coin(t_map *map, int x, int y)
{
	int i = 0;
	while (i < map->items)
	{
		if (map->player.move == 'D' && map->coin[i].cord.x == x && map->coin[i].cord.y == y + 1 && map->coin[i].is_there)
		{
			map->coin[i].is_there = false;
			map->nmb_coins--;
			break;
		}
		else if (map->player.move == 'U' && map->coin[i].cord.x == x && map->coin[i].cord.y == y - 1 && map->coin[i].is_there)
		{
			map->coin[i].is_there = false;
			map->nmb_coins--;
			break;
		}
		else if (map->player.move == 'L' && map->coin[i].cord.x == x - 1 && map->coin[i].cord.y == y && map->coin[i].is_there)
		{
			map->coin[i].is_there = false;
			map->nmb_coins--;
			break;
		}
		else if (map->player.move == 'R' && map->coin[i].cord.x == x + 1 && map->coin[i].cord.y == y && map->coin[i].is_there)
		{
			map->coin[i].is_there = false;
			map->nmb_coins--;
			break;
		}
		i++;
	}
}

void	move_enemy(t_enemy *enemy)
{
	if (enemy->move == 'L')
		enemy->cord.x--;
	else if (enemy->move == 'R')
		enemy->cord.x++;
	else if (enemy->move == 'U')
		enemy->cord.y--;
	else if (enemy->move == 'D')
		enemy->cord.y++;
	else
		enemy->move = 'I';
}

double	get_distance(t_cord cord_p, t_cord cord_e)
{
	double distance = sqrt(pow((cord_p.x - cord_e.x), 2) + pow((cord_p.y - cord_e.y), 2)); // distance between player and enemy
	return (distance);
}

char	get_random_move()
{
	static char	moves[] = {'U', 'D', 'L', 'R'};
	return (moves[rand() % 4]);
}

char get_best_move(t_map *map, int i, int offset)
{
	double act_distance = get_distance(map->player.cord, map->enemy[i].cord) + offset;
	if (act_distance > get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x - 1, map->enemy[i].cord.y}) 
	&& is_valid_move_enemy(map, 0, -1, i))
		return ('L');
	else if (act_distance > get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x + 1, map->enemy[i].cord.y})
	&& is_valid_move_enemy(map, 0, 1, i))
		return ('R');
	else if (act_distance > get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x, map->enemy[i].cord.y - 1})
	&& is_valid_move_enemy(map, -1, 0, i))
		return ('U');
	else if (act_distance > get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x, map->enemy[i].cord.y + 1})
	&& is_valid_move_enemy(map, 1, 0, i))
		return ('D');
	get_best_move(map, i, offset + 1);
	return (get_random_move());
}

void	animate_enemy(t_map *map, int i)
{
	int y = map->enemy[i].cord.y;
	int	x = map->enemy[i].cord.x;
	
	if (map->enemy[i].count_enemy % 50 == 0)
	{
		map->enemy[i].i_enemy++;
		if (map->enemy[i].i_enemy == 1)
		{
			map->enemy[i].i_enemy = 0;
			map->enemy[i].count_enemy = 0;
		}
	}
	if (map->enemy[i].step_enemy >= SCALE)
	{	
		move_enemy(&map->enemy[i]);
		if (x != map->enemy[i].cord.x || y != map->enemy[i].cord.y)
			remove_grass(map, x, y, i);
		map->enemy[i].step_enemy = 0;
		//map->enemy[i].move = 'I';
		map->enemy[i].anim_enemy = false;
	}
	map->enemy[i].dellay_enemy += 1;
	if ((int)map->enemy[i].dellay_enemy % map->rate == 0)
	{
		merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, 0xFF000000);
		if (map->enemy[i].move == 'R')
			animate_move_enemy(map, &map->tex.enemy_right, 1, 0, i);
		else if (map->enemy[i].move == 'L')
			animate_move_enemy(map, &map->tex.enemy_left, -1, 0, i);
		else if (map->enemy[i].move == 'U')
			animate_move_enemy(map, &map->tex.enemy_up, 0, -1, i);
		else if (map->enemy[i].move == 'D')
			animate_move_enemy(map, &map->tex.enemy_down, 0, 1, i);
		else if (map->enemy[i].move == 'I')
		{
			clear_frame(&map->tex.frame_enemy[i], map);
			choose_frame(&map->tex.frame_enemy[i], &map->tex.enemy_idle, map->enemy[i].i_enemy);
			merge_enemy_images(map, &map->tex.frame_enemy[i], SCALE * map->enemy[i].cord.x, SCALE * map->enemy[i].cord.y, i);
		}
	}
	map->enemy[i].count_enemy++;
}

void	validate_move(t_map *map, int i)
{
	if (map->enemy[i].move == 'L' && is_valid_move_enemy(map, 0, -1, i))
		map->enemy[i].move = 'L';
	else if (map->enemy[i].move == 'U' && is_valid_move_enemy(map, -1, 0, i))
		map->enemy[i].move = 'U';
	else if (map->enemy[i].move == 'R' && is_valid_move_enemy(map, 0, 1, i))
		map->enemy[i].move = 'R';
	else if (map->enemy[i].move == 'D' && is_valid_move_enemy(map, 1, 0, i))
		map->enemy[i].move = 'D';
	else
		map->enemy[i].move = get_random_move();
}

void	enemy_loop(t_map *map)
{
	int i = 0;
	static int id = 0;
	srand(time(NULL) ^ (id * 12345));
	id++;
	while (i < map->skel)
	{
		if (map->enemy[i].is_there == true)
		{	
			if (get_distance(map->player.cord, map->enemy[i].cord) <= 5.0f && !map->enemy[i].anim_enemy)
			{
				map->enemy[i].move = get_best_move(map, i, 0);
				animate_enemy(map, i++);
				continue ;
			}
			else if (!map->enemy[i].anim_enemy)
				map->enemy[i].move = get_random_move();
			validate_move(map, i);
			animate_enemy(map, i);
		}
		i++;
	}
}

void	animate_player(t_map *map)
{
	int y = map->player.cord.y;
	int	x = map->player.cord.x;
	
	check_exit(map, x, y);
	check_coin(map, x, y);

	if (map->count_player % 50 == 0)
	{
		map->i_player++;
		if (map->i_player == 1)
		{
			map->i_player = 0;
			map->count_player = 0;
		}
	}
	if (map->step_player >= SCALE)
	{	
		moove_player(map);
		if (x != map->player.cord.x || y != map->player.cord.y)
			remove_coin(map, x, y);
		map->step_player = 0;
		map->player.move = 'I';
		map->anim_player = false;
	}
	map->dellay_player += 1;
	if ((int)map->dellay_player % map->rate == 0)
	{
		merge_images(&map->tex.composite, &map->tex.grass, SCALE * map->player.cord.x, SCALE * map->player.cord.y, 0xFF000000);
		if (map->player.move == 'R')
			animate_move(map, &map->tex.player_right, 1, 0);
		else if (map->player.move == 'L')
			animate_move(map, &map->tex.player_left, -1, 0);
		else if (map->player.move == 'U')
			animate_move(map, &map->tex.player_up, 0, -1);
		else if (map->player.move == 'D')
			animate_move(map, &map->tex.player_down, 0, 1);
		else if (map->player.move == 'I')
		{
			clear_frame(&map->tex.frame_player, map);
			choose_frame(&map->tex.frame_player, &map->tex.player_idle, map->i_player);
			merge_player_images(map, &map->tex.composite, &map->tex.frame_player, SCALE * map->player.cord.x, SCALE * map->player.cord.y);
		}
	}
	map->count_player++;
}

int game_loop(t_map *map)
{
	animate_player(map);
	animate_coin(map);
	enemy_loop(map);
	if (map->nmb_coins == 0)
		animate_open_exit(map);
	mlx_put_image_to_window(map->mlx, map->win, map->tex.composite.img, 0, 0);
	mlx_string_put(map->mlx, map->win, 10, 10, 0xFF0000, "zakaria howa li kayn");
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
    map->tex.enemy_right.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_walk_right.xpm", &map->tex.enemy_right.width, &map->tex.enemy_right.height);
    map->tex.enemy_right.addr = mlx_get_data_addr(map->tex.enemy_right.img, &map->tex.enemy_right.bpp, &map->tex.enemy_right.line_length, &map->tex.enemy_right.endian);
    map->tex.enemy_left.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_walk_left.xpm", &map->tex.enemy_left.width, &map->tex.enemy_left.height);
    map->tex.enemy_left.addr = mlx_get_data_addr(map->tex.enemy_left.img, &map->tex.enemy_left.bpp, &map->tex.enemy_left.line_length, &map->tex.enemy_left.endian);
    map->tex.enemy_up.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_walk_up.xpm", &map->tex.enemy_up.width, &map->tex.enemy_up.height);
    map->tex.enemy_up.addr = mlx_get_data_addr(map->tex.enemy_up.img, &map->tex.enemy_up.bpp, &map->tex.enemy_up.line_length, &map->tex.enemy_up.endian);
    map->tex.enemy_down.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_walk_down.xpm", &map->tex.enemy_down.width, &map->tex.enemy_down.height);
    map->tex.enemy_down.addr = mlx_get_data_addr(map->tex.enemy_down.img, &map->tex.enemy_down.bpp, &map->tex.enemy_down.line_length, &map->tex.enemy_down.endian);
    map->tex.enemy_idle.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Skel_idle_down.xpm", &map->tex.enemy_idle.width, &map->tex.enemy_idle.height);
    map->tex.enemy_idle.addr = mlx_get_data_addr(map->tex.enemy_idle.img, &map->tex.enemy_idle.bpp, &map->tex.enemy_idle.line_length, &map->tex.enemy_idle.endian);
}

int	ft_exit(int i)
{
	exit(i);
	return (0);
}

int rendring(t_map *map) 
{	
    map->mlx = mlx_init();
	if (!map || !map->map || !*(map->map))
		return (-1);
	int x = SCALE * map->cord.height;
	int	y = SCALE * map->cord.witdh;
	int i = 0;
	while (i < map->skel)
	{
		map->enemy[i].count_enemy = 0;
		map->enemy[i].dellay_enemy = 0;
		map->enemy[i].step_enemy = 0;
		map->enemy[i].frame_nmb_enemy = 0;
		map->enemy[i].i_enemy = 0;
		map->enemy[i].anim_enemy = false;
		map->tex.frame_enemy[i].img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/grass.xpm", &map->tex.frame_enemy[i].width, &map->tex.frame_enemy[i].height);
		map->tex.frame_enemy[i].addr = mlx_get_data_addr(map->tex.frame_enemy[i].img, &map->tex.frame_enemy[i].bpp, &map->tex.frame_enemy[i].line_length, &map->tex.frame_enemy[i].endian);
		i++;
	}
	map->count_player = 0;
	map->dellay_player = 0;
	map->frame_nmb_player = 0;
	map->step_player = 0;
	map->player.move = 'I';
	map->i_exit = 0;
	map->exit_flag = 0;
	map->nmb_coins = map->items;
	int size = (map->cord.height * map->cord.witdh);
 	map->rate = 24000 / size;
	map->tex.frame_player.img = mlx_xpm_file_to_image(map->mlx, "../textures/Adventure/grass.xpm", &map->tex.frame_player.width, &map->tex.frame_player.height);
    map->tex.frame_player.addr = mlx_get_data_addr(map->tex.frame_player.img, &map->tex.frame_player.bpp, &map->tex.frame_player.line_length, &map->tex.frame_player.endian);
	map->tex.coin_.img = mlx_xpm_file_to_image(map->mlx, "../textures/coin.xpm", &map->tex.coin_.width, &map->tex.coin_.height);
    map->tex.coin_.addr = mlx_get_data_addr(map->tex.coin_.img, &map->tex.coin_.bpp, &map->tex.coin_.line_length, &map->tex.coin_.endian);
    map->win = mlx_new_window(map->mlx, y, x, "so_long");
    map->tex.exit.img = mlx_xpm_file_to_image(map->mlx, "../textures/ass/Chest.xpm", &map->tex.exit.width, &map->tex.exit.height);
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
	mlx_hook(map->win, 2, 1L<<0, key_press, map);
	mlx_hook(map->win, 17, 0, ft_exit, 0); 
	mlx_loop_hook(map->mlx, game_loop, map);
    mlx_loop(map->mlx);
    return 0;
}
