#include <stdio.h>

int main(){
    float km;
    float mile = 1.609;
    printf("Please enter kilometers: ");
    scanf("%f", &km);
    printf("%.1f km is equal to %.1f miles.", km, km/1.609);
}
