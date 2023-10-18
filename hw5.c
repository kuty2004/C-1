#include <stdio.h>

void DecToBin(int num){
    int until = num/2;
    int remain = num%2;
    if(until >= 1){
        DecToBin(num/2);
    }
    printf("%d", remain);
}

int main(){
    int number;
    printf("Please enter a number: ");
    scanf("%d", &number);
    DecToBin(number);
    return 0;
}