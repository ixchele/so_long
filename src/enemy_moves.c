/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:58:55 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/06 06:17:27 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <math.h>

int	get_distance(t_cord cord_p, t_cord cord_e)
{
	int distance = sqrt(pow((cord_p.x - cord_e.x), 2) + pow((cord_p.y - cord_e.y), 2)); // distance between player and enemy
	return (distance);
}

char get_best_move(t_map *map, int i)
{
	int act_distance = get_distance(map->player.cord, map->enemy[i].cord);
	if (act_distance < get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x - 1, map->enemy[i].cord.y})
		&& is_valid_move_enemy(map, 0, -1, i))
		return ('L');
	else if (act_distance < get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x + 1, map->enemy[i].cord.y}))
		return ('R');
	else if (act_distance < get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x, map->enemy[i].cord.y - 1}))
		return ('U');
	else if (act_distance < get_distance(map->player.cord, (t_cord){map->enemy[i].cord.x, map->enemy[i].cord.y + 1}))
		return ('D');
	return ('I');
}
