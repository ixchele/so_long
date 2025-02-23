/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:59:16 by zbengued          #+#    #+#             */
/*   Updated: 2025/02/20 16:49:43 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	init_for_check(t_map *map, int *i)
{
	*i = 0;
	map->items = 0;
	map->skel = 0;
	map->is_there_exit = false;
	map->is_there_player = false;
}

static void	get_infos(t_map *map, int i, int j)
{
	if (map->map[i][j] == 'E' && map->is_there_exit == false)
		get_exit_inf(map, i, j);
	else if (map->map[i][j] == 'P' && map->is_there_player == false)
		get_player_inf(map, i, j);
	else if (map->map[i][j] == 'C')
		get_coin_inf(map, i, j);
	else if (map->map[i][j] != '1' && map->map[i][j] != '0')
		ft_error(map, "Invalid character in map");
}

bool	check_elements(t_map *map)
{
	int (i), (j);
	init_for_check(map, &i);
	map->coin = malloc(sizeof(t_coin));
	if (!map->coin)
		return (ft_error(map, "malloc failed"), false);
	map->enemy = malloc(sizeof(t_enemy));
	if (!map->enemy)
		return (ft_error(map, "malloc failed"), false);
	while (++i < map->cord.height)
	{
		j = 0;
		while (j < map->cord.witdh)
		{
			if (map->map[i][j] == 'E' && map->is_there_exit == true)
				return (ft_error(map, "There is more than 1 exit"), false);
			if (map->map[i][j] == 'P' && map->is_there_player == true)
				return (ft_error(map, "There is more than 1 player"), false);
			else
				get_infos(map, i, j);
			j++;
		}
	}
	return (map->items && map->is_there_player && map->is_there_exit);
}

bool	check_walls(t_map *map)
{
	int (i) = 0;
	while (i < map->cord.witdh)
	{
		if (map->map[0][i] != '1' || map->map[map->cord.height - 1][i] != '1')
			return (false);
		i++;
	}
	i = 1;
	while (i < map->cord.height)
	{
		if (map->map[i][0] != '1' || map->map[i][map->cord.witdh - 1] != '1')
			return (false);
		if (i == map->cord.height
			&& (int)ft_strlen(map->map[i]) != map->cord.witdh)
			return (false);
		if (i != map->cord.height
			&& (int)ft_strlen(map->map[i]) != map->cord.witdh)
			return (false);
		i++;
	}
	return (true);
}

char	*map_join(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ret;

	ret = NULL;
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	ret = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (ft_printf("Malloc Failed\n"), NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}
