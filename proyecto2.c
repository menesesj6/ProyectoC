
/*Programa calcula angulos internos de un poligono.

El programa solicita coordenadas (x,y) al usuario de manera
interactiva. Con base en estas coordenadas dadas se define
si puede haber un poligono convexo o no. Si si es convexo,
se calculan cada uno de sus angulos internos y se indica en
cual coordenada esta ese angulo. ESte angulo se calcula al
despejar la ley de cosenos.

Hecho por:
Jorge Meneses Garro - C14742
Kristhel Quesada Lopez - C06153*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double PI = 3.14159265358979323846; // Necesario para los angulos

float pointDist(float xA, float yA, float xB, float yB){
    // Se calcula la distancia entre dos puntos
    float dist = sqrt(pow(xB-xA, 2) + pow(yB-yA, 2));
    return dist;
}

float cosLaw(float a, float b, float c){
    // Se calcula el angulo despejando ley de cosenos a^2 = b^2+c^2-2*b*c*cos(phi)
    float angle = acos((pow(a, 2) - pow(b, 2) - pow(c, 2))/(-2*b*c)); // Angulo en radianes
    return (angle*180)/PI; // Angulo en grados
}

void swap(float *a, float *b){
    // Intercambiar valores
    float temp = *a;
    *a = *b;
    *b = temp;
}

int main(){
    int n; // Cantidad de lados y angulos
    int totAngle; // Angulo total teorico
    int i, j, k, m; // Valor para iteraciones
    float sum; // Suma inicial de angulos obtenidos
    
    // Se pide al usuario la cantidad de lados del poligono
    printf("Ingrese la cantidad de lados de su poligono: \n"); 
    scanf("%d", &n); // Recibir cantidad de lados y angulos del poligono deseado
    printf("\n");

    // Caso de error, deben ser minimo 3 lados
    if (n < 3){
        printf("Su poligono es invalido, debe ser minimo de 3 lados.\n");
        exit(1);
    }

    totAngle = (n-2)*180; // Angulo interno total teorico
    
    // Arrays necesarios
    float xCoordsIN[n], yCoordsIN[n], dists[n], auxdists[n], angles[n]; 
    /*
    xCoordsIN: 
        Coordenadas x ingresadas por el usuario
    yCoordsIN: 
        Coordenadas y ingresadas por el usuario
    dists: 
        Tamano de cada lado del poligono formado
    auxdists: 
        Tamano de la linea opuesta a cada angulo para la ley de cosenos
    angles: 
        Angulos internos del poligono formado
    */

    // Obtener e imprimir coordenadas
    for (i = 0; i < n; i++){
        printf("Ingrese la %d° coordenada x: ", i+1);
        scanf("%f", &xCoordsIN[i]); // Recibir coordenada x
        printf("Ingrese la %d° coordenada y: ", i+1);
        scanf("%f", &yCoordsIN[i]); // Recibir coordenada y
        printf("Coordenadas => [%f, %f]\n\n", xCoordsIN[i], yCoordsIN[i]); // Imprimir cada par ordenado
    }

    // Se iteran todas los poligonos posibles para analizar si hay uno convexo
    for (m = 0; m<n; m++){
        for (j = 0; j < n; j++){
            for (k = 0; k < n; k++){
            swap(&xCoordsIN[k], &xCoordsIN[m]); // Variar coordenadas x
            swap(&yCoordsIN[k], &yCoordsIN[m]); // Variar coordenadas y
            // Obtener todas las distancias del perimetro del poligono
            for (i = 0; i < n; i++){
                if (i == n-1){
                    dists[n-1] = pointDist(xCoordsIN[0], yCoordsIN[0], xCoordsIN[n-1], yCoordsIN[n-1]);
                } else{
                    dists[i] = pointDist(xCoordsIN[i], yCoordsIN[i], xCoordsIN[i+1], yCoordsIN[i+1]);
                }
            }

            // Obtener las distancias auxiliares
            for (i = 0; i < n; i++){
                if (i == 0){
                    auxdists[i] = pointDist(xCoordsIN[i+1], yCoordsIN[i+1], xCoordsIN[n-1], yCoordsIN[n-1]);
                }
                else if(i == n-1){
                    auxdists[n-1] = pointDist(xCoordsIN[0], yCoordsIN[0], xCoordsIN[i-1], yCoordsIN[i-1]);
                }
                else {
                    auxdists[i] = pointDist(xCoordsIN[i-1], yCoordsIN[i-1], xCoordsIN[i+1], yCoordsIN[i+1]);
                }
            }

            // Obtener los angulos con ley de cosenos
            for (i = 0; i < n; i++){
                if (i == 0){
                    angles[i] = cosLaw(auxdists[i], dists[n-1], dists[i]);
                }
                else{
                    angles[i] = cosLaw(auxdists[i], dists[i-1], dists[i]);
                }
            }

            sum = 0; // Se reinicia la suma de angulos internos

            // Obtener la suma de angulos internos obtenida
            for (i = 0; i < n; i++){
                sum += angles[i];
            }
            // Verificar suma de angulos internos, permitiendo 5% de error
            if (sum < 0.95*totAngle || 1.05*totAngle < sum){
                continue; // Ir a la siguiente iteracion
            } else {
                printf("Suma de angulos internos obtenida: %.2f° => CORRECTO, ES CONVEXO!\n\n", sum); 
                for (i = 0; i<n; i++){
                    printf("El angulo visto desde [%.2f, %.2f] => %.2f°\n", xCoordsIN[i], yCoordsIN[i], angles[i]); // Imprimir resultados con 2 decimales
                }
                exit(1);
                }
            }
        }
    }
    printf("ERROR, NO SE PUDO ENCONTRAR UN POLIGONO CONVEXO.\n"); // Mensaje error cuando no es convexo
    return 0;
}
