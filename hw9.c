#include <stdio.h>

int main(void) {
    int ch;
    printf("Input> ");
    ch = getchar();
    printf("Output> ");
    while(ch != EOF){
        if ('A' <= ch && ch <= 'Z') {
            ch += 'a' - 'A';
            putchar(ch);
        }else if ('a' <= ch && ch <= 'z') {
            ch -= 'a' - 'A';
            putchar(ch);
        }
        else{
            putchar(ch);
        }
        ch = getchar();
    }
    return 0;
}
