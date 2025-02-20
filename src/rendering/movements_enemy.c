/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_enemy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:47:14 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/13 13:57:50 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static bool	no_collision(t_map *map, t_cord cord)
{
	int (i) = 0;
	if (map->map[cord.y - 1][cord.x] == 'X')
		i++;
	if (map->map[cord.y + 1][cord.x] == 'X')
		i++;
	if (map->map[cord.y][cord.x - 1] == 'X')
		i++;
	if (map->map[cord.y][cord.x + 1] == 'X')
		i++;
	if (i > 1)
		return (false);
	return (true);
}

bool	is_valid_move_enemy(t_map *map, int n, int z, int i)
{
	map->enemy[i].anim_enemy = true;
	if (map->map[map->enemy[i].cord.y + n][map->enemy[i].cord.x + z] != '1'
		&& map->map[map->enemy[i].cord.y + n][map->enemy[i].cord.x + z] != 'E'
		&& map->map[map->enemy[i].cord.y + n][map->enemy[i].cord.x + z] != 'X'
		&& no_collision(map, (t_cord){map->enemy[i].cord.x + z,
			map->enemy[i].cord.y + n, 0, 0})
		&& map->map[map->enemy[i].cord.y + n][map->enemy[i].cord.x + z] != 'C')
		return (true);
	map->enemy[i].anim_enemy = false;
	return (false);
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
}

char	get_best_move(t_map *map, int i, int offset)
{
	double	act_distance;

	act_distance = get_distance(map->player.cord, map->enemy[i].cord) + offset;
	if (act_distance > get_distance(map->player.cord,
			(t_cord){map->enemy[i].cord.x - 1, map->enemy[i].cord.y, 0, 0})
		&& is_valid_move_enemy(map, 0, -1, i))
		return ('L');
	else if (act_distance > get_distance(map->player.cord,
			(t_cord){map->enemy[i].cord.x + 1, map->enemy[i].cord.y, 0, 0})
		&& is_valid_move_enemy(map, 0, 1, i))
		return ('R');
	else if (act_distance > get_distance(map->player.cord,
			(t_cord){map->enemy[i].cord.x, map->enemy[i].cord.y - 1, 0, 0})
		&& is_valid_move_enemy(map, -1, 0, i))
		return ('U');
	else if (act_distance > get_distance(map->player.cord,
			(t_cord){map->enemy[i].cord.x, map->enemy[i].cord.y + 1, 0, 0})
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
		map->enemy[i].move = 'I';
}
