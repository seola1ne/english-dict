// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=nyh7105&logNo=221105837718

#include <cstdio>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 100

using namespace std;

char EngS[10000][100]; // �ܾ��� (RAM), �ִ� 1����, ���̴� 100
char KorS[10000][100]; // �ܾ��� (RAM), �ִ� 1����, ���̴� 100
int total; // �� �ܾ��� ����

typedef struct ExamQueue { // ���� �ܾ ������ ť
    int front; // ���� ��ġ�� ����Ŵ
    int rear; // ���� ��ġ�� ����Ŵ
    int WordData[10000]; // ������ ���� �ܾ��� ��ġ�� ������ �迭
} ExamQueue;

void initQueue(ExamQueue*);
void ExamSetting();
void StartExam(ExamQueue*);

void initQueue(ExamQueue* test) { // ť �ʱ�ȭ
    test->front = -1;
    test->rear = -1;
}

void ExamSetting() { // ť �ʱ� ����
    ExamQueue test;
    initQueue(&test);

    bool entered[10000];

    for(int i = 0; i < total; i++) {
        int n=rand() % total;
        if(!entered[n])
        {
            test.WordData[i] = n; // ���� �ܾ� �迭�� �ε����� �������� ��� ť�� WordData �迭�� ����
            entered[n]=true;
        }
    }

    test.rear = total-1;

    StartExam(&test);
}

void StartExam(ExamQueue* test) {

    system("cls");

    int i = 0;
    int WordIndex; // ������ �� �ܾ��� �ε����� �����ϴ� ����
    char userAnswer[100]; // ����ڰ� ���� ���� ������ ���ڿ�
    int wrongCount = 0;

    while(test->front != test->rear) { // WordData �迭�� ������ �ƴ� ����gggggggggggggggSSSsSs
        }

        else { // ������ �ƴϸ�
            printf("\n����!\n\n���� : %s", EngS[WordIndex]);
            Sleep(1500);

            test->WordData[test->rear+1] = WordIndex; // Ʋ�� �ܾ� �ε����� WordData �迭�� �������� ����
            test->rear += 1;

            test->front++; // �ش� �ܾ� �ǳʶ�(�տ��� ����)
            wrongCount++; // Ʋ�� Ƚ�� �߰�
        }
    }

    printf("�� Ʋ�� Ƚ���� %d���Դϴ�. \n\n(�ƹ�Ű�� ���� ���ư���)", wrongCount);

    getch();
}


int isFull(ExamQueue *test) { // ť ��ȭ ���� �Ǵ�
    return test->rear == total-1;
}

int isEmpty(ExamQueue *test) { // ť ���� ���� �Ǵ�
    return test->rear == test->front;
}

int compareString(const void *a, const void *b){
    return(strcmp((char*)a,(char*)b));
}

void HanYoungKey(){
    keybd_event(VK_HANGEUL, 0, 0, 0);//����
    keybd_event(VK_HANGEUL, 0, KEYEVENTF_KEYUP, 0);// ���� ����
}

void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
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

    printf("���� �ܾ ���ÿ�. (����) : ");
    fgets(Eword, 100, stdin);
    HanYoungKey();
    printf("�� �ܾ��� ���� ���ÿ�. (�ѱ�) : ");
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
    printf("A: Add Word / E: ���� ���� / K: �� ���� / D: ����. (esc�� ����)\n\n");

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
    printf("���� ����ܾ�: %s", EngS[point]);
    printf("���� ���� ��: %s\n", KorS[point]);

    char korbuffer[100];

    strcpy(korbuffer, KorS[point]);

    if(mode == 0)
    {
        printf("\'����\' �� �������� �����Ͻðڽ��ϱ�? ('Q' �Է����� ���) : ");
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
        printf("\'��\' �� �������� �����Ͻðڽ��ϱ�? ('Q' �Է����� ���) : ");
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
                if(key==224) // ����Ű
                {
                    key=getch();
                    {
                        if(key==72) // ����
                        {
                            if(point>0)
                            {
                                point--;
                            }
                        }
                        if(key==80) // �Ʒ���
                        {
                            if(point<total-1)
                            {
                                point++;
                            }
                        }
                    }
                }
                if((key==68 || key==100) && total!=0) // D Ű, Delete �۾��� ��
                {
                    delete_word(point);
                }
                if(key==65 || key==97) // A Ű, Add �۾��� ��
                {
                    insert_word();
                }
                if(key==69 || key==101) // E Ű, English Modify �۾��� ��.
                {
                    modify_word(point, 0);
                }
                if(key==75 || key==107) // K Ű, Korean Modify �۾��� ��.
                {
                    modify_word(point, 1);
                }
                if(key==27) //esc
                {
                    // ����Ʈ �Ӽ���
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
    printf("�ܾ� ����");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    gotoxy(x+16, y);
    if(point==1) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("�׽�Ʈ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    gotoxy(x+30, y);
    if(point==2) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("����");
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
                if(key==224) // ����Ű
                {
                    key=getch();
                    {
                        if(key==75) // ����
                        {
                            if(point>0)
                            {
                                point--;
                            }
                        }
                        if(key==77) // ������
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
