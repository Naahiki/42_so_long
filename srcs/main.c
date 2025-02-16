#include "so_long.h"

int close_game(t_game *game) {
    mlx_destroy_window(game->mlx, game->win);
    exit(0); //Tengo que hacer free??
}

int key_hook(int keycode, t_game *game) {
    if (keycode == 53) // Tecla ESC
        close_game(game);

    // Movimientos con WASD
    else if (keycode == 13 || keycode == 126) // W o Flecha arriba
        move_player(game, 0, -1);
    else if (keycode == 1 || keycode == 125) // S o Flecha abajo
        move_player(game, 0, 1);
    else if (keycode == 0 || keycode == 123) // A o Flecha izquierda
        move_player(game, -1, 0);
    else if (keycode == 2 || keycode == 124) // D o Flecha derecha
        move_player(game, 1, 0);

    return (0);
}

int main(int argc, char **argv) {
    t_game game;

    if (argc != 2) {
        printf("Uso: ./so_long <mapa.ber>\n");
        return (1);
    }

    // Leer el mapa
    game.map = read_map(argv[1]);

    // Validar el mapa
    validate_map(game.map);

    // Inicializar contadores y posición del jugador
    game.moves = 0;
    game.coins = 0;

    for (int y = 0; game.map[y]; y++) {
        for (int x = 0; game.map[y][x]; x++) {
            if (game.map[y][x] == 'C') // Contar coins
                game.coins++;
            if (game.map[y][x] == 'P') { // Encontrar posición inicial del jugador
                game.player_x = x;
                game.player_y = y;
            }
        }
    }

    printf("Coins totales: %d\n", game.coins);

    // Calcular dimensiones del mapa
    int map_width = strlen(game.map[0]);
    int map_height = 0;
    while (game.map[map_height])
        map_height++;

    // Inicializar MiniLibX
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, map_width * 64, map_height * 64, "so_long");

    // Cargar texturas
    int width, height;
    game.wall = mlx_xpm_file_to_image(game.mlx, "textures/ice_rock.xpm", &width, &height);
    if (!game.wall)
        error_exit("No se pudo cargar la textura wall.xpm");
    game.floor = mlx_xpm_file_to_image(game.mlx, "textures/ice.xpm", &width, &height);
    if (!game.floor)
        error_exit("No se pudo cargar la textura floor.xpm");
    game.player = mlx_xpm_file_to_image(game.mlx, "textures/pengu.xpm", &width, &height);
    if (!game.player)
        error_exit("No se pudo cargar la textura player.xpm");
    game.collectible = mlx_xpm_file_to_image(game.mlx, "textures/coin.xpm", &width, &height);
    if (!game.collectible)
        error_exit("No se pudo cargar la textura collectible.xpm");
    game.exit = mlx_xpm_file_to_image(game.mlx, "textures/agujero.xpm", &width, &height);
    if (!game.exit)
        error_exit("No se pudo cargar la textura exit.xpm");

    // Renderizar el mapa inicial
    render_map(&game);

    // Hooks para manejar eventos
    mlx_hook(game.win, 2, 1L << 0, key_hook, &game); // Evento de teclado
    mlx_hook(game.win, 17, 1L << 17, close_game, &game); // Evento de cierre

    // Bucle principal de eventos
    mlx_loop(game.mlx);

    return (0);
}