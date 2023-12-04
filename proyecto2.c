#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double PI = 3.14159265358979323846; // Necesario paralos angulos

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
    float sum = 0; // Suma inicial de angulos obtenidos
    
    // Se pide al usuario la cantidad de lados del poligono
    printf("Ingrese la cantidad de lados de su poligono: \n"); 
    scanf("%d", &n);
    printf("\n");

    // Caso de error, deben ser minimo 3 lados
    if (n < 3){
        printf("Su poligono es invalido, debe ser minimo de 3 lados.\n");
        exit(1);
    }

    float xCoords[n], yCoords[n], dists[n], auxdists[n], angles[n]; // Arrays necesarios

    printf("Ingrese las coordenadas en orden que se conectan por lineas en el poligono.\n");

    // Obtener e imprimir coordenadas
    for (i = 0; i < n; i++){
        printf("Ingrese la %d° coordenada x: ", i+1);
        scanf("%f", &xCoords[i]);
        printf("Ingrese la %d° coordenada y: ", i+1);
        scanf("%f", &yCoords[i]);
        printf("Coordenadas => [%f, %f]\n\n", xCoords[i], yCoords[i]);
    }

    // Obtener todas las distancias del perimetro del poligono
    for (i = 0; i < n; i++){
        if (i == n-1){
            dists[n-1] = pointDist(xCoords[0], yCoords[0], xCoords[n-1], yCoords[n-1]);
        } else{
            dists[i] = pointDist(xCoords[i], yCoords[i], xCoords[i+1], yCoords[i+1]);
        }
    }

    // Obtener las distancias auxiliares
    for (i = 0; i < n; i++){
        if (i == 0){
            auxdists[i] = pointDist(xCoords[i+1], yCoords[i+1], xCoords[n-1], yCoords[n-1]);
        }
        else if(i == n-1){
            auxdists[n-1] = pointDist(xCoords[0], yCoords[0], xCoords[i-1], yCoords[i-1]);
        }
        else {
            auxdists[i] = pointDist(xCoords[i-1], yCoords[i-1], xCoords[i+1], yCoords[i+1]);
        }
    }

    // Obtener los angulos con ley de cosenos
    for (i = 0; i < n; i++){
        if (i == 0){
            angles[i] = cosLaw(auxdists[i], dists[n-1], dists[i]);
        }
        else{
            angles[i] = cosLaw(auxdists[i], dists[i], dists[i-1]);
        }
    }

    // Obtener la suma de angulos internos obtenida
    for (i = 0; i < n; i++){
        sum = sum + angles[i];
    }

    totAngle = (n-2)*180; // Angulo interno total teorico
    printf("Suma de angulos internos obtenida: %.2f°\n\n", sum);

    // Verificar suma de angulos internos, permituendo 5% de error
    if (sum < 0.95*totAngle || 1.05*totAngle < sum){
        printf("ERROR. Poligono no convexo porque su suma de angulos internos no es el teorico.\n");
        exit(1);
    } else{
        // Imprimir resultados
        for (i = 0; i<n; i++){
            printf("El angulo visto desde [%.2f, %.2f] => %.2f°\n", xCoords[i], yCoords[i], angles[i]);
        }
    }

    return 0;
}
