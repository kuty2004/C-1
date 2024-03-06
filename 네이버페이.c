#include <stdio.h>

int main(void){
    printf("=== 네이버 페이 결제 계산 프로그램 ===\n");
    int cost;
    printf("주문액을 입력하세요: ");
    scanf("%d", &cost);
    printf("\n");

    printf("=== 결제 수단 목록 ===\n");
    printf("a) Npay머니 네이버통장 충전결제 b)Npay머니 일반 충전결제 c)계좌 간편결제 d)네이버 현대카드 간편결제 e)청구할인 삼성카드결제 f)일반 카드결제\n");
    char payment;
    int paymoney = 0, bank = 0, card = 0, sale = 0;
    int basic = cost*(1.0/100);

    printf("결제 수단을 입력하세요: ");
    scanf(" %c", &payment);
    while(1){
        if(payment == 'A' || payment == 'a'){
            paymoney = cost*(1.5/100);
            bank = cost*(0.5/100);
            break;
        }
        else if(payment == 'B' || payment == 'b'){
            paymoney = cost*(1.5/100);
            break;
        }
        else if (payment == 'C' || payment == 'c' || payment == 'F' || payment == 'f'){
            break;
        }
        else if(payment == 'D' || payment == 'd'){
            card = cost*(5.0/100);
            if ( card >= 10000){
                card = 10000;
            }
            break;
        }
        else if(payment == 'E' || payment == 'e'){
            sale = cost*(5.0/100);
            if(cost < 50000){
                sale = 0;
            }
            if(sale >= 5000){
                sale = 5000;
            }
            break;
        }
        else{
            printf("잘못 입력하셨습니다. 재입력 바랍니다. \n");
            printf("결제 수단을 입력하세요: ");
            scanf(" %c", &payment);
            continue;
        }
        break;
    }
    printf("\n");

    char membership;
    int member = 0;
    printf("네이버 멤버십에 가입되어 있나요 (y/n)? ");
    scanf(" %c", &membership);
    if (membership == 'Y' || membership == 'y') {
        if (cost >= 200000) {
            member = (cost-200000) * (1.0 / 100) + 8000;
        } else {
            member = cost * (4.0 / 100);
        }
        if (member >= 20000) {
            member = 20000;
        }
    }
    else {
        member = 0;
    }

    printf("\n");

    printf("=== 결제 및 적립 내역 ===\n");
    printf("주문금액 %d원\n", cost);
    if(sale > 0){
        printf("청구할인 %d원\n", sale);
    }
    printf("기본 적립 %d원\n", basic);
    if(paymoney > 0){
        printf("네이버페이 머니 결제적립 %d원\n", paymoney);
    }
    if(bank > 0 ){
        printf("네이버통장 추가적립 %d원\n", bank);
    }
    if(card > 0){
        printf("네이버 현대카드 추가적립 %d원\n", card);
    }
    if(member > 0){
        printf("네이버 멤버십 추가적립 %d원\n", member);
    }
    printf("총 적립액은 %d원입니다.\n", cost*(1/100)+paymoney+bank+card+member+basic);

    return 0;
}   