/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 15:17:10 by zbengued          #+#    #+#             */
/*   Updated: 2025/03/04 04:31:13 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	init_enemy(t_map *map)
{
	int (i) = 0;
	while (i < map->skel)
	{
		map->enemy[i].count_enemy = 0;
		map->enemy[i].dellay_enemy = 0;
		map->enemy[i].step_enemy = 0;
		map->enemy[i].frame_nmb_enemy = 0;
		map->enemy[i].i_enemy = 0;
		map->enemy[i].stuned = 0;
		map->enemy[i].anim_enemy = false;
		map->tex.frame_enemy[i].img = mlx_xpm_file_to_image(map->mlx,
				"Textures/tr_im.xpm",
				&map->tex.frame_enemy[i].width,
				&map->tex.frame_enemy[i].height);
		if (!map->tex.frame_enemy[i].img)
			ft_error(map, "Enemy Frame Failed");
		map->tex.frame_enemy[i].addr = mlx_get_data_addr(
				map->tex.frame_enemy[i].img,
				&map->tex.frame_enemy[i].bpp,
				&map->tex.frame_enemy[i].line_length,
				&map->tex.frame_enemy[i].endian);
		i++;
	}
}

void	init_struct(t_map *map)
{
	map->count_player = 0;
	map->dellay_player = 0;
	map->frame_nmb_player = 0;
	map->step_player = 0;
	map->player.move = 'I';
	map->i_exit = 0;
	map->exit_flag = 0;
	map->nmb_coins = map->items;
}

void	init_composit_image(t_map *map)
{
	fill_with_texture(&map->tex.composite, &map->tex.grass);
	draw_static_elements(map);
}
