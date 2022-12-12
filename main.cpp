// https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=nyh7105&logNo=221105837718

#include <cstdio>
#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 100
<<<<<<< HEAD
#define MaxSize 10000

using namespace std;

=======

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

>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
char EngS[10000][100]; // �ܾ��� (RAM), �ִ� 1����, ���̴� 100
char KorS[10000][100]; // �ܾ��� (RAM), �ִ� 1����, ���̴� 100

int total; // �� �ܾ��� ����

<<<<<<< HEAD
// -------- ���� �ܾ� ���� ť ���� ---------

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

    for(int i = 0; i < total; i++) {
        test.WordData[i] = (rand() % total) + i; // ���� �ܾ� �迭�� �ε����� �������� ��� ť�� WordData �迭�� ����
    }

    test.rear = total-1;

    StartExam(&test);
}

void StartExam(ExamQueue* test) {
    int i = 0;
    int WordIndex; // ������ �� �ܾ��� �ε����� �����ϴ� ����
    char userAnswer[100]; // ����ڰ� ���� ���� ������ ���ڿ�
    int wrongCount = 0;

    while(test->front != test->rear) { // WordData �迭�� ������ �ƴ� ����
        WordIndex = test->WordData[i]; // ������ �� �ܾ� �ε����� test->WordData �迭�� i��° ������ ����

        printf("%d��° �ܾ� : %s\n", i++, KorS[WordIndex]);
        printf("�ش� �ܾ ����� �ϸ� ? : ");
        fgets(userAnswer, 100, stdin);

        if(strcmp(userAnswer, EngS[WordIndex]) == 0) { // ����� ��� ���� ��
            printf("\n����!\n\n");
            test->front++; // ���� �ܾ�� ����
        }

        else { // ������ �ƴϸ�
            printf("\n����!\n\n");

            test->WordData[test->rear+1] = WordIndex; // Ʋ�� �ܾ� �ε����� WordData �迭�� �������� ����
            test->rear += 1;

            test->front++; // �ش� �ܾ� �ǳʶ�(�տ��� ����)
            wrongCount++; // Ʋ�� Ƚ�� �߰�
        }
    }

    printf("�� Ʋ�� Ƚ���� %d���Դϴ�. \n", wrongCount);
}


/*
int isFull(ExamQueue *test) { // ť ��ȭ ���� �Ǵ�
    return test->rear == MaxSize-1;
}

int isEmpty(ExamQueue *test) { // ť ���� ���� �Ǵ�
    return test->rear == test->front;
}
*/

// ------------------------------

=======
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
int compareString(const void *a, const void *b){
    return(strcmp((char*)a,(char*)b));
}

void HanYoungKey(){
    keybd_event(VK_HANGEUL, 0, 0, 0);//����
    keybd_event(VK_HANGEUL, 0, KEYEVENTF_KEYUP, 0);// ���� ����
}

<<<<<<< HEAD
void gotoxy(int x, int y) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consoleHandle, pos);
}

=======
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
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

<<<<<<< HEAD
void dictionary_menu(int point)
=======
void menu(int point)
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
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
<<<<<<< HEAD
        fgets(word, 100, stdin);
        if(word[0]=='Q' && word[1]=='\n') return;
=======
        scanf("%s", word);
        if(word[0]=='Q' && word[1]=='\0') return;
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
        else
        {
            strcpy(EngS[point], word);
        }
    }
    if(mode == 1)
    {
        printf("\'��\' �� �������� �����Ͻðڽ��ϱ�? ('Q' �Է����� ���) : ");
<<<<<<< HEAD
        fgets(word, 100, stdin);
        if(word[0]=='Q' && word[1]=='\n') return;
=======
        scanf("%s", word);
        if(word[0]=='Q' && word[1]=='\0') return;
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
        else
        {
            strcpy(KorS[point], word);
        }
    }
}

<<<<<<< HEAD
void dictionary_mainmenu()
{
    system("cls");
    int point = 0;
    dictionary_menu(point);
=======
void mainmenu()
{
    int point = 0;
    menu(point);
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140

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
<<<<<<< HEAD
=======
                                menu(point);
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
                            }
                        }
                        if(key==80) // �Ʒ���
                        {
                            if(point<total-1)
                            {
                                point++;
<<<<<<< HEAD
=======
                                menu(point);
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
                            }
                        }
                    }
                }
                if((key==68 || key==100) && total!=0) // D Ű, Delete �۾��� ��
                {
                    delete_word(point);
<<<<<<< HEAD
=======
                    menu(point);
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
                }
                if(key==65 || key==97) // A Ű, Add �۾��� ��
                {
                    insert_word();
<<<<<<< HEAD
=======
                    menu(point);
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
                }
                if(key==69 || key==101) // E Ű, English Modify �۾��� ��.
                {
                    modify_word(point, 0);
<<<<<<< HEAD
=======
                    menu(point);
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
                }
                if(key==75 || key==107) // K Ű, Korean Modify �۾��� ��.
                {
                    modify_word(point, 1);
<<<<<<< HEAD
=======
                    menu(point);
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
                }
                if(key==27) //esc
                {
                    // ����Ʈ �Ӽ���
                    break;
                }
            }
<<<<<<< HEAD
            dictionary_menu(point);
=======
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
        }
    }

    system("cls");

}

<<<<<<< HEAD
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


=======
>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
int main()
{
    load();
    mainmenu();
<<<<<<< HEAD
=======

>>>>>>> 25e568fe7fe6145e0710f01a6b435bfd5d75f140
}
