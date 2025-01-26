/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbengued <zbengued@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 09:25:15 by zbengued          #+#    #+#             */
/*   Updated: 2025/01/21 11:54:16 by zbengued         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <mlx.h>
#include <stdio.h>

void	window_displayer(t_map *map)
{
    void *mlx;
    void *win;
    void *img;
	void *spr;
	int	z = 0;
    int width = 100 * map->witdh;
    int height = 100 * map->height;
    char *xpm_file = "../textures/Adventure/grass.xpm";
	char *sprite = "../textures/Adventure/player_0-31737359949.xpm";
	printf("-----w = %d, h = %d------\n", width, height);
    mlx = mlx_init();
    if (!mlx) 
	{
        fprintf(stderr, "Error: Failed to initialize MLX.\n");
        return ;
    }
    img = mlx_xpm_file_to_image(mlx, xpm_file, &z, &z);
    if (!img)
	{
        fprintf(stderr, "Error: Failed to load the XPM image.\n");
        return ;
    }
	spr = mlx_xpm_file_to_image(mlx, sprite, &z, &z);
    if (!spr)
	{
        fprintf(stderr, "Error: Failed to load the XPM image.\n");
        return ;
    }
    win = mlx_new_window(mlx, width, height, "XPM Image Example");
    if (!win) 
	{
        fprintf(stderr, "Error: Failed to create a window.\n");
        return ;
    }
    mlx_put_image_to_window(mlx, win, img, 0, 0);
	// mlx_put_image_to_window(mlx, win, spr, 0, 0);
    mlx_loop(mlx);

    return ;
}
