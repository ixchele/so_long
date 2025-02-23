/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions_t.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:53:27 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/12 22:38:06 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

void	remove_grass(t_map *map, int x, int y, int i)
{
	check_enemy(map);
	map->map[y][x] = '0';
	map->map[map->enemy[i].cord.y][map->enemy[i].cord.x] = 'X';
	merge_images(&map->tex.composite, &map->tex.grass,
		(t_cord){SCALE * x, SCALE * y, 0, 0});
}

void	remove_coin(t_map *map, int x, int y)
{
	check_enemy(map);
	map->map[y][x] = '0';
	map->map[map->player.cord.y][map->player.cord.x] = 'P';
	merge_images(&map->tex.composite, &map->tex.grass,
		(t_cord){SCALE * x, SCALE * y, 0, 0});
	ft_printf("Number of moves => %d\n", 1 + map->nmb_steps_player++);
}
