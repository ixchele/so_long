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

int to_screen_x(double x, t_data *img) {
    return (int)(x * img->scale_x + img->offset_x);
}

int to_screen_y(double y, t_data *img) {
    return (int)(img->offset_y - y * img->scale_y);
}

void draw_function(t_data *img, double (*f)(double), double x_min, double x_max, int color) {
    double step = 0.01; // Précision du tracé
    double x = x_min;

    while (x < x_max) {
        double y1 = f(x);
        double y2 = f(x + step);

        int x1_pix = to_screen_x(x, img);
        int y1_pix = to_screen_y(y1, img);
        int x2_pix = to_screen_x(x + step, img);
        int y2_pix = to_screen_y(y2, img);
        mlx_pixel_put(img->mlx_ptr, img->win_ptr, x1_pix, y1_pix, color);
        mlx_pixel_put(img->mlx_ptr, img->win_ptr, x2_pix, y2_pix, color);
        x += step;
    }
}

double parabola(double x) {
    return sqrt(2 - x * x);
}

// Exemple de fonction mathématique : sinus
// double sine(double x) {
//     return sin(x);
// }

int main() {
    t_data img;

    img.mlx_ptr = mlx_init();
    img.width = 800;
    img.height = 600;
    img.win_ptr = mlx_new_window(img.mlx_ptr, img.width, img.height, "Draw Function");

    img.scale_x = 600;  // Pixels par unité sur l'axe X
    img.scale_y = 600;  // Pixels par unité sur l'axe Y
    img.offset_x = img.width / 2;  // Décalage pour centrer l'origine en X
    img.offset_y = img.height / 2; // Décalage pour centrer l'origine en Y

    draw_function(&img, parabola, -4, 4, 0xFF0000); // Parabole en rouge

    mlx_loop(img.mlx_ptr); // Boucle pour garder la fenêtre ouverte
    return 0;
}
