#include <stdio.h>

int totalmoney = 1000000;

void deposit(unsigned int depositmoney){
    totalmoney += depositmoney;
    printf("입금이 완료되었습니다.\n");
    printf("현재 잔고는 %d원입니다.\n", totalmoney);
    printf("\n");
}

void withdraw(unsigned int withdrawmoney){
    if(withdrawmoney > totalmoney){
        printf("잔액이 부족합니다.\n");
        printf("현재 잔고는 %d원입니다.\n", totalmoney);
        printf("\n");
    }
    else{
        totalmoney -= withdrawmoney;
        printf("출금이 완료되었습니다.\n");
        printf("현재 잔고는 %d원입니다.\n", totalmoney);
        printf("\n");
    }
}

void check_balance(){
    printf("현재 잔고는 %d원입니다.\n", totalmoney);
    printf("\n");
}

int main(void){
    int worknum;
    printf("===== ㅅㅁ은행 ATM기입니다  =====\n");

    while(1){
        printf("1.입금\n2.출금\n3.잔액 조회\n4.종료\n");
        printf("원하는 작업 번호를 선택하세요:");
        scanf("%d", &worknum);

        if(worknum == 1){
            int depositmoney;
            printf("입금할 금액을 입력하세요: ");
            scanf("%d", &depositmoney);
            deposit(depositmoney);
            continue;
        }
        else if(worknum == 2){
            int withdrawmoney;
            printf("출금할 금액을 입력하세요:");
            scanf("%d", &withdrawmoney);
            withdraw(withdrawmoney);
            continue;
        }
        else if(worknum == 3){
            check_balance();
            continue;
        }
        else if(worknum == 4){
            printf("안녕히 가세요.\n");
            printf("\n");
            break;
        }
        else{
            printf("올바른 작업 번호를 선택하세요.\n");
            printf("\n");
            continue;
        }
    }

}