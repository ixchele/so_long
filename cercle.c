#include <stdio.h>

// Fonction pour placer un pixel (remplace par ton implémentation graphique)
void putPixel(int x, int y) {
    printf("Pixel à (%d, %d)\n", x, y);
}

// Algorithme de tracé de cercle
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r; // Variable de décision

    // Trace les huit octants en symétrie
    while (y >= x) {
        // Tracer les 8 pixels de symétrie
        putPixel(xc + x, yc + y);
        putPixel(xc - x, yc + y);
        putPixel(xc + x, yc - y);
        putPixel(xc - x, yc - y);
        putPixel(xc + y, yc + x);
        putPixel(xc - y, yc + x);
        putPixel(xc + y, yc - x);
        putPixel(xc - y, yc - x);

        x++;

        // Vérifie la décision
        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }
}

int main() {
    int xc = 50, yc = 50, r = 10; // Centre et rayon du cercle
    drawCircle(xc, yc, r);

    return 0;
}
