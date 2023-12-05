#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int topDist = __INT_MAX__;

void assign(int* a, int* b){
    *b = *a;
}

void fastestPath(int orIndex, int destIndex, int cities, int plength, int pindex, int fastpath[cities], int currpath[cities]){
    
}

int main() {
    int N; // Cantidad de ciudades total
    int i, j; // Para iteraciones
    int num; // Valor ingresado por usuario
    int originIndex, destinyIndex; // Indice del destino y el origen
    char destiny, origin; // Punto inicial y final
    printf("Ingrese la cantidad de ciudades: \n");
    scanf("%d", &N);
    int dists[N][N]; // Matriz de distancias
    int fastPath[N];
    int currPath[N];
    // Asignar la diagonal de 0s
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i==j){
                dists[i][j] = 0;
            }
        }
    }
    printf("Ingrese distancias. Debe poner -1 si no hay conexion.\n");
    // Asignar y reflejar valores de la matriz
    for (i = 0; i < N; i++) {
        for (j = i+1; j < N; j++) {
            printf("Distancia %c => %c: ", 'A' + i, 'A' + j);
            scanf("%d", &num);
            assign(&num, &dists[i][j]);
            assign(&num, &dists[j][i]); // Reflejar el valor ingresado
            }
            
        }

    printf("\n\nMatriz de distancias resultantes:\n");
    printf(" ");
    // Imprimir matriz de distancias
    for (int j = 0; j < N; j++) {
        printf("%3c", 'A' + j);
    }

    printf("\n");

    for (i = 0; i < N; i++) {
        printf("%c", 'A'+i);
        for (j = 0; j<N; j++){
            if (dists[i][j] == 0){
                printf("  -");
            }
            else{
                printf("%3d", dists[i][j]);
            }
        }
        printf("\n");
    }

    printf("Ingrese su ciudad de origen: \n");
    scanf("%s", &origin);

    printf("Ingrese su ciudad de destino: \n");
    scanf("%s", &destiny);

    originIndex = origin - 'A'; // Indice numerico de la ciudad de origen
    if (originIndex > N-1){ // Caso de error
        printf("ERROR. Ciudad origen fuera del rango."); 
        exit(1);
    }
    destinyIndex = destiny - 'A'; // Indice numerico de la ciudad destino
    if (destinyIndex > N-1){ // Caso de error
        printf("ERROR. Ciudad destino fuera del rango.");
        exit(1);
    }
    fastestPath(originIndex, destinyIndex, N, 0, 0, fastPath, currPath);
    return 0;
}
