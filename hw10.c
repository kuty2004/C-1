#include <stdio.h>
#include <math.h>
#include <string.h>

struct cityinfo{
    char city[20];
    char country[60];
    int population;
};

void ClearLine(void){
    while(getchar()!='\n');
}

void RemoveRSN(char str[]){
    int len = strlen(str);
    str[len - 1] = 0;
}

int main(void){
    struct cityinfo arr[3];
    printf("input three cities: \n");
    for(int i = 0; i < 3; i++){
        printf("Name> ");
        fgets(arr[i].city, sizeof(arr[i].city), stdin);
        RemoveRSN(arr[i].city);
        
        printf("Country> ");
        fgets(arr[i].country, sizeof(arr[i].country), stdin);
        RemoveRSN(arr[i].country);

        printf("Population> ");
        scanf("%d", &arr[i].population);
        ClearLine();
    }
    printf("\n");
    printf("Printing the three cities: \n");
    for(int i = 0; i < 3; i++){
        printf("%d. %s in %s with a population of %d people\n", i+1, arr[i].city, arr[i].country, arr[i].population);
    }
    return 0;
}