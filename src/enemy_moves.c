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
#include <time.h>


char	get_random_move(void)
{
	static char	moves[] = {'U', 'D', 'L', 'R'};
	return (moves[rand() % 4]);
}

void	enemy_moves(t_map *map)
{
	int i = 0;

	srand(time(NULL));
	while (i < map->skel)
	{
		map->enemy[i].move = get_random_move();
		move_enemy(map, &map->enemy[i]);
		i++;
	}
}

