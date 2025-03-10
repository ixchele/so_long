/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:00:37 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/14 20:00:43 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	get_player_inf(t_map *map, int i, int j)
{
	map->is_there_player = true;
	map->player.cord.x = j;
	map->player.cord.y = i;
}

void	get_exit_inf(t_map *map, int i, int j)
{
	map->is_there_exit = true;
	map->exit.cord.x = j;
	map->exit.cord.y = i;
}

void	get_coin_inf(t_map *map, int i, int j)
{
	t_coin	*tmp;

	tmp = ft_realloc(map->coin, sizeof(t_coin) * (map->items + 1));
	if (!tmp)
		ft_error(map, "Error\n Realloc Failed\n");
	map->coin = tmp;
	map->coin[map->items].cord.x = j;
	map->coin[map->items].cord.y = i;
	map->coin[map->items].is_there = true;
	map->coin[map->items].taken = false;
	map->coin[map->items].i_coin = 1;
	map->items++;
}

void	get_enemy_inf(t_map *map, int i, int j)
{
	t_enemy	*tmp;

	if (map->skel == 99)
		ft_error(map, "Too many enemies (Max enemies ; 98)");
	tmp = ft_realloc(map->enemy, sizeof(t_enemy) * (map->skel + 1));
	if (!tmp)
		ft_error(map, "Realloc Failed\n");
	map->enemy = tmp;
	map->enemy[map->skel].cord.x = j;
	map->enemy[map->skel].cord.y = i;
	map->enemy[map->skel].is_there = true;
	map->skel++;
}
