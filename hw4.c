#include <stdio.h>

int main(void){
    int num1, count = 0;
    printf("Please enter a number: ");
    scanf("%d", &num1);
    for(int i = 1; i <= num1; i++){
        int calculate = num1%i; 
        if (calculate == 0){
            count += 1;
        }
    }
    if(count == 2){
        printf("It is a prime number.");
    }
    else{
        printf("It is not a prime number.");
    }
}