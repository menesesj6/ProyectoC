/*
Código realizado por:
- Jorge Meneses Garro, C14742
- Kristhel Quesada López, C06153

Descripción:
El siguiente código permite que el usuario cree una matriz de
NxM donde los datos almacenados serian de manera dinamica. En
el programa se hara uso de 4 funciones:
1. La primera crea una matriz mediante memoria dinamica mediante
una logica de que esta represente un puntero de punteros, ya que
eso hace de manera mas sencilla la extraccion de los punteros de
cada fila, aparte que le da mas robustez al concepto de matriz.
2. La segunda funciona para darle estructura a la matriz y poderla
visualizar de mejor manera.
3. La tercera es una funcion que me permite crear una cantidad
arbitraria de numeros empleando la menoria dinamica y el uso de
reallocate para dimensionar la entrada ingresada segun los valo-
res que disponga el usuario.
4. La cuarta funcion es la funcion objetivo, la cual cumple con
los requisitos que demanda el enunciado. Pasa por parametro la
cantidad indefinida de numeros, los convierte a enteros, llena
la matriz creada con los valores enteros y luego de tener la
matriz creada completamente, extraemos los punteros que corres-
ponden al valor de la primera fila. Luego, como segunda compro-
bacion se despliega la matriz creada a como el usuario dispuso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FUERADERANGO para detectar el error cuando se ingresa
// una cantidad de valores diferente al tamanio asignado
// a la matriz.
enum ERRORES {
    EXITO = 0,
    FUERADERANGO = -1,
};

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


// Funcion que permite crear una cantidad arbitraria de numeros enteros
/*
str es donde se almacenaran todos los valores que vayamos agregando, o que
agrega el usuario, se define como memoria dinamica con malloc y se le asigna
1*size creando primero un unico espacio en memoria de tamanio char. Luego una
variable para el while, que define la posicion inicial del str.
El while se va a encargar que cada que se ingrese una variable mediante el
uso de getc que me permite recibir una entrada por parte del usuario o del
standard input y siempre que sea distinto de un cambio de linea para que se
guarden los cambios hasta donde se haya realizado. Luego para la posicion
de str i se guarda ahi el valor ingresado. Finalmente, como todo string, fina-
lizamos su ultimo valor con \0 y retornamos el string creado dinamicamente.
*/
char *dynamicString() {
    char *str, valor;
    int i = 0;
    str = (char*)malloc(1*sizeof(char));

    // PEDIRLE LOS VALORES AL USUARIO
    printf("Ingrese los numeros que desea almacenar en la matriz: \n");

    while(valor = getc(stdin), valor != '\n') {
        str[i] = valor;
        i++;
        str = realloc(str, i*sizeof(char));
    }

    str[i] = '\0';
    return(str);
}


int funcionObjetivo(int **matriz, int rows, int columns, char *entrada) {
    // Inicializamos las variables
    char* cursor = entrada;
    int i=0, j=0, contador=0;
    int tamanio = rows*columns;
    int status = EXITO;

    if (rows<0 || columns<0){
        printf("Ni filas y las columnas no pueden ser negativas\n");
        status = FUERADERANGO; // Valor inválido, error
        goto exit;
    }


    // Aca hacemos casting de str a int para almacenarlas en la matriz
    /*
    Cursor es una variable que me permite recorrer el string.
    De la libreria string.h se utiliza strlen y strtol. El primero permite
    btener el tamanio de un string contando todo como un caracter de uno a
    uno. El segundo permite convertir un string basicamente a un long int.
    Para ello se le especifica en su parametro primero el valor que almacena
    cursor (lo que va leyendo), luego su posicion en memoria y por ultimo
    se especifica la base del numero, en nuestro caso decimal.
    */
    while (cursor != entrada + strlen(entrada)) {
        long int x = strtol(cursor, &cursor, 10);

        // Funciona para indicar el separador, en este caso
        // se disenia para que se puedan separar los numeros
        // por coma y por espacio. Si el cursor tiene como
        // valor estos elementos entonces corre el puntero sin
        // mas.
        while (*cursor == ' ' || *cursor == ',') {
            cursor++;
        }

        // Para deteccion de errores
        // No solo detecta si el tamanio es incorrecto
        // tambien si no es un entero porque el contador
        // no se actualiza si cursor lee chars.
        contador++;

        if (tamanio < contador) {
            printf(
            "La cantidad de valores ingresados debe ser menor o igual que NxM o verifique que solo haya ingresado enteros\n"
            );
            status = FUERADERANGO;
            goto exit;
        }
        
        // como la matriz debe funcionar para enteros hacemos un casting
        // de long int a int, y almacenamos el valor que registra el puntero
        // en la posicion de la matriz
        int intval = (int) x;
        matriz[i][j] = intval;


        // esto me permite controlar el flujo de almacenamiento, los valores
        // se agregan de por columna y se cambia de fila una vez hayamos lle-
        // gado al final de las columnas totales.
        if (j == columns-1) {
            j = -1; // se setea en -1 ya que de otra forma no ajustaba
            i++;
        }

        // esto es lo que permite ir aumentando la columna
        j=j+1;
    }


    // Aca obtenemos los punteros asociados a cada fila y comprobamos
    // obteniendo el valor al cual apunta el puntero
    for (int i=0; i<rows; i++) {
        printf("El puntero de la fila %d es: %p\n", i, &matriz[i]);
        printf("Valor que apunta al puntero de la fila: %d", *matriz[i]);
        printf("\n");
    }

    // Aca desplegamos la matriz creado como segundo metodo de comprobacion
    printf("\nSu matriz creada es:\n");
    viewMatrix(matriz, rows, columns);

exit:
    return status;
}


// MAIN
int main() {
    // INICIALIZAR VARIABLES
    int filas, columnas;
    int **matrix;
    char * entrada = dynamicString();

    // INTERACCION CON EL USUARIO
    printf("\n>>> Determine la forma en la que quiere distribuir la matriz\n");
    printf("Escoja la cantidad de filas de la matriz: ");
    scanf("%d", &filas);
    printf("Escoja la cantidad de columnas de la matriz: ");
    scanf(" %d", &columnas);

    // CREAR LA MATRIZ
    matrix = createMatrix(filas, columnas);

    // LLAMAR A LA FUNCION OBJETIVO
    printf("\n");
    funcionObjetivo(matrix, filas, columnas, entrada);

    // LIBERAR MEMORIA DE LA MATRIZ CREADA
    for (int k=0; k<filas; k++) {
        free(matrix[k]);
    }
    free(matrix);
    
    // LIBERAR MEMORIA DE LOS VALORES INGRESADOS
    free(entrada);


    return 0;
}