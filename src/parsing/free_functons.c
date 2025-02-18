/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functons.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 17:07:25 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/18 17:08:21 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	safe_free(void *obj)
{
	if (!obj)
		return ;
	free(obj);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		safe_free(arr[i]);
		i++;
	}
	safe_free(arr);
}

void	safe_destroy(t_map *map, void *obj)
{
	if (!obj)
		return ;
	mlx_destroy_image(map->mlx, obj);
}

void	destroy_images(t_map *map)
{
	int	i;

	i = 0;
	safe_destroy(map, map->tex.p_r.img);
	safe_destroy(map, map->tex.p_l.img);
	safe_destroy(map, map->tex.p_u.img);
	safe_destroy(map, map->tex.p_d.img);
	safe_destroy(map, map->tex.p_i.img);
	safe_destroy(map, map->tex.e_r.img);
	safe_destroy(map, map->tex.e_l.img);
	safe_destroy(map, map->tex.e_u.img);
	safe_destroy(map, map->tex.e_d.img);
	safe_destroy(map, map->tex.e_i.img);
	safe_destroy(map, map->tex.wall.img);
	safe_destroy(map, map->tex.grass.img);
	safe_destroy(map, map->tex.composite.img);
	while (i < 6)
		safe_destroy(map, map->tex.coin[i++].img);
	i = 0;
	while (i <= map->skel)
		safe_destroy(map, map->tex.frame_enemy[i++].img);
	safe_destroy(map, map->tex.coin_.img);
	safe_destroy(map, map->tex.frame_player.img);
	safe_destroy(map, map->tex.exit.img);
}

void	ft_exit(t_map *map, int code)
{
	free_array(map->map);
	free_array(map->flood_map);
	destroy_images(map);
	if (map->win)
		mlx_destroy_window(map->mlx, map->win);
	if (map->mlx)
		mlx_destroy_display(map->mlx);
	safe_free(map->coin);
	safe_free(map->enemy);
	safe_free(map->mlx);
	free(map->nmb_of_steps);
	exit(code);
}
