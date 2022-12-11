// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=nyh7105&logNo=221105837718

#include <cstdio>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 100

using namespace std;

typedef struct ExamQueue {
    int front;
    int rear;

} ExamQueue;

char EngS[10000][100]; // 단어장 (RAM), 최대 1만개, 길이는 100
char KorS[10000][100]; // 단어장 (RAM), 최대 1만개, 길이는 100

int total; // 총 단어의 개수

int compareString(const void *a, const void *b){
    return(strcmp((char*)a,(char*)b));
}

void HanYoungKey(){
    keybd_event(VK_HANGEUL, 0, 0, 0);//누름
    keybd_event(VK_HANGEUL, 0, KEYEVENTF_KEYUP, 0);// 누름 해제
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
    char trash;

    printf("넣을 단어를 쓰시오. (영어) : ");
    fgets(Eword, 100, stdin);
    HanYoungKey();
    printf("이 단어의 뜻을 쓰시오. (한글) : ");
    fgets(Kword, 100, stdin);


    strcpy(EngS[total], Eword);
    strcpy(KorS[total], Kword);
    total++;

    system("cls");
    HanYoungKey();
    save();
}

void menu(int point)
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    printf("A: Add Word / E: 영어 수정 / K: 뜻 수정 / D: 삭제. (esc로 종료)\n\n");
    for(int i=0; i<total; i++)
    {
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

    if(mode == 0)
    {
        printf("\'영어\' 를 무엇으로 변경하시겠습니까? ('Q' 입력으로 취소) : ");
        scanf("%s", word);
        if(word[0]=='Q' && word[1]=='\0') return;
        else
        {
            strcpy(EngS[point], word);
        }
    }
    if(mode == 1)
    {
        printf("\'뜻\' 을 무엇으로 변경하시겠습니까? ('Q' 입력으로 취소) : ");
        scanf("%s", word);
        if(word[0]=='Q' && word[1]=='\0') return;
        else
        {
            strcpy(KorS[point], word);
        }
    }
}

void mainmenu()
{
    int point = 0;
    menu(point);

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
                                menu(point);
                            }
                        }
                        if(key==80) // 아래쪽
                        {
                            if(point<total-1)
                            {
                                point++;
                                menu(point);
                            }
                        }
                    }
                }
                if((key==68 || key==100) && total!=0) // D 키, Delete 작업을 함
                {
                    delete_word(point);
                    menu(point);
                }
                if(key==65 || key==97) // A 키, Add 작업을 함
                {
                    insert_word();
                    menu(point);
                }
                if(key==69 || key==101) // E 키, English Modify 작업을 함.
                {
                    modify_word(point, 0);
                    menu(point);
                }
                if(key==75 || key==107) // K 키, Korean Modify 작업을 함.
                {
                    modify_word(point, 1);
                    menu(point);
                }
                if(key==27) //esc
                {
                    // 포인트 속성값
                    break;
                }
            }
        }
    }

    system("cls");

}

int main()
{
    load();
    mainmenu();

}
