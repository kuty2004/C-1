#include <stdio.h>

int main(void){
    int icesize;
    printf("=== 아이스바 그리기 프로그램 ===\n");
    while(1){
        printf("아이스바의 크기를 3 이상의 홀수로 입력하세요:");
        scanf("%d", &icesize);

        if(icesize<3 || icesize%2 == 0){
            printf("아이스바의 크기가 범위를 벗어납니다. (짝수 또는 3 미만)\n");
            printf("\n");
            continue;
        }
        else{
            for(int i = 1; i <= icesize; i++){
                printf("*");
            }
            printf("\n");

            for(int j = 3; j <= icesize; j++){
                for(int k = 1; k <=3; k++){
                    printf("*");
                    for(int blank = 1; blank <= (icesize-2)/2; blank++){
                        printf(" ");
                    }
                }
                printf("\n");
            }
            for(int l = 1; l <= icesize; l++){
                printf("*");
            }
            printf("\n");

            for(int m = 1; m <= icesize/5; m++){
                for(int blank = 1; blank <= (icesize-1)/2; blank++){
                    printf(" ");
                }
                printf("|\n");
            }
            break;
            }
        }
}