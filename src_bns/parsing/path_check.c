/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:26:34 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/18 13:31:45 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

void	valid_file_name(t_map *map, char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 1] != 'r' || file[i - 2] != 'e' || file[i - 3] != 'b'
		|| file[i - 4] != '.' || file[i - 5] == '/')
		ft_error(map, "Invalid File Name");
}
