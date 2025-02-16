#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"
# include <string.h>
# include <stdbool.h>

// Estructura para el juego
typedef struct s_game {
    void *mlx;
    void *win;
    void *player;
    void *wall;
    void *floor;
    void *collectible;
    void *exit;
    char **map;
    int player_x;
    int player_y;
    int moves;
    int coins;
} t_game;

// Estructura para posiciones en el mapa
typedef struct {
    int x;
    int y;
} Position;

// Funciones de validación y manejo del mapa
void error_exit(char *message);
char **read_map(char *file);
void print_map(char **map);
void validate_map(char **map);
void render_map(t_game *game);
void move_player(t_game *game, int x, int y);
int close_game(t_game *game);

// Funciones adicionales de validación del mapa
bool is_rectangular(char **map);
bool is_closed(char **map);
bool check_elements(char **map);

// Algoritmo Flood Fill y validaciones de camino
char **clone_map(char **map);
void flood_fill(char **map, int x, int y);
bool is_valid_path(char **map);
Position find_player(char **map);

#endif