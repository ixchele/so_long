#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "get_next_line/get_next_line.h"

typedef struct s_map {
    char **map;
    int height;
} t_map;

char **read_map(char *file, t_map *map) {
    char *line;
    int i = 0;
    int fd;
    int capacity = 10;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return NULL;

    map->map = malloc(sizeof(char *) * capacity);
    if (!map->map) {
        close(fd);
        return NULL;
    }

    while ((line = get_next_line(fd))) {
        if (i >= capacity) {
            capacity *= 2;
            map->map = realloc(map->map, sizeof(char *) * capacity);
            if (!map->map) {
                close(fd);
                return NULL;
            }
        }
        map->map[i++] = line;
    }
    map->map[i] = NULL;
    map->height = i;

    // Réajustement pour la taille exacte
    map->map = realloc(map->map, sizeof(char *) * (i + 1));
    if (!map->map) {
        close(fd);
        return NULL;
    }

    close(fd);
    return map->map;
}

int main() {
    t_map map1;
    char **map1_ = read_map("~/Desktop/so_long/maps/map1.ber", &map1);

    // Affichage de la carte
    for (int i = 0; i < map1.height; i++) {
        for (int j = 0; map1_[i][j] != '\0'; j++) {
            printf("%c", map1_[i][j]);
        }
        printf("\n");
    }

    // Libération de la mémoire allouée
    for (int i = 0; i < map1.height; i++) {
        free(map1.map[i]);
    }
    free(map1.map);

    return 0;
}
