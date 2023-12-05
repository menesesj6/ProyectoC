/*
Código realizado por:
- Jorge Meneses Garro, C14742
- Kristhel Quesada López, C06153

Descripción:
El siguiente código permite que el usuario cree una matriz de
NxM donde los datos almacenados serian de manera dinamica. En
el programa se hara uso de una funcion que recibe una cantidad
arbitrario de numeros enteros que representen las posiciones
dentro de la matriz. Asimismo, se realizan sanity checks tal
que si la funcion retorna un 0 entonces no hubo ningun error
mas si retorna un -1 entonces se detecto un error, como que
los valores ingresados no corresponden a un unico tipo, o los
valores ingresados no son enteros.
*/

/*
Se nos pide trabajar con enteros, como el usuario debe ingresar
una cantidad indefinida de ellos sabemos que vamos a tener un
arreglo de enteros de 32bits o 4 bytes.

Se podria decir que cada posicion del arreglo representa una
posicion en la matriz. Dependiendo de lo que nos especifiquen
entonces seccionamos las filas de la matriz cada tantas columnas.

Por tanto se asume la siguiente logica con base en la descripcion
brindada en el enunciado. Se le va a solicitar al usuario un
array de valores enteros, pero antes se le debera preguntar la
cantidad de filas y columnas que va a tener la matriz. Entonces,
si el usuario digita row=3, column=2 se deberia esperar un array
tipo --> valores={1,2,3,4,5,6} donde las filas son:
-fila1: 1,2
-fila2: 3,4
-fila3: 5,6
y por tanto solo se deberian obtener los punteros de 1, 3 y 5.
*/

#include <stdio.h>
#include <stdlib.h>

void matrix(int row, int column, int valores[]) {
    // No hay manera de guardar el tamanio de un array, la unica
    // forma es si los especificamos en otra variable
    int size = row * column;
    int fin = size - 1; // para sanity check


    // Sanity 
}


int main() {
    // INICIALIZAR VARIABLES
    int fila;
    int columna;
    int tamanio;
    int value;
    void* matrizPunt = NULL;
    char entrada[20];

    // INTERACCION CON EL USUARIO
    printf("Escoja la cantidad de filas de la matriz: ");
    scanf("%d", &fila);
    printf("Escoja la cantidad de columnas de la matriz: ");
    scanf(" %d", &columna);

    tamanio = fila * columna;

    // CREAR LA MATRIZ
    matrizPunt = calloc(tamanio, sizeof(int));
    int * matriz = (int *) matrizPunt;

    for (int i=0; i < tamanio; i++) {
        printf("Ingrese el primer valor de la matriz: ");
        scanf("%s", entrada);

        value = atoi(entrada);

        matriz[i] = value;
    }

    // Ver matriz
    for (int j=0; j < tamanio; j++) {
        printf("Posicion %d de matriz es 0x%x\n", j, matriz[j]);
    }


    // LIBERAR MEMORIA
    free(matriz);


    return 0;
}

