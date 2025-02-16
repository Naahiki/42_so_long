// #include "so_long.h"
// #include <string.h>
// #include "get_next_line.h"
// #include <stdbool.h>

// void error_exit(char *message) {
//     write(2, "Error\n", 6);
//     write(2, message, strlen(message));
//     exit(1);
// }
// char **read_map(char *file) {
//     int fd = open(file, O_RDONLY);
//     char *line;
//     char **map;
//     int i = 0;

//     if (fd < 0)
//         error_exit("No se puede abrir el archivo del mapa.");

//     map = malloc(sizeof(char *) * 100); // Reserva memoria para el mapa
//     if (!map)
//         error_exit("Error de memoria al leer el mapa.");

//     while ((line = get_next_line(fd))) {
//         if (line[strlen(line) - 1] == '\n')
//             line[strlen(line) - 1] = '\0';

//         printf("Línea leída: %s\n", line); // Imprime cada línea
//         map[i++] = strdup(line);
//         free(line);
//     }
//     map[i] = NULL; // Termina el mapa con NULL
//     close(fd);
//     return (map);
// }

// void print_map(char **map) {
//     int i = 0;

//     while (map[i]) {
//         printf("%s\n", map[i]); // Imprime cada línea seguida de un salto de línea
//         i++;
//     }
// }

// // Función para comprobar si el mapa es rectangular
// bool is_rectangular(char **map) {
//     size_t len = strlen(map[0]);
//     for (int i = 1; map[i]; i++) {
//         if (strlen(map[i]) != len)
//             return (false);
//     }
//     return (true);
// }

// // Función para comprobar si el mapa está cerrado por muros
// bool is_closed(char **map) {
//     int rows = 0;
//     int cols = strlen(map[0]);

//     while (map[rows])
//         rows++;

//     for (int i = 0; i < rows; i++) {
//         if (map[i][0] != '1' || map[i][cols - 1] != '1')
//             return (false);
//     }
//     for (int j = 0; j < cols; j++) {
//         if (map[0][j] != '1' || map[rows - 1][j] != '1')
//             return (false);
//     }
//     return (true);
// }

// // Función para comprobar los elementos del mapa
// bool check_elements(char **map) {
//     int player = 0, exit = 0, collectible = 0;

//     for (int i = 0; map[i]; i++) {
//         for (int j = 0; map[i][j]; j++) {
//             if (map[i][j] == 'P')
//                 player++;
//             else if (map[i][j] == 'E')
//                 exit++;
//             else if (map[i][j] == 'C')
//                 collectible++;
//             else if (map[i][j] != '1' && map[i][j] != '0') {
//                 printf("Carácter inválido encontrado: %c\n", map[i][j]);
//                 return (false); // Si encuentra un carácter no válido
//             }
//         }
//     }

//     // Imprimir para depuración
//     printf("P: %d, E: %d, C: %d\n", player, exit, collectible);

//     return (player >= 1 && exit >= 1 && collectible >= 1);
// }

// // Función principal de validación
// void validate_map(char **map) {
//     int player_count = 0;
//     int exit_count = 0;

//     for (int y = 0; map[y]; y++) {
//         for (int x = 0; map[y][x]; x++) {
//             if (map[y][x] == 'P')
//                 player_count++;
//             else if (map[y][x] == 'E')
//                 exit_count++;
//             else if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'C') {
//                 printf("Error: Carácter inválido en el mapa: %c\n", map[y][x]);
//                 exit(1);
//             }
//         }
//     }

//     if (player_count != 1) {
//         printf("Error: El mapa debe contener exactamente 1 posición inicial 'P'.\n");
//         exit(1);
//     }

//     if (exit_count != 1) {
//         printf("Error: El mapa debe contener exactamente 1 salida 'E'.\n");
//         exit(1);
//     }
// }


#include "so_long.h"
#include <string.h>
#include "get_next_line.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Función para manejar errores y salir del programa
void error_exit(char *message) {
    write(2, "Error\n", 6);
    write(2, message, strlen(message));
    exit(1);
}

// Función para leer el mapa desde un archivo
char **read_map(char *file) {
    int fd = open(file, O_RDONLY);
    char *line;
    char **map;
    int i = 0;

    if (fd < 0)
        error_exit("No se puede abrir el archivo del mapa.");

    map = malloc(sizeof(char *) * 100); // Reserva memoria para el mapa
    if (!map)
        error_exit("Error de memoria al leer el mapa.");

    while ((line = get_next_line(fd))) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        printf("Línea leída: %s\n", line); // Imprime cada línea
        map[i++] = strdup(line);
        free(line);
    }
    map[i] = NULL; // Termina el mapa con NULL
    close(fd);
    return (map);
}

// Función para imprimir el mapa (para depuración)
void print_map(char **map) {
    int i = 0;
    while (map[i]) {
        printf("%s\n", map[i]);
        i++;
    }
}

// Verifica si el mapa es rectangular
bool is_rectangular(char **map) {
    size_t len = strlen(map[0]);
    for (int i = 1; map[i]; i++) {
        if (strlen(map[i]) != len)
            return false;
    }
    return true;
}

// Verifica si el mapa está completamente rodeado de muros
bool is_closed(char **map) {
    int rows = 0;
    int cols = strlen(map[0]);

    while (map[rows])
        rows++;

    for (int i = 0; i < rows; i++) {
        if (map[i][0] != '1' || map[i][cols - 1] != '1')
            return false;
    }
    for (int j = 0; j < cols; j++) {
        if (map[0][j] != '1' || map[rows - 1][j] != '1')
            return false;
    }
    return true;
}

// Verifica la cantidad correcta de elementos en el mapa
bool check_elements(char **map) {
    int player = 0, exit = 0, collectible = 0;

    for (int i = 0; map[i]; i++) {
        for (int j = 0; map[i][j]; j++) {
            if (map[i][j] == 'P')
                player++;
            else if (map[i][j] == 'E')
                exit++;
            else if (map[i][j] == 'C')
                collectible++;
            else if (map[i][j] != '1' && map[i][j] != '0') {
                printf("Carácter inválido encontrado: %c\n", map[i][j]);
                return false;
            }
        }
    }

    printf("P: %d, E: %d, C: %d\n", player, exit, collectible);
    return (player == 1 && exit == 1 && collectible >= 1);
}


// Función para clonar el mapa (para evitar modificar el original)
char **clone_map(char **map) {
    int rows = 0;
    while (map[rows])
        rows++;

    char **copy = malloc((rows + 1) * sizeof(char *));
    if (!copy)
        return NULL;

    for (int i = 0; i < rows; i++) {
        copy[i] = strdup(map[i]);
    }
    copy[rows] = NULL;

    return copy;
}

// Algoritmo Flood Fill: Inundar el mapa desde la posición del jugador
void flood_fill(char **map, int x, int y) {
    if (map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'E')  
        return;  // No inundamos paredes ni la salida

    map[y][x] = 'F';  // Marcamos como visitado

    // Llamadas recursivas en las 4 direcciones
    flood_fill(map, x + 1, y);
    flood_fill(map, x - 1, y);
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
}


// Función para encontrar la posición del jugador
Position find_player(char **map) {
    Position pos = {-1, -1};  // Valor inválido por defecto
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++) {
            if (map[y][x] == 'P') {
                pos.x = x;
                pos.y = y;
                return pos;
            }
        }
    }
    return pos;
}

// Función para verificar si hay un camino válido
bool is_valid_path(char **map) {
    Position player = find_player(map);
    if (player.x == -1 || player.y == -1) {
        printf("Error: No se encontró la posición del jugador.\n");
        return false;
    }

    char **map_copy = clone_map(map);
    if (!map_copy) {
        printf("Error: No se pudo copiar el mapa.\n");
        return false;
    }

    // Aplicamos Flood Fill desde la posición del jugador
    flood_fill(map_copy, player.x, player.y);

    // Verificamos si la salida ('E') es alcanzable
    bool path_exists = false;
    bool all_coins_accessible = true; // Variable para verificar todas las monedas

    for (int y = 0; map_copy[y]; y++) {
        for (int x = 0; map_copy[y][x]; x++) {
            if (map[y][x] == 'E' && 
                (map_copy[y + 1][x] == 'F' || map_copy[y - 1][x] == 'F' ||
                 map_copy[y][x + 1] == 'F' || map_copy[y][x - 1] == 'F')) {
                path_exists = true;
            }

            // Verificamos si TODAS las monedas ('C') fueron alcanzadas
            if (map[y][x] == 'C' && map_copy[y][x] != 'F') {
                all_coins_accessible = false;
            }
        }
    }

    // Liberamos memoria del mapa copiado
    for (int i = 0; map_copy[i]; i++) {
        free(map_copy[i]);
    }
    free(map_copy);

    // Mensaje de error si alguna moneda no es accesible
    if (!all_coins_accessible) {
        printf("❌ Error: Hay monedas inaccesibles en el mapa.\n");
        return false;
    }

    if (!path_exists) {
        printf("❌ Error: No hay un camino válido del jugador a la salida.\n");
        return false;
    }

    printf("✅ Camino válido: Todas las monedas son accesibles y la salida también.\n");
    return true;
}

// Función principal de validación del mapa
void validate_map(char **map) {
    if (!is_rectangular(map)) {
        printf("Error: El mapa no es rectangular.\n");
        exit(1);
    }

    if (!is_closed(map)) {
        printf("Error: El mapa no está cerrado por muros.\n");
        exit(1);
    }

    if (!check_elements(map)) {
        printf("Error: El mapa no contiene los elementos requeridos.\n");
        exit(1);
    }

    if (!is_valid_path(map)) {
        //printf("Error: No hay un camino válido del jugador a la salida.\n");
        exit(1);
    }

    printf("✅ El mapa es válido y tiene un camino correcto.\n");
}