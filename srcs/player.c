#include "so_long.h"

// Función para mover al jugador
void move_player(t_game *game, int x_offset, int y_offset) {
    int new_x = game->player_x + x_offset;
    int new_y = game->player_y + y_offset;

    // Evitar colisiones con muros
    if (game->map[new_y][new_x] == '1')
        return;

    // Recolectar coleccionables
    if (game->map[new_y][new_x] == 'C') {
        game->map[new_y][new_x] = '0';
        game->coins--;
        printf("Coleccionables restantes: %d\n", game->coins);
    }

    // Intentar acceder a la salida
    if (game->map[new_y][new_x] == 'E') {
        if (game->coins > 0) {
            printf("¡Todavía quedan coleccionables por recoger!\n");
            return; // No permitir el movimiento
        } else {
            printf("¡Has ganado en %d movimientos!\n", game->moves);
            close_game(game);
        }
    }

    // Actualizar posición del jugador
    game->map[game->player_y][game->player_x] = '0'; // Limpiar posición anterior
    game->map[new_y][new_x] = 'P'; // Nueva posición
    game->player_x = new_x;
    game->player_y = new_y;

    // Incrementar contador de movimientos
    game->moves++;
    printf("Movimientos: %d\n", game->moves);

    // Renderizar mapa actualizado
    render_map(game);
}