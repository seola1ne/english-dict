// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=nyh7105&logNo=221105837718

#include <cstdio>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 100

using namespace std;

char EngS[10000][100]; // 단어장 (RAM), 최대 1만개, 길이는 100
char KorS[10000][100]; // 단어장 (RAM), 최대 1만개, 길이는 100
int total; // 총 단어의 개수

typedef struct ExamQueue { // 시험 단어를 저장할 큐
    int front; // 삭제 위치를 가리킴
    int rear; // 삽입 위치를 가리킴
    int WordData[10000]; // 출제할 영어 단어의 위치를 저장할 배열
} ExamQueue;

void initQueue(ExamQueue*);
void ExamSetting();
void StartExam(ExamQueue*);

void initQueue(ExamQueue* test) { // 큐 초기화
    test->front = -1;
    test->rear = -1;
}

void ExamSetting() { // 큐 초기 세팅
    ExamQueue test;
    initQueue(&test);

    bool entered[10000];

    for(int i = 0; i < total; i++) {
        int n=rand() % total;
        if(!entered[n])
        {
            test.WordData[i] = n; // 영어 단어 배열의 인덱스를 랜덤으로 섞어서 큐의 WordData 배열에 저장
            entered[n]=true;
        }
    }

    test.rear = total-1;

    StartExam(&test);
}

void StartExam(ExamQueue* test) {

    system("cls");

    int i = 0;
    int WordIndex; // 문제를 낼 단어의 인덱스를 저장하는 변수
    char userAnswer[100]; // 사용자가 적은 답을 저장할 문자열
    int wrongCount = 0;

    while(test->front != test->rear) { // WordData 배열이 공백이 아닐 동안gggggggggggggggSSSsSs
        }

        else { // 정답이 아니면
            printf("\n오답!\n\n정답 : %s", EngS[WordIndex]);
            Sleep(1500);

            test->WordData[test->rear+1] = WordIndex; // 틀린 단어 인덱스를 WordData 배열의 마지막에 삽입
            test->rear += 1;

            test->front++; // 해당 단어 건너뜀(앞에서 삭제)
            wrongCount++; // 틀린 횟수 추가
        }
    }

    printf("총 틀린 횟수는 %d번입니다. \n\n(아무키를 눌러 돌아가기)", wrongCount);

    getch();
}


int isFull(ExamQueue *test) { // 큐 포화 여부 판단
    return test->rear == total-1;
}

int isEmpty(ExamQueue *test) { // 큐 공백 여부 판단
    return test->rear == test->front;
}

int compareString(const void *a, const void *b){
    return(strcmp((char*)a,(char*)b));
}

void HanYoungKey(){
    keybd_event(VK_HANGEUL, 0, 0, 0);//누름
    keybd_event(VK_HANGEUL, 0, KEYEVENTF_KEYUP, 0);// 누름 해제
}

void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

// 띄어쓰기를 '_' 로 표현을 해야함, 해당 부분에 대한 솔루션 필요.

void save()
{
    FILE *fp;

    fp = fopen("EngWord.txt", "w");
    for(int i=0; i<total; i++)
    {
        fputs(EngS[i], fp);
    }

    fclose(fp);

    fp = fopen("KorWord.txt", "w");
    for(int i=0; i<total; i++)
    {
        fputs(KorS[i], fp);
    }
    fclose(fp);
}

void load()
{
    FILE *fp;
    fp = fopen("EngWord.txt", "r");

    char buffer[100]={};
    int cnt = 0;

    while(feof(fp)==0)
    {
        fgets(buffer, MAX, fp);
        strcpy(EngS[cnt], buffer);
        cnt++;
    }
    fclose(fp);

    cnt = 0;
    fp = fopen("KorWord.txt", "r");

    while(feof(fp)==0)
    {
        fgets(buffer, MAX, fp);
        strcpy(KorS[cnt], buffer);
        cnt++;
    }
    fclose(fp);

    total = cnt-1;
}

void insert_word()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    system("cls");
    char Eword[100];
    char Kword[100];

    printf("넣을 단어를 쓰시오. (영어) : ");
    fgets(Eword, 100, stdin);
    HanYoungKey();
    printf("이 단어의 뜻을 쓰시오. (한글) : ");
    fgets(Kword, 100, stdin);

    int where=0;

    strcpy(EngS[total], Eword);
    total++;

    char buffer[100];

    strcpy(buffer, Eword);
    qsort((void *)EngS, total, sizeof(EngS[0]), compareString);

    for(int i=0; i<total; i++)
    {
        if(strcmp(EngS[i], buffer)==0)
        {
            where=i;
            for(int j=total-1; j>where; j--)
            {
                strcpy(KorS[j], KorS[j-1]);
            }
            break;
        }
    }

    strcpy(KorS[where], Kword);

    system("cls");
    HanYoungKey();
    save();
}

void dictionary_menu(int point)
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("A: Add Word / E: 영어 수정 / K: 뜻 수정 / D: 삭제. (esc로 종료)\n\n");

    int start = point>=4 ? point-4:0;
    for(int i=start; i<start+5; i++)
    {
        if(i>=total) break;
        if(i==point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        printf("%s%s\n", EngS[i], KorS[i]);
    }
    save();
}

void delete_word(int point)
{
    for(int i=point; i<total; i++)
    {
        strcpy(EngS[i], EngS[i+1]);
        strcpy(KorS[i], KorS[i+1]);
        total--;
        point--;
    }
}

void modify_word(int point, int mode)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    char word[100];
    system("cls");
    printf("기존 영어단어: %s", EngS[point]);
    printf("기존 영어 뜻: %s\n", KorS[point]);

    char korbuffer[100];

    strcpy(korbuffer, KorS[point]);

    if(mode == 0)
    {
        printf("\'영어\' 를 무엇으로 변경하시겠습니까? ('Q' 입력으로 취소) : ");
        fgets(word, 100, stdin);
        if(word[0]=='Q' && word[1]=='\n') return;
        else
        {
            int where;

            strcpy(EngS[point], word);

            qsort((void *)EngS, total, sizeof(EngS[0]), compareString);

            for(int i=0; i<total; i++)
            {
                if(strcmp(EngS[i], word)==0)
                {
                    where=i;
                    for(int j=total-1; j>where; j--)
                    {
                        strcpy(KorS[j], KorS[j-1]);
                    }
                    break;
                }
            }

        strcpy(KorS[where], korbuffer);

        system("cls");
        }
    }
    if(mode == 1)
    {
        HanYoungKey();
        printf("\'뜻\' 을 무엇으로 변경하시겠습니까? ('Q' 입력으로 취소) : ");
        fgets(word, 100, stdin);
        if(word[0]=='Q' && word[1]=='\n') return;
        else
        {
            strcpy(KorS[point], word);
        }
        HanYoungKey();
    }
}

void dictionary_mainmenu()
{
    system("cls");
    int point = 0;
    dictionary_menu(point);

    while(1)
    {
        int key;
        if(kbhit())
        {
            key=getch();
            {
                if(key==224) // 방향키
                {
                    key=getch();
                    {
                        if(key==72) // 위쪽
                        {
                            if(point>0)
                            {
                                point--;
                            }
                        }
                        if(key==80) // 아래쪽
                        {
                            if(point<total-1)
                            {
                                point++;
                            }
                        }
                    }
                }
                if((key==68 || key==100) && total!=0) // D 키, Delete 작업을 함
                {
                    delete_word(point);
                }
                if(key==65 || key==97) // A 키, Add 작업을 함
                {
                    insert_word();
                }
                if(key==69 || key==101) // E 키, English Modify 작업을 함.
                {
                    modify_word(point, 0);
                }
                if(key==75 || key==107) // K 키, Korean Modify 작업을 함.
                {
                    modify_word(point, 1);
                }
                if(key==27) //esc
                {
                    // 포인트 속성값
                    break;
                }
            }
            dictionary_menu(point);
        }
    }

    system("cls");

}

void titledraw(int point)
{
    system("cls");

    printf("\n\n\n\n");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("                      C");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("LASS ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("C");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("ARD     \n\n\n");

    printf("   -------------------------------------------------\n\n");

    int x = 8, y = 10;

    gotoxy(x, y);
    if(point==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("단어 사전");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    gotoxy(x+16, y);
    if(point==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("테스트");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    gotoxy(x+30, y);
    if(point==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("종료");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void mainmenu()
{
    int point = 0;

    titledraw(point);

    while(1)
    {
        int key;
        if(kbhit())
        {
            key=getch();
            {
                if(key==224) // 방향키
                {
                    key=getch();
                    {
                        if(key==75) // 왼쪽
                        {
                            if(point>0)
                            {
                                point--;
                            }
                        }
                        if(key==77) // 오른쪽
                        {
                            if(point<2)
                            {
                                point++;
                            }
                        }
                    }
                }
                if(key==13)
                {
                    if(point==0) dictionary_mainmenu();
                    if(point==1) ExamSetting();
                    if(point==2) break;
                }
            }

            titledraw(point);
        }
    }

    system("cls");
}


int main()
{
    load();
    mainmenu();
}
