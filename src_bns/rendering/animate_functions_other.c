/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate_functions_other.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:51:41 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/12 22:29:36 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

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

void	animate_open_exit(t_map *map)
{
	static int	count = 0;
	static int	flag = 0;

	if (!flag && count % map->rate == 0)
	{
		merge_images(&map->tex.composite, &map->tex.grass, (t_cord){SCALE
			* map->exit.cord.x, SCALE * map->exit.cord.y, 0, 0});
		merge_exit_images(map, &map->tex.composite, &map->tex.exit,
			(t_cord){SCALE * map->exit.cord.x, SCALE * map->exit.cord.y, 0,
			0});
		map->i_exit++;
		if (map->i_exit == 6)
		{
			flag = 1;
			return ;
		}
	}
	count++;
}
