/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 20:39:54 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/18 17:09:15 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"
#include <mlx.h>

void	ft_error(t_map *map, char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	ft_exit(map, 1);
}

int	main(int ac, char **av)
{
	t_map	map;

	ft_bzero(&map, sizeof(t_map));
	if (ac != 2)
		ft_error(&map, "Argument must be a single Map!");
	valid_file_name(&map, av[1]);
	read_(av[1], &map);
	if (!map.map)
		ft_error(&map, "Error Reading Map!");
	is_valid(&map);
	ft_printf("Map is Valid! Starting Game...\n");
	rendring(&map);
}
