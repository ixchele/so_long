/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_xpm_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:30:23 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/13 18:37:19 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	load_xpm_addrs_player(t_map *map)
{
	map->tex.p_r.addr = mlx_get_data_addr(map->tex.p_r.img,
			&map->tex.p_r.bpp, &map->tex.p_r.line_length,
			&map->tex.p_r.endian);
	map->tex.p_l.addr = mlx_get_data_addr(map->tex.p_l.img,
			&map->tex.p_l.bpp, &map->tex.p_l.line_length,
			&map->tex.p_l.endian);
	map->tex.p_u.addr = mlx_get_data_addr(map->tex.p_u.img,
			&map->tex.p_u.bpp, &map->tex.p_u.line_length,
			&map->tex.p_u.endian);
	map->tex.p_d.addr = mlx_get_data_addr(map->tex.p_d.img,
			&map->tex.p_d.bpp, &map->tex.p_d.line_length,
			&map->tex.p_d.endian);
	map->tex.p_i.addr = mlx_get_data_addr(map->tex.p_i.img,
			&map->tex.p_i.bpp, &map->tex.p_i.line_length,
			&map->tex.p_i.endian);
}

void	load_xpm_addrs_enemy(t_map *map)
{
	map->tex.e_r.addr = mlx_get_data_addr(map->tex.e_r.img,
			&map->tex.e_r.bpp, &map->tex.e_r.line_length,
			&map->tex.e_r.endian);
	map->tex.e_l.addr = mlx_get_data_addr(map->tex.e_l.img,
			&map->tex.e_l.bpp, &map->tex.e_l.line_length,
			&map->tex.e_l.endian);
	map->tex.e_u.addr = mlx_get_data_addr(map->tex.e_u.img,
			&map->tex.e_u.bpp, &map->tex.e_u.line_length,
			&map->tex.e_u.endian);
	map->tex.e_d.addr = mlx_get_data_addr(map->tex.e_d.img,
			&map->tex.e_d.bpp, &map->tex.e_d.line_length,
			&map->tex.e_d.endian);
	map->tex.e_i.addr = mlx_get_data_addr(map->tex.e_i.img,
			&map->tex.e_i.bpp, &map->tex.e_i.line_length,
			&map->tex.e_i.endian);
}

void	load_xpm_addrs_coin(t_map *map)
{
	map->tex.coin[0].addr = mlx_get_data_addr(map->tex.coin[0].img,
			&map->tex.coin[0].bpp, &map->tex.coin[0].line_length,
			&map->tex.coin[0].endian);
	map->tex.coin[1].addr = mlx_get_data_addr(map->tex.coin[1].img,
			&map->tex.coin[1].bpp, &map->tex.coin[1].line_length,
			&map->tex.coin[1].endian);
	map->tex.coin[2].addr = mlx_get_data_addr(map->tex.coin[2].img,
			&map->tex.coin[2].bpp, &map->tex.coin[2].line_length,
			&map->tex.coin[2].endian);
	map->tex.coin[3].addr = mlx_get_data_addr(map->tex.coin[3].img,
			&map->tex.coin[3].bpp, &map->tex.coin[3].line_length,
			&map->tex.coin[3].endian);
	map->tex.coin[4].addr = mlx_get_data_addr(map->tex.coin[4].img,
			&map->tex.coin[4].bpp, &map->tex.coin[4].line_length,
			&map->tex.coin[4].endian);
	map->tex.coin[5].addr = mlx_get_data_addr(map->tex.coin[5].img,
			&map->tex.coin[5].bpp, &map->tex.coin[5].line_length,
			&map->tex.coin[5].endian);
}

void	load_xpm_addrs_other(t_map *map)
{
	map->tex.frame_player.addr = mlx_get_data_addr(map->tex.frame_player.img,
			&map->tex.frame_player.bpp, &map->tex.frame_player.line_length,
			&map->tex.frame_player.endian);
	map->tex.coin_.addr = mlx_get_data_addr(map->tex.coin_.img,
			&map->tex.coin_.bpp, &map->tex.coin_.line_length,
			&map->tex.coin_.endian);
	map->tex.exit.addr = mlx_get_data_addr(map->tex.exit.img,
			&map->tex.exit.bpp, &map->tex.exit.line_length,
			&map->tex.exit.endian);
	map->tex.wall.addr = mlx_get_data_addr(map->tex.wall.img,
			&map->tex.wall.bpp, &map->tex.wall.line_length,
			&map->tex.wall.endian);
	map->tex.grass.addr = mlx_get_data_addr(map->tex.grass.img,
			&map->tex.grass.bpp, &map->tex.grass.line_length,
			&map->tex.grass.endian);
	map->tex.win.addr = mlx_get_data_addr(map->tex.win.img,
			&map->tex.win.bpp, &map->tex.win.line_length,
			&map->tex.win.endian);
	map->tex.lose.addr = mlx_get_data_addr(map->tex.lose.img,
			&map->tex.lose.bpp, &map->tex.lose.line_length,
			&map->tex.lose.endian);
}

void	init_all_xpms_adds(t_map *map)
{
	load_xpm_addrs_player(map);
	load_xpm_addrs_enemy(map);
	load_xpm_addrs_coin(map);
	load_xpm_addrs_other(map);
	if (!map->tex.p_r.addr || !map->tex.p_l.addr || !map->tex.p_u.addr
		|| !map->tex.p_d.addr || !map->tex.p_i.addr
		|| !map->tex.e_r.addr || !map->tex.e_l.addr || !map->tex.e_u.addr
		|| !map->tex.e_d.addr || !map->tex.e_i.addr
		|| !map->tex.coin[0].addr || !map->tex.coin[1].addr
		|| !map->tex.coin[2].addr || !map->tex.coin[3].addr
		|| !map->tex.coin[4].addr || !map->tex.coin[5].addr
		|| !map->tex.frame_player.addr || !map->tex.coin_.addr
		|| !map->tex.exit.addr || !map->tex.wall.addr
		|| !map->tex.grass.addr || !map->tex.win.addr
		|| !map->tex.lose.addr)
		ft_error(map, "Failed to Load XPM Addresses");
}
