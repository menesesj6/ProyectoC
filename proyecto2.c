#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double PI = 3.14159265358979323846;

float pointDist(float xA, float yA, float xB, float yB){
    // Se calcula la distancia entre dos puntos
    float dist = sqrt(pow(xB-xA, 2) + pow(yB-yA, 2));
    return dist;
}

float cosLaw(float a, float b, float c){
    // Se calcula el angulo despejando ley de cosenos
    float angle = acos((pow(a, 2) - pow(b, 2) - pow(c, 2))/(-2*b*c));
    return (angle*180)/PI;
}

int main(){
    int n; // Cantidad de lados y angulos
    int totAngle; // Angulo total teorico
    int i; // Valor para iteraciones
    
    // Se pide al usuario la cantidad de lados del poligono
    printf("Ingrese la cantidad de lados de su poligono: \n"); 
    scanf("%d", &n);

    // Caso de error, deben ser minimo 3 lados
    if (n < 3){
        printf("Su poligono es invalido, debe ser minimo de 3 lados.\n");
        exit(1);
    }

    float xCoords[n], yCoords[n], angles[n]; // Arrays necesarios

    for (i = 0; i < n; i++){
        printf("Ingrese la %d° coordenada x: ", i+1);
        scanf("%f", &xCoords[i]);
        printf("Ingrese la %d° coordenada y: ", i+1);
        scanf("%f", &yCoords[i]);
        printf("Coordenadas => [%f, %f]\n\n", xCoords[i], yCoords[i]);
    }

    totAngle = (n-2)*180; // Angulo interno total teorico
    printf("EL angulo interno total del poligono teorico: %d\n", totAngle);
    return 0;
}
