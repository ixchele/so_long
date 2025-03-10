/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_enemy_ran.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:36:56 by zbengued          #+#    #+#             */
/*   Updated: 2025/03/04 03:54:11 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

char	get_random_move(void)
{
	static char	moves[] = {'U', 'D', 'L', 'R'};

	return (moves[rand() % 4]);
}
