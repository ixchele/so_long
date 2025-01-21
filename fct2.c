
#include <mlx.h>
#include <math.h>
#include <stdlib.h>

typedef struct s_data {
    void    *mlx_ptr;
    void    *win_ptr;
    int     width;
    int     height;
    double  scale_x;
    double  scale_y;
    double  offset_x;
    double  offset_y;
} t_data;

double to_cartesian_x(int x_pix, t_data *img) 
{
    return (x_pix - img->offset_x) / img->scale_x;
}

double to_cartesian_y(int y_pix, t_data *img) 
{
    return (img->offset_y - y_pix) / img->scale_y;
}

double implicit_equation(double x, double y) 
{
    return pow(x * x + y * y - 1, 3) - x * x * pow(y, 3);
}

void draw_implicit(t_data *img, double tolerance, int color) 
{
	int x_pix = 0;
    while (x_pix < img->width)
	{
		int y_pix = 0;
        while (y_pix < img->height) 
		{
            double x = to_cartesian_x(x_pix, img);
            double y = to_cartesian_y(y_pix, img);

            double result = implicit_equation(x, y);

            if (fabs(result) < tolerance)
                mlx_pixel_put(img->mlx_ptr, img->win_ptr, x_pix, y_pix, color);
			y_pix++;
        }
		x_pix++;
    }
}

int main() {
    t_data img;

    img.mlx_ptr = mlx_init();
    img.width = 800;
    img.height = 800;
    img.win_ptr = mlx_new_window(img.mlx_ptr, img.width, img.height, "Implicit Function");
    img.scale_x = 200;
    img.scale_y = 200;
    img.offset_x = img.width / 2;
    img.offset_y = img.height / 2;
    draw_implicit(&img, 0.01, 0xFF0000);
    mlx_loop(img.mlx_ptr);
    return 0;
}
