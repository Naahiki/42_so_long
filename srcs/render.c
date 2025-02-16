#include "so_long.h"

void render_map(t_game *game) {
    int x, y;

    for (y = 0; game->map[y]; y++) {
        for (x = 0; game->map[y][x]; x++) {
            // Dibujar el fondo siempre primero
            mlx_put_image_to_window(game->mlx, game->win, game->floor, x * 64, y * 64);

            // Dibujar el sprite según el contenido del mapa
            if (game->map[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->wall, x * 64, y * 64);
            else if (game->map[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->player, x * 64, y * 64);
            else if (game->map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->collectible, x * 64, y * 64);
            else if (game->map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->exit, x * 64, y * 64);
        }
    }
}