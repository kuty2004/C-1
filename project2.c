#include "ascii_art.h"
#include <stdio.h>

int main(void){
    int picnum, right, down; 
    while(1){
        printf("그림 번호 선택(1.main, 2.flower, 3.castle, 기타:종료): ");
        scanf("%d", &picnum);

        if(picnum != 1 && picnum != 2 && picnum != 3){
            printf("안녕히 가세요.");
            break;
        }

        printf("오른쪽으로 몇 칸 이동할까요?");
        scanf("%d", &right);
        printf("아래로 몇 줄 이동할까요?");
        scanf("%d", &down);
        printf("선택한 그림을 해당 위치로부터 출력합니다.\n");
    
        if(picnum == 1){
            for(int i = 1; i <= down; i++){
                printf("\n");
            }
            for(int column = 0; column < 9; column++){
                for(int j = 1; j <= right; j++){
                    printf(" ");
                }
                for(int row = 0; row < 46; row++){
                    char *pic_main = ascii_main[column];
                    printf("%c", pic_main[row]);
                }
                printf("\n");
            }
            printf("\n");
        }
        else if(picnum == 2){
            for(int i = 1; i <= down; i++){
                printf("\n");
            }
            for(int column = 0; column < 13; column++){
                for(int j = 1; j <= right; j++){
                    printf(" ");
                }
                for(int row = 0; row <= 18; row++){
                    char *pic_flower = ascii_flower[column];
                    printf("%c", pic_flower[row]);
                }
                printf("\n");
            }
            printf("\n");
        }
        else if(picnum == 3){
            for(int i = 1; i <= down; i++){
                printf("\n");
            }
            for(int column = 0; column < 20; column++){
                for(int j = 1; j <= right; j++){
                    printf(" ");
                }
                for(int row = 0; row < 57; row++){
                    char *pic_castle = ascii_castle[column];
                    printf("%c", pic_castle[row]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}