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
Se decide cambiar la logica a una representaci[on de matriz mas detallada,
porque una matriz aca en C debe verse como un puntero de punteros, la idea
anterior tenia un fallo en la logica porque cuando uno accede al puntero
de un array, este tiene un unico puntero que esta asociado al primer byte
del arreglo. Entonces, se intentara construir la matriz tal que se repre-
sente como un array de arrays para mayor robustez.

Entonces, vamos a tener un puntero, que apunta a la matriz y dentro de
ella es donde vamos a proceder a obtener cada puntero correspondiente
a las filas.

Para se va a definir como: int **MATRIZ
donde (*MATRIZ) se refiere a la matriz e (int *) se refiere a lo que con-
tiene *MATRIZ, es decir, le indicamos que contiene punteros.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void viewPointer2Rows(int **matriz, int row) {

    for (int i=0; i<row; i++) {
        printf("El puntero de la fila %d es: %p\n", i, &matriz[i]);
        printf("Valor que apunta al puntero de la fila: %d", *matriz[i]);
        printf("\n");
    }
}

// Funcion para inicializar la matriz, y crear todas sus caracteristicas
int **createMatrix(int N, int M) {
    int **matriz;

    // Vamos a reservar memoria de acuerdo a las filas y con
    // tamanio de un puntero int. El (int **) al inicio, re-
    // cordemos es para indicar que sera un puntero de punteros.
    matriz = (int **)calloc(N, sizeof(int *));


    // El siguiente for es para almacenar memoria en las filas
    for (int i=0; i<N; i++) {

        // reserva memoria de acuerdo a las columnas M y con
        // tamanio de entero, porque aqui si van los enteros
        // recordemos que (int *) es para hacer el casting in-
        // dicando esa posicion dentro de matriz es un puntero.
        matriz[i] = (int *)calloc(M, sizeof(int));
    }

    return matriz;
}


// Funcion para ver la matriz
void viewMatrix(int **matriz, int N, int M) {

    // for que recorre las filas
    for (int i=0; i<N; i++) {
        
        // for que recorre las columnas
        for (int j=0; j<M; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n"); // para separar las filas
    }
}


// MAIN
int main() {
    // INICIALIZAR VARIABLES
    int filas, columnas, tamanio, values;
    int **matrix;
    char entrada[20];

    // INTERACCION CON EL USUARIO
    printf("Escoja la cantidad de filas de la matriz: ");
    scanf("%d", &filas);
    printf("Escoja la cantidad de columnas de la matriz: ");
    scanf(" %d", &columnas);

    tamanio = filas * columnas;

    // CREAR LA MATRIZ
    matrix = createMatrix(filas, columnas);

    // GUARDAR VALORES EN LA MATRIZ
    //printf("Ingrese los numeros que desea almacenar en la matriz: ");
    //scanf("%s", entrada);
    //printf("Asi se ve values %s\n", entrada);
    //printf("Asi se ve len values %zu\n", strlen(entrada));

    for (int i=0; i<filas; i++) {
        for (int j=0; j<columnas; j++) {
            printf("Ingrese el valor para la posicion [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
        printf("\n");
    }

    // VER LOS PUNTEROS DE LAS FILAS
    viewPointer2Rows(matrix, filas);

    // VER MATRIZ
    printf("\nSu matriz creada es:\n");
    viewMatrix(matrix, filas, columnas);


    // LIBERAR MEMORIA
    // lo hacemos en el main ya que de otra forma no podriamos
    // utilizarla aca.
    for (int k=0; k<filas; k++) {
        free(matrix[k]);
    }

    free(matrix);


    return 0;
}

