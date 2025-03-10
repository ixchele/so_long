/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_lose.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:13:00 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/23 16:33:39 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

int	you_lose(t_map *map)
{
	static int	i = 1;

	i++;
	if (i % 30000 == 0)
		ft_exit(map, 0);
	mlx_put_image_to_window(map->mlx, map->win, map->tex.lose.img,
		(map->cord.witdh - 5) * SCALE / 2, (map->cord.height - 3) * SCALE / 2);
	return (1);
}

int	you_win(t_map *map)
{
	static int	i = 1;

	i++;
	if (i % 30000 == 0)
		ft_exit(map, 0);
	mlx_put_image_to_window(map->mlx, map->win, map->tex.win.img,
		(map->cord.witdh - 5) * SCALE / 2, (map->cord.height - 3) * SCALE / 2);
	return (1);
}

void	lose_loop(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	ft_printf("You Lost! You were killed by a Skeleton!\n");
	mlx_hook(map->win, 2, 1L << 0, key_press, map);
	mlx_hook(map->win, 17, 0, mlx_exit, map);
	mlx_loop_hook(map->mlx, you_lose, map);
	mlx_loop(map->mlx);
}

void	win_loop(t_map *map)
{
	mlx_clear_window(map->mlx, map->win);
	ft_printf("You Won! You have reached the Exit!\n");
	mlx_hook(map->win, 2, 1L << 0, key_press, map);
	mlx_hook(map->win, 17, 0, mlx_exit, map);
	mlx_loop_hook(map->mlx, you_win, map);
	mlx_loop(map->mlx);
}
