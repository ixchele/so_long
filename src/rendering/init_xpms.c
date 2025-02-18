/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:14:47 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/13 18:41:06 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	load_xpms_player(t_map *map)
{
	map->tex.p_r.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/P_R.xpm", &map->tex.p_r.width,
			&map->tex.p_r.height);
	map->tex.p_l.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/P_L.xpm", &map->tex.p_l.width,
			&map->tex.p_l.height);
	map->tex.p_u.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/P_U.xpm", &map->tex.p_u.width,
			&map->tex.p_u.height);
	map->tex.p_d.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/P_D.xpm", &map->tex.p_d.width,
			&map->tex.p_d.height);
}

void	load_xpms_enemy(t_map *map)
{
	map->tex.e_r.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/E_R.xpm", &map->tex.e_r.width,
			&map->tex.e_r.height);
	map->tex.e_l.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/E_L.xpm", &map->tex.e_l.width,
			&map->tex.e_l.height);
	map->tex.e_u.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/E_U.xpm", &map->tex.e_u.width,
			&map->tex.e_u.height);
	map->tex.e_d.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/E_D.xpm", &map->tex.e_d.width,
			&map->tex.e_d.height);
	map->tex.e_i.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/E_I.xpm", &map->tex.e_i.width,
			&map->tex.e_i.height);
}

void	load_xpms_coin(t_map *map)
{
	map->tex.coin[0].img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Coin_0.xpm", &map->tex.coin[0].width,
			&map->tex.coin[0].height);
	map->tex.coin[1].img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Coin_1.xpm", &map->tex.coin[1].width,
			&map->tex.coin[1].height);
	map->tex.coin[2].img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Coin_2.xpm", &map->tex.coin[2].width,
			&map->tex.coin[2].height);
	map->tex.coin[3].img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Coin_3.xpm", &map->tex.coin[3].width,
			&map->tex.coin[3].height);
	map->tex.coin[4].img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Coin_4.xpm", &map->tex.coin[4].width,
			&map->tex.coin[4].height);
	map->tex.coin[5].img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Coin_5.xpm", &map->tex.coin[5].width,
			&map->tex.coin[5].height);
}

void	load_xpms_other(t_map *map)
{
	map->tex.frame_player.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Grass.xpm", &map->tex.frame_player.width,
			&map->tex.frame_player.height);
	map->tex.coin_.img = mlx_xpm_file_to_image(map->mlx, "Textures/Coin.xpm",
			&map->tex.coin_.width, &map->tex.coin_.height);
	map->tex.exit.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Chest.xpm", &map->tex.exit.width,
			&map->tex.exit.height);
	map->tex.wall.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Wall.xpm", &map->tex.wall.width,
			&map->tex.wall.height);
	map->tex.grass.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/Grass.xpm", &map->tex.grass.width,
			&map->tex.grass.height);
	map->tex.p_i.img = mlx_xpm_file_to_image(map->mlx,
			"Textures/P_I.xpm", &map->tex.p_i.width,
			&map->tex.p_i.height);
}

void	init_all_xpms(t_map *map)
{
	load_xpms_player(map);
	load_xpms_enemy(map);
	load_xpms_coin(map);
	load_xpms_other(map);
	if (!map->tex.p_r.img || !map->tex.p_l.img || !map->tex.p_u.img
		|| !map->tex.p_d.img || !map->tex.p_i.img
		|| !map->tex.e_r.img || !map->tex.e_l.img || !map->tex.e_u.img
		|| !map->tex.e_d.img || !map->tex.e_i.img
		|| !map->tex.coin[0].img || !map->tex.coin[1].img
		|| !map->tex.coin[2].img || !map->tex.coin[3].img
		|| !map->tex.coin[4].img || !map->tex.coin[5].img
		|| !map->tex.frame_player.img || !map->tex.coin_.img
		|| !map->tex.exit.img || !map->tex.wall.img
		|| !map->tex.grass.img)
		ft_error(map, "Failed to Load XPMs");
}
