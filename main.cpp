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
    int WordData[10000];
} ExamQueue;

ExamQueue test;

void exam()
{
    test.WordData[1] = 1;
}

char EngS[10000][100]; // �ܾ��� (RAM), �ִ� 1����, ���̴� 100
char KorS[10000][100]; // �ܾ��� (RAM), �ִ� 1����, ���̴� 100

int total; // �� �ܾ��� ����

int compareString(const void *a, const void *b){
    return(strcmp((char*)a,(char*)b));
}

void HanYoungKey(){
    keybd_event(VK_HANGEUL, 0, 0, 0);//����
    keybd_event(VK_HANGEUL, 0, KEYEVENTF_KEYUP, 0);// ���� ����
}

// ���⸦ '_' �� ǥ���� �ؾ���, �ش� �κп� ���� �ַ�� �ʿ�.

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

    printf("���� �ܾ ���ÿ�. (����) : ");
    fgets(Eword, 100, stdin);
    HanYoungKey();
    printf("�� �ܾ��� ���� ���ÿ�. (�ѱ�) : ");
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
    printf("A: Add Word / E: ���� ���� / K: �� ���� / D: ����. (esc�� ����)\n\n");
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
    printf("���� ����ܾ�: %s", EngS[point]);
    printf("���� ���� ��: %s\n", KorS[point]);

    if(mode == 0)
    {
        printf("\'����\' �� �������� �����Ͻðڽ��ϱ�? ('Q' �Է����� ���) : ");
        scanf("%s", word);
        if(word[0]=='Q' && word[1]=='\0') return;
        else
        {
            strcpy(EngS[point], word);
        }
    }
    if(mode == 1)
    {
        printf("\'��\' �� �������� �����Ͻðڽ��ϱ�? ('Q' �Է����� ���) : ");
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
                if(key==224) // ����Ű
                {
                    key=getch();
                    {
                        if(key==72) // ����
                        {
                            if(point>0)
                            {
                                point--;
                                menu(point);
                            }
                        }
                        if(key==80) // �Ʒ���
                        {
                            if(point<total-1)
                            {
                                point++;
                                menu(point);
                            }
                        }
                    }
                }
                if((key==68 || key==100) && total!=0) // D Ű, Delete �۾��� ��
                {
                    delete_word(point);
                    menu(point);
                }
                if(key==65 || key==97) // A Ű, Add �۾��� ��
                {
                    insert_word();
                    menu(point);
                }
                if(key==69 || key==101) // E Ű, English Modify �۾��� ��.
                {
                    modify_word(point, 0);
                    menu(point);
                }
                if(key==75 || key==107) // K Ű, Korean Modify �۾��� ��.
                {
                    modify_word(point, 1);
                    menu(point);
                }
                if(key==27) //esc
                {
                    // ����Ʈ �Ӽ���
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
