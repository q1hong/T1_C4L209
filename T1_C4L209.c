#include <stdio.h>
#include <stdlib.h>
#include <string.h> //

#define TAMANO_MAX 100

int maximo(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

int encontrar_diagonal_mas_larga(int **matriz, int tamano) {
    int max_longitud = 0;

    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            if (matriz[i][j] == 1) {
                int x = i;
                int y = j;
                int longitud = 0;

                while (x >= 0 && y < tamano && matriz[x][y] == 1) {
                    longitud++;
                    x--;
                    y++;
                }

                max_longitud = maximo(max_longitud, longitud);
            }
        }
    }

    return max_longitud;
}

int** leer_matriz(char *nombre_archivo, int *tamano) {
    FILE *archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    char buffer[TAMANO_MAX];
    int **matriz = (int **)malloc(TAMANO_MAX * sizeof(int *));
    int fila = 0;

    while (fgets(buffer, sizeof(buffer), archivo)) {
        matriz[fila] = (int *)malloc(TAMANO_MAX * sizeof(int));
        int columna = 0;
        char *token = strtok(buffer, " \n");

        while (token != NULL) {
            matriz[fila][columna] = atoi(token);
            columna++;
            token = strtok(NULL, " \n");
        }

        if (*tamano == 0) {
            *tamano = columna;
        }

        fila++;
    }

    fclose(archivo);
    return matriz;
}

void liberar_matriz(int **matriz, int tamano) {
    for (int i = 0; i < tamano; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <archivo_matriz.txt>\n", argv[0]);
        return 1;
    }

    int tamano = 0;
    int **matriz = leer_matriz(argv[1], &tamano);

    int resultado = encontrar_diagonal_mas_larga(matriz, tamano);

    printf("La secuencia de 1s más larga es: %d\n", resultado);

    liberar_matriz(matriz, tamano);

    return 0;
}
