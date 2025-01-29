#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_image {
    void *img;
    char *addr;
    int bpp;
    int line_length;
    int endian;
    int width;
    int height;
} t_image;

void	fill_with_texture(t_image *composite, t_image *texture)
{
	int	y;
	int	x;
	int	tex_y;
	int	tex_x;
	unsigned int	color;
	char	*src_pixel;
	char	*dst_pixel;

	y = 0;
	while (y < composite->height)
	{
		x = 0;
		while (x < composite->width)
		{
			tex_x = x % texture->width;
			tex_y = y % texture->height;
			src_pixel = texture->addr + (tex_y * texture->line_length + tex_x * (texture->bpp / 8));
			color = *(unsigned int *)src_pixel;
			dst_pixel = composite->addr + (y * composite->line_length + x * (composite->bpp / 8));
			*(unsigned int *)dst_pixel = color;
			x++;
		}
		y++;
	}
}

int main() {
    void *mlx = mlx_init();
    int win_width = 800;
    int win_height = 600;
    void *win = mlx_new_window(mlx, win_width, win_height, "Remplir avec une texture (composite)");

    t_image texture;
    t_image composite;
    texture.img = mlx_xpm_file_to_image(mlx, "../textures/Adventure/grass.xpm", &texture.width, &texture.height);
    if (!texture.img)
	{
        printf("Erreur : Impossible de charger la texture.\n");
        return 1;
    }
    texture.addr = mlx_get_data_addr(texture.img, &texture.bpp, &texture.line_length, &texture.endian);
    composite.img = mlx_new_image(mlx, win_width, win_height);
    composite.addr = mlx_get_data_addr(composite.img, &composite.bpp, &composite.line_length, &composite.endian);
    composite.width = win_width;
    composite.height = win_height;
    fill_with_texture(&composite, &texture);
    mlx_put_image_to_window(mlx, win, composite.img, 0, 0);
    mlx_loop(mlx);
    return 0;
}
