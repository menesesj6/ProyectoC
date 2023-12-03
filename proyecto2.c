#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double PI = 3.14159265358979323846;

float pointDist(float xA, float yA, float xB, float yB){
    float dist = sqrt(pow(xB-xA, 2) + pow(yB-yA, 2));
    return dist;
}

float cosLaw(float a, float b, float c){
    float angle = acos((pow(c, 2) - pow(a, 2) - pow(b, 2))/(-2*a*b));
    return (angle*180)/PI;
}

int main(){
    return 0;
}
