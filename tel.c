#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

//구조체 정의: 연락처 정보를 저장
typedef struct {
    char name[30];  //이름
    char phone[20]; //전화번호
    char memo[50];  //메모
} Contact;

//연락처를 이름 기준으로 정렬하기 위한 비교 함수
int compare(const void *a, const void *b) {
    Contact *contactA = (Contact *)a;
    Contact *contactB = (Contact *)b;
    return strcasecmp(contactA->name, contactB->name);
}

//함수 선언
void search(char *contact, int num);
void add(char *name, char *phone, char *memo);
void delete(char *contact, int num);
void list(int linenum);
int countlines();
void search_contact();
void add_contact();
void delete_contact();

//메인 함수
int main(void) {
    initscr();  //ncurses 초기화
    cbreak();   //한 글자씩 입력 받기
    noecho();   //입력된 문자 화면에 출력하지 않음
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);  //터미널의 크기 얻기
    WINDOW* menuwin = newwin(7, xMax - 12, yMax - 9, 5);  //새로운 윈도우 menuwin 생성
    box(menuwin, 0, 0);  //윈도우에 박스 그리기
    refresh();
    wrefresh(menuwin);   //윈도우 새로고침
    keypad(menuwin, true);  //키패드 활성화

    //메뉴 옵션 정의
    char *choices[5] = {"Search contact", "Add contact", "Delete contact", "Show contact list", "Exit"};
    int choice;
    int highlight = 0;

    //메인 루프
    while (1) {
        //메뉴 옵션 출력
        for (int i = 0; i < 5; i++) {
            if (i == highlight)
                wattron(menuwin, A_REVERSE); //하이라이트 표시
            mvwprintw(menuwin, i + 1, 1, choices[i]);
            wattroff(menuwin, A_REVERSE); //하이라이트 해제
        }
        choice = wgetch(menuwin); //키 입력 받기

        //사용자 입력 처리
        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight < 0)
                    highlight = 4; //범위 초과 시 마지막 항목으로 이동
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight > 4)
                    highlight = 0; //범위 초과 시 첫번째 항목으로 이동
                break;
            case 10: //Enter key
                clear();
                switch (highlight) {
                    case 0:
                        wclear(menuwin); //윈도우 내용 지우기
                        search_contact(menuwin); //연락처 검색 함수 호출
                        box(menuwin, 0, 0); //윈도우 박스 재생성
                        wrefresh(menuwin); //윈도우 새로고침
                        break;
                    case 1:
                        wclear(menuwin); //윈도우 내용 지우기
                        add_contact(); //연락처 추가 함수 호출
                        box(menuwin, 0, 0); //윈도우 박스 재생성
                        wrefresh(menuwin); //윈도우 새로고침
                        break;
                    case 2:
                        wclear(menuwin); //윈도우 내용 지우기
                        delete_contact(menuwin); //연락처 삭제 함수 호출
                        box(menuwin, 0, 0); //윈도우 박스 재생성
                        wrefresh(menuwin); //윈도우 새로고침
                        break;
                    case 3:
                        wclear(menuwin); //윈도우 내용 지우기
                        int count = countlines(); //파일의 줄 수 세기
                        list(count); //연락처 리스트 출력 함수 호출
                        box(menuwin, 0, 0); //윈도우 박스 재생성
                        wrefresh(menuwin); //윈도우 새로고침
                        break;
                    case 4:
                        endwin(); //윈도우 종료
                        return 0;
                }
                break;
            default:
                break;
        }
        wrefresh(menuwin);
    }

    endwin();
    return 0;
}

//연락처 찾기 기능을 구현한 함수
void search(char *contact, int num) {
    WINDOW *win = newwin(LINES, COLS, 0, 0); //새로운 윈도우 생성
    FILE *fp = fopen("data.txt", "r"); //data.txt 파일 읽기모드로 열기
    if (fp == NULL) { //파일 열기에 실패했을 경우
        mvwprintw(win, 0, 0, "Failed to open file\n"); //실패 문구 출력
        wrefresh(win); //윈도우 새로고침
        delwin(win); //윈도우 삭제
        return;
    }
    
    Contact contacts[100];
    qsort(contacts, 100, sizeof(Contact), compare); //연락처를 이름 순으로 정렬
    char line[100];
    int found = 0;
    int i = 0;
    while (fgets(line, sizeof(line), fp) != NULL) { //파일에서 모든 줄을 읽을 때까지
        char contactName[30], contactPhone[20], contactMemo[50];
        sscanf(line, "%29[^:]:%19[^:]:%49[^\n]", contactName, contactPhone, contactMemo); //읽은 줄을 이름, 연락처, 메모로 나누기
        switch(num) {
            case 1: //이름으로 검색을 선택 시
                contactName[strcspn(contactName, "\n")] = 0; //이름에서 줄바꿈 제거
                if (strcmp(contactName, contact) == 0) { //입력한 이름과 일치하는 이름이 있으면
                    mvwprintw(win, i++, 0, "Name: %s, Phone number: %s, Memo: %s\n\n", contactName, contactPhone, contactMemo); //연락처 출력
                    wrefresh(win); //윈도우 새로고침
                    found = 1;
                    break;
                }
                break;
            case 2: //번호로 검색을 선택 시 
                contactPhone[strcspn(contactPhone, "\n")] = 0; //번호에서 줄바꿈 제거
                if (strcmp(contactPhone, contact) == 0) { //입력한 번호와 일치하는 번호가 있으면
                    mvwprintw(win, i++, 0, "Name: %s, Phone number: %s, Memo: %s\n\n", contactName, contactPhone, contactMemo); //연락처 출력
                    wrefresh(win); //윈도우 새로고침
                    found = 1;
                    break;
                }
                break;
            case 3: //메모로 검색을 선택 시 
                contactMemo[strcspn(contactMemo, "\n")] = 0; //메모에서 줄바꿈 제거
                if (strcmp(contactMemo, contact) == 0) { //입력한 메모와 일치하는 메모가 있으면
                    mvwprintw(win, i++, 0, "Name: %s, Phone number: %s, Memo: %s\n\n", contactName, contactPhone, contactMemo); //연락처 출력
                    wrefresh(win); //윈도우 새로고침
                    found = 1; 
                    break;
                }
                break;
        }
    }
    if (!found) { //일치하는 연락처를 못 찾았으면
        mvwprintw(win, i++, 0, "Could not find contact\n"); //문구를 출력
        wrefresh(win); //윈도우 새로고침
    }

    mvwprintw(win, i, 0, "Press any button to go back..."); //안내문 출력
    wrefresh(win); //윈도우 새로고침
    fclose(fp); //파일 닫기
    
    keypad(win, TRUE); //키보드 입력 대기
    wgetch(win); //키보드 입력 읽기

    wclear(win); //윈도우 내용 지우기
    wrefresh(win); //윈도우 새로고침
    delwin(win); //윈도우 삭제
}

//연락처 추가 기능을 구현한 함수
void add(char *name, char *phone, char *memo) {
    WINDOW *win = newwin(LINES, COLS, 0, 0); //새로운 윈도우 만들기
    FILE *fp = fopen("data.txt", "a"); //파일을 추가 모드로 열기
    if (fp == NULL) { //파일을 못 열었으면
        mvwprintw(win, 0, 0, "Failed to open file\n"); //안내 문구 출력
        wrefresh(win); //윈도우 새로고침
        delwin(win); //윈도우 삭제
        return;
    }

    fprintf(fp, "%s:%s:%s\n", name, phone, memo); //입력받은 이름:숫자:메모 형식으로 파일에 입력
    mvwprintw(win, 0, 0,"Contact added successfully\n"); //성공적으로 저장되었음을 출력
    mvwprintw(win, 1, 0, "Press any button to go back..."); //안내 문구 출력
    wrefresh(win); //윈도우 새로고침
    fclose(fp); //파일 닫기
    
    keypad(win, TRUE); //키보드 입력 대기
    wgetch(win); //입력 읽기

    wclear(win); //윈도우 내용 지우기
    wrefresh(win); //윈도우 새로고침
    delwin(win); //윈도우 삭제
}

//연락처 삭제 기능을 구현한 함수
void delete(char *contact, int num) {
    WINDOW *win = newwin(LINES, COLS, 0, 0); //새로운 윈도우 생성
    FILE *fp = fopen("data.txt", "r"); //data.txt 파일을 읽기모드로 열기
    FILE *temp = fopen("temp.txt", "w"); //임시로 번호를 추가할 temp.txt 파일을 입력 모드로 열기
    if (fp == NULL || temp == NULL) { //파일을 못 열었으면
        mvwprintw(win, 0, 0, "Failed to open file\n"); //실패 문구 출력
        wrefresh(win); //윈도우 새로고침
        delwin(win); //윈도우 삭제 
        return;
    }

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), fp) != NULL) { //파일 내의 모든 줄을 읽을 때까지
        char contactName[30], contactPhone[20], contactMemo[50];
        sscanf(line, "%29[^:]:%19[^:]:%49[^\n]", contactName, contactPhone, contactMemo); //읽은 줄에서 이름, 연락처, 메모를 분리
        switch(num) {
            case 1: //이름으로 삭제를 선택했을 시 
                contactName[strcspn(contactName, "\n")] = 0; //이름에서 줄바꿈 문자 제거
                if (strcmp(contactName, contact) != 0) { //입력된 이름과 이름이 일치하지 않으면
                    fprintf(temp, "%s", line); //temp.txt 파일에 줄 복사
                } else { //입력된 이름과 이름이 일치하면
                    found = 1; //found 변수를 1로 초기화 
                }
                break;
            case 2: //번호로 삭제를 선택했을 시 
                contactPhone[strcspn(contactPhone, "\n")] = 0; //번호에서 줄바꿈 문자 제거
                if (strcmp(contactPhone, contact) != 0) { //입력된 번호와 번호가 일치하지 않으면
                    fprintf(temp, "%s", line); //temp.txt 파일에 줄 복사
                } else { //입력된 번호와 번호가 일치하면
                    found = 1; //found 변수를 1로 초기화
                }
                break;
            case 3: //메모로 삭제를 선택했을 시 
                contactMemo[strcspn(contactMemo, "\n")] = 0; //메모에서 줄바꿈 문자 제거
                if (strcmp(contactMemo, contact) != 0) { //입력된 메모와 메모가 일치하지 않으면
                    fprintf(temp, "%s", line); //temp.txt 파일에 줄 복사
                } else { //입력된 메모와 메모가 일치하면
                    found = 1; //found 변수를 1로 초기화
                }
                break;
        }
    }

    if (found != 0) { //일치하는 연락처를 찾았으면
        remove("data.txt"); //data.txt 파일을 제거
        rename("temp.txt", "data.txt"); //temp.txt 파일의 이름을 data.txt로 변경
        mvwprintw(win, 0, 0, "Contact deleted successfully\n"); //성공 문구 출력
        wrefresh(win); //윈도우 새로고침
    } else { //일치하는 연락처를 못 찾았으면
        remove("temp.txt"); //temp.txt 파일을 제거
        mvwprintw(win, 0, 0, "Contact not found\n"); //실패 문구 출력
        wrefresh(win); //윈도우 새로고침
    }

    mvwprintw(win, 1, 0, "Press any button to go back..."); //안내 문구 출력
    wrefresh(win); //윈도우 새로고침
    fclose(fp); //data.txt 파일 닫기
    fclose(temp); //temp.txt 파일 닫기
    
    keypad(win, TRUE); //키보드 입력 대기
    wgetch(win); //입력 읽기

    wclear(win); //윈도우 내용 삭제
    wrefresh(win); //윈도우 새로고침
    delwin(win); //윈도우 삭제
}

int countlines(){
    FILE *fp = fopen("data.txt", "r"); //data.txt 파일을 읽기모드로 열기
    if (fp == NULL) { //파일을 못 열었으면
        printw("Failed to open file\n"); //실패 문구 출력
        return 0;
    }

    int count = 0; 
    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL) { //파일의 모든 줄을 읽을 때까지
        count++; //count 변수 증가
    }
    return count;
}

//연락처 리스트를 출력하는 기능 구현
void list(int linenum) {
    WINDOW *win = newwin(LINES, COLS, 0, 0); //새로운 윈도우 만들기
    FILE *fp = fopen("data.txt", "r"); //data.txt 파일을 읽기모드로 열기
    if (fp == NULL) { //파일을 못 열었으면
        mvwprintw(win, 0, 0,"Failed to open file\n"); //실패 문구 출력
        wrefresh(win); //윈도우 새로고침
        delwin(win); //윈도우 삭제
        return;
    }

    Contact contacts[linenum];
    int count = 0; 
    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL) { //파일의 모든 줄을 읽을 때까지
        sscanf(line, "%29[^:]:%19[^:]:%49[^\n]", contacts[count].name, contacts[count].phone, contacts[count].memo); //이름, 번호, 메모를 분리하여 저장
        count++; //count 변수 증가
    }
    fclose(fp); //파일 닫기

    qsort(contacts, count, sizeof(Contact), compare); //연락처를 이름순으로 정렬

    int per_page = LINES - 2;
    int page = 0;
    int ch;
    do {
        wclear(win); //윈도우 내용 지우기
        box(win, 0, 0); //박스 생성
        for (int i = 0; i < per_page && i + page * per_page < count; i++) { //현재 페이지에 해당하는 연락처를 출력
            mvwprintw(win, i + 1, 1, "Name: %-30s Phone number: %-20s Memo: %-50s", 
                      contacts[i + page * per_page].name[0] ? contacts[i + page * per_page].name : "N/A", 
                      contacts[i + page * per_page].phone[0] ? contacts[i + page * per_page].phone : "N/A", 
                      contacts[i + page * per_page].memo[0] ? contacts[i + page * per_page].memo : "N/A");
                      //문자열이 공백인지 확인하고 공백이면 N/A, 아니면 문자열을 그대로 출력
        }
        mvwprintw(win, LINES - 1, 0, "Page %d/%d. Press n for next page, p for previous page, q to quit.", page + 1, (count + per_page - 1) / per_page); //안내 문구 출력
        wrefresh(win); //윈도우 새로고침

        ch = wgetch(win); //입력 읽기
        switch (ch) { 
            case 'n': //n이 입력되었으면
                if ((page + 1) * per_page < count) //페이지의 끝을 넘어가지 않도록
                    page++; //다음 페이지로 넘기기
                break;
            case 'p': //p가 입력되었으면
                if (page > 0) //페이지의 시작을 넘지 않도록
                    page--; //이전 페이지로 넘기기
                break;
        }
    } while (ch != 'q'); //q가 입력되기 전까지 반복

    wclear(win); //윈도우 내용 삭제
    wrefresh(win); //윈도우 새로고침
    delwin(win); //윈도우 삭제 
}

//연락처 검색 함수의 메뉴를 선택하는 함수
void search_contact(WINDOW *menuwin) {
    refresh(); //menuwin 내용 업데이트
    WINDOW *searchwin = newwin(6, 40, (LINES - 15) / 2, (COLS - 40) / 2); //새로운 윈도우 생성
    box(searchwin, 0, 0); //박스 그리기
    wrefresh(searchwin); //윈도우 새로고침
    keypad(searchwin, true); //키보드 입력 대기
    int select;
    int highlight = 0;
    char *options[4] = {"Search by name", "Search by phone number", "Search by memo", "Back to menu"}; //메뉴 설정
    int exit_loop = 0;

    while (!exit_loop) { //exip_loop가 되기 전까지
        for (int i = 0; i < 4; i++) { //메뉴 출력
            if (i == highlight)
                wattron(searchwin, A_REVERSE); //하이라이트 표시
            mvwprintw(searchwin, i + 1, 1, options[i]);
            wattroff(searchwin, A_REVERSE); //하이라이트 해제
        }
        select = wgetch(searchwin); //입력 읽기

        //사용자 입력 처리
        switch (select) {
            case KEY_UP: 
                highlight--;
                if (highlight < 0)
                    highlight = 3; //범위 초과 시 마지막 항목으로 이동
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight > 3)
                    highlight = 0; //범위 초과 시 첫번째 항목으로 이동
                break;
            case 10: //Enter key가 입력되면 
                if (highlight == 3) {
                    wclear(searchwin); //윈도우 내용 삭제
                    wrefresh(searchwin); //윈도우 새로고침
                    delwin(searchwin); //윈도우 삭제
                    touchwin(menuwin); //윈도우 내용 변경
                    wrefresh(menuwin); //윈도우 새로고침
                    exit_loop = 1; //반복문 종료
                    break;
                }
                wclear(searchwin); //윈도우 내용 삭제
                wrefresh(searchwin); //윈도우 새로고침
                delwin(searchwin); //윈도우 삭제
                switch (highlight) {
                    case 0: //이름으로 찾기를 선택 시 
                        printw("Enter name to search: "); //이름을 입력하라고 출력 
                        refresh(); //새로고침
                        echo(); //사용자가 입력한 문자를 화면에 출력
                        char searchStr1[100];
                        getnstr(searchStr1, sizeof(searchStr1) - 1);
                        searchStr1[strlen(searchStr1)] = '\0';
                        noecho(); //사용자가 입력한 문자를 화면에서 삭제
                        search(searchStr1, 1); //탐색 함수를 시작
                        return;
                    case 1: //번호로 찾기를 선택 시
                        printw("Enter phone number to search: "); //번호를 입력하라고 출력
                        refresh(); //새로고침
                        echo(); //사용자가 입력한 문자를 화면에 출력
                        char searchStr2[100]; 
                        getnstr(searchStr2, sizeof(searchStr2) - 1);
                        searchStr2[strlen(searchStr2)] = '\0';
                        noecho(); //사용자가 입력한 문자를 화면에서 삭제
                        search(searchStr2, 2); //탐색 함수를 시작
                        return;
                    case 2: //메모로 찾기를 선택 시 
                        printw("Enter memo to search: "); //번호를 입력하라고 출력
                        refresh(); //새로고침
                        echo(); //사용자가 입력한 문자를 화면에 출력
                        char searchStr3[100];
                        getnstr(searchStr3, sizeof(searchStr3) - 1);
                        searchStr3[strlen(searchStr3)] = '\0';
                        noecho(); //사용자가 입력한 문자를 화면에서 삭제
                        search(searchStr3, 3); //탐색 함수를 시작
                        return;
                    case 3:
                        return;
                }
                break;
            default:
                break;
        }
    }
}

//연락처 삭제 함수의 메뉴를 선택하는 함수
void delete_contact(WINDOW *menuwin) {
    refresh(); //새로고침
    WINDOW *deletewin = newwin(6, 40, (LINES - 10) / 2, (COLS - 40) / 2); //새로운 윈도우 생성
    box(deletewin, 0, 0); //박스 생성
    wrefresh(deletewin); //윈도우 새로고침
    keypad(deletewin, true); //키보드 입력 대기
    int select;
    int highlight = 0;
    char *options[4] = {"Delete by name", "Delete by phone number", "Delete by memo", "Back to menu"}; //메뉴 설정
    int exit_loop = 0;

    while (!exit_loop) { //exit_loop가 되기 전까지
        for (int i = 0; i < 4; i++) { //메뉴 출력
            if (i == highlight)
                wattron(deletewin, A_REVERSE); //하이라이트 표시
            mvwprintw(deletewin, i + 1, 1, options[i]);
            wattroff(deletewin, A_REVERSE); //하이라이트 삭제
        }
        select = wgetch(deletewin); //입력 받기

        //사용자 읿력 처리
        switch (select) {
            case KEY_UP:
                highlight--;
                if (highlight < 0)
                    highlight = 3; //범위 초과 시 마지막 항목으로 이동
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight > 3)
                    highlight = 0; //범위 초과 시 첫번째 항목으로 이동
                break;
            case 10: //Enter key 입력 시 
                if (highlight == 3) {
                    wclear(deletewin); //윈도우 내용 삭제
                    wrefresh(deletewin); //윈도우 새로고침
                    delwin(deletewin); //윈도우 삭제
                    touchwin(menuwin); //윈도우 내용 업데이트
                    wrefresh(menuwin); //윈도우 새로고침
                    exit_loop = 1; //반복문 종료
                    break;
                }
                wclear(deletewin); //윈도우 내용 삭제
                wrefresh(deletewin); //윈도우 새로고침
                delwin(deletewin); //윈도우 삭제 
                switch (highlight) {
                    case 0: //이름으로 삭제를 선택 시 
                        printw("Enter name to delete: "); //이름을 입력하라고 출력
                        refresh(); //새로고침
                        echo(); //사용자 입력을 화면에 출력
                        char deleteStr1[100];
                        getnstr(deleteStr1, sizeof(deleteStr1) - 1);
                        deleteStr1[strlen(deleteStr1)] = '\0';
                        noecho(); //사용자 입력을 화면에서 삭제
                        delete(deleteStr1, 1); //삭제 함수 실행
                        return;
                    case 1: //전화번호로 삭제를 선택 시
                        printw("Enter phone number to delete: "); //번호를 입력하라고 출력
                        refresh(); //새로고침
                        echo(); //사용자 입력을 화면에 출력
                        char deleteStr2[100];
                        getnstr(deleteStr2, sizeof(deleteStr2) - 1);
                        deleteStr2[strlen(deleteStr2)] = '\0';
                        noecho(); //사용자 입력을 화면에서 삭제
                        delete(deleteStr2, 2); //삭제 함수 실행
                        return;
                    case 2: //메모로 삭제를 선택 시
                        printw("Enter memo to delete: "); //메모를 삭제하라고 출력
                        refresh(); //새로고침
                        echo(); //사용자 입력을 화면에 출력
                        char deleteStr3[100];
                        getnstr(deleteStr3, sizeof(deleteStr3) - 1);
                        deleteStr3[strlen(deleteStr3)] = '\0';
                        noecho(); //사용자 입력을 화면에서 삭제
                        delete(deleteStr3, 3); //삭제 함수를 실행
                        return;
                }
                return;
            default:
                return;
        }
    }
}

//추가 함수를 실행할 때 입력을 처리하는 함수
void get_input(char *prompt, char *buffer, size_t buffer_size) {
    printw("%s", prompt); //prompt를 출력
    refresh(); //새로고침
    echo(); //사용자 입력을 화면에 출력
    getnstr(buffer, buffer_size - 1);
    buffer[strlen(buffer)] = '\0';
    noecho(); //사용자 입력을 화면에서 삭제
    if (strcmp(buffer, "\n") == 0 || buffer[0] == '\0' || buffer[0] == '\n' || buffer[0] == ' ') { //입력이 공백일 경우
        buffer[0] = '\0'; //빈 문자열로 저장
    }
}

//추가 함수를 시작하기 전 필요한 인수를 받는 함수
void add_contact() {
    char addname[100] = "";
    char addphone[100] = "";
    char addmemo[100] = "";

    get_input("Name: ", addname, sizeof(addname)); //이름 입력받기
    get_input("Phone number: ", addphone, sizeof(addphone)); //전화번호 입력받기
    get_input("Memo: ", addmemo, sizeof(addmemo)); //메모 입력받기

    add(addname, addphone, addmemo); //추가 함수 실행
}
