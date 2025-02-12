/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movments.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:29:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/11 16:05:25 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (act_distance > get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x - 1, map->enemy[i].cord.y, 0, 0}) 
	&& is_valid_move_enemy(map, 0, -1, i))
		return ('L');
	else if (act_distance > get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x + 1, map->enemy[i].cord.y, 0, 0})
	&& is_valid_move_enemy(map, 0, 1, i))
		return ('R');
	else if (act_distance > get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x, map->enemy[i].cord.y - 1, 0, 0})
	&& is_valid_move_enemy(map, -1, 0, i))
		return ('U');
	else if (act_distance > get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x, map->enemy[i].cord.y + 1, 0, 0})
	&& is_valid_move_enemy(map, 1, 0, i))
		return ('D');
	get_best_move(map, i, offset + 1);
	return (get_random_move());
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
