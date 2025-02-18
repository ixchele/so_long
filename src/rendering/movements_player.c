/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:29:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/13 14:05:03 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

bool	is_valid_move_player(t_map *map, int n, int z)
{
	map->anim_player = true;
	if (map->map[map->player.cord.y + n][map->player.cord.x + z] != '1'
		&& map->map[map->player.cord.y + n][map->player.cord.x + z] != 'E')
		return (true);
	if (map->map[map->player.cord.y + n][map->player.cord.x + z] == 'E'
		&& !map->nmb_coins)
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
		ft_exit(map, 0);
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
	double	distance;

	distance = sqrt(pow((cord_p.x - cord_e.x), 2) + pow((cord_p.y
					- cord_e.y), 2));
	return (distance);
}
