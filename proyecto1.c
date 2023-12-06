#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void assign(int* a, int* b){
    *b = *a;
}

void swap(int *a, int *b){
    // Intercambiar valores
    int temp = *a;
    *a = *b;
    *b = temp;
}

int fact(int x){
    if(x == 0){
        return 1;
    } else{
        return x*fact(x-1);
    }
}

int perms(int cityIndexes[], int N, int index, int auxArray[], int * count){
    int i, j;
    if (index == N-1){
        for (i = 0; i < N; i++){
        assign(&cityIndexes[i], &auxArray[i + (*count)]);
        }
        (*count) += N;
    }
    for (i = index; i < N; i++){
        swap(&cityIndexes[index], &cityIndexes[i]);
        perms(cityIndexes, N, index + 1, auxArray, count);
        swap(&cityIndexes[index], &cityIndexes[i]);
    }
}

int main() {
    int N; // Cantidad de ciudades total
    int i, j, k, m, l; // Para iteraciones
    int num; // Valor ingresado por usuario
    int originIndex, destinyIndex; // Indice del destino y el origen
    int distToBeat; // DIstancia directa, se debe ser menor a eso
    int sum = 0;
    int count = 0;
    char destiny, origin; // Punto inicial y final
    printf("Ingrese la cantidad de ciudades: \n");
    scanf("%d", &N);
    int dists[N][N]; // Matriz de distancias
    int bestPath[N];
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
            printf("\n");
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

    printf("Ingrese su ciudad de origen: \n "); // Obtener la ciudad de origen
    scanf(" %c", &origin);
    printf("\n");
    printf("Ingrese su ciudad de destino: \n "); // Obtener la ciudad de destino
    scanf(" %c", &destiny);

    int cityIndexes[N]; // Array de posibles ciudades por letra
    for (i = 0; i < N; i++){
        cityIndexes[i] = i;
    }
    
    char cities[N]; // Ciudades en chars
    for (i = 0; i < N; i++){
        cities[i] = 'A' + i;
    }

    originIndex = origin - 'A'; // Indice numerico de la ciudad de origen
    if (originIndex > cityIndexes[N-1]){
        printf("ERROR, ciudad origen fuera de rango.");
    }
    destinyIndex = destiny - 'A'; // Indice numerico de la ciudad destino
    if (destinyIndex > cityIndexes[N-1]){
        printf("ERROR, ciudad destino fuera de rango.");
    }
    if (originIndex == destinyIndex){ // Caso que origen = destino
        printf("Ya se esta ahi, no ocupa viajar. -> Distancia: 0\n");
        exit(1);
    }
    printf("\nBuscando el camino mas corto para ir de %c a %c...", originIndex + 'A', destinyIndex + 'A');

    distToBeat = dists[originIndex][destinyIndex]; // Distancia directa, es primera opcion
    if (distToBeat == -1){ // Caso que no hay conexion directa
        printf("\nNo hay camino directo entre %c y %c. Buscando otro...", originIndex + 'A', destinyIndex + 'A');
        distToBeat = __INT_MAX__; // Macro maximo numerico para buscar algo menor
    }
    // Logica de camino mas corto
    int auxArray[fact(N)*N]; // Array con caminos posibles
    int Paths[fact(N)][N]; // Matriz de caminos posibles
    perms(cityIndexes, N, 0, auxArray,  &count); // Iterar osbre todos los caminos posibles
    
    // Asignar la matriz de caminos posibles
    for (i = 0; i < fact(N); i++){
        for (j = 0; j < N; j++){
            Paths[i][j] = auxArray[k];
            k++;
        }
    }

    int distTOTAL;
    for (i = 0; i < fact(N); i++){
        if (Paths[i][0] != originIndex){
            continue;
        } else{
            distTOTAL = 0;
            for (m = 0; m < N; m++){
            }
            for (j = 0; j < N; j++){
            if (Paths[i][j] == destinyIndex){
                distTOTAL = distTOTAL;
                break;
            } else if (dists[Paths[i][j]][Paths[i][j+1]] == -1){
                distTOTAL = __INT_MAX__;
                break;
            } else{
                distTOTAL += dists[Paths[i][j]][Paths[i][j+1]];
                } // FIn iteracion camino
            }
            if(distTOTAL < distToBeat && distTOTAL > 0){
                distToBeat = distTOTAL;
                for(l = 0; l < N; l++){
                    bestPath[l] = Paths[i][l];
                }
            }

        }
        
        }
    printf("\n\nENCONTRADO! Camino mas corto:\n");

    for (i = 0; i < N && bestPath[i] != destinyIndex; i++){
        printf("-> %c ", cities[bestPath[i]]);
    }
    printf("-> %c", cities[destinyIndex]);
    printf("\nDistancia: %d\n", distToBeat);
    return 0;
}
