#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>


#define length 1000   /// ��Ϸ����
#define high 640
#define fishnum 9      ///��Ϸ�������
#define changenum 12      ///���ͼ�β�����̬Ч��������
#define boomnum 2          ///ը������
#define alarmnum 2      ///��������

PIMAGE enter, enterchange[3], background, player[changenum];
PIMAGE numfish[fishnum], boom[boomnum], alarm[alarmnum];
PIMAGE pao, wancheng;
PIMAGE background2, background3, gameover;

typedef struct games
{
    double position_x;   ///������
    double position_y;    ///������
    double v_x;      ///ˮƽ�ٶ�
    double v_y;      ///��ֱ�ٶ�
} yu;


yu players;///���
yu timer;///����
yu zhadan;///���ը��
yu food1;///��ת1����
yu food2;///2����
yu food3;///3����
yu food4;///4����
yu food5;///5����
yu food6;///6����
yu food7;///7�ź�����
yu food8;///��ת1����
yu paopao;///����


int yuturn = 0;             ///�ж����Ƿ��ͷ   1  ��ͷ��   0 ����ͷ��
int backchange = 0;              ///�жϱ����Ƿ�任            0 Ϊ��ʼ�˵�ҳ�� 1Ϊ�˵�1 2Ϊ�˵�2
int goback = 0;            ///�˵�ҳ��ص���ʼ                0Ϊ��ʼ�˵�ҳ��   1Ϊ�˵�1    2Ϊ�˵�2

double p1size;             ///������ߴ�
double start_p1size;      ///������ĳ�ʼ��С
int alive = 3;            ///�������
int gamestatus = 0;       ///��Ϸ״̬�� 0 Ϊ������Ϸ��1 Ϊ������Ϸ״̬��2 Ϊ��Ϸ��ͣ
double starttime;              ///��ʱ
double endtime;                ///��ʱ
double timelong = 150.0;       ///��Ϸʱ������
double resttime;          ///��Ϸʣ��ʱ��
int  socre_p1 = 0;         ///��Ϸ����
int flag = 0;                        ///������¼�����λ��
char remake;              ///��Ϸ�ؿ�


void playmusic();
void every_data();
void formbackground();
void initdata1();
void data_withoutinput();
void data_withinput();
void background_over();
void game_over();
void background_1();
void background_2();


void playmusic()             ///�������ļ���
{
    mciSendString(TEXT("open backmusic\\bit.mp3"), NULL, 0, NULL);                    ///���ظ�����
    mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music1.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music3.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\huankuai.mp3"),NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\baozha.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music5.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("opne backmusic\\music6.mp3"), NULL, 0, NULL);
}

void every_data()            ///��ʼ����
{
    wancheng = newimage();
    enter = newimage();
    background = newimage();
    background2 = newimage();
    background3 = newimage();
    pao = newimage();
    gameover = newimage();
    for(int i = 0; i < 3; i++)
        enterchange[i] = newimage();
    for(int i = 0; i < changenum; i++)
        player[i] = newimage();
    for(int i = 0; i < fishnum; i++)
        numfish[i] = newimage();
    for(int i = 0; i < boomnum; i++)
        boom[i] = newimage();
    for(int i = 0; i< alarmnum; i++)
        alarm[i] = newimage();

    getimage(enter, "yupic\\background1.png");    ///����ҳ��
    getimage(background2, "yupic\\background3.png");   ///�˵�1ҳ��
    getimage(background3, "yupic\\background4.png");   ///�˵�2ҳ��

    getimage(wancheng, "yupic\\wancheng.png");
    getimage(gameover, "yupic\\gameover.png");       ///��Ϸ����ҳ��

    getimage(enterchange[0], "yupic\\tietu22.png");      ///���ͣ����������ط�ͼƬ�仯
    getimage(enterchange[1], "yupic\\tietu33.png");
    getimage(enterchange[2], "yupic\\tietu44.png");

    getimage(background, "yupic\\background.png");        ///��Ϸ����
    getimage(pao, "yupic\\paopao.png");                    ///��������

    getimage(player[0], "yupic\\players11.png");                  ///���1��תͼ
    getimage(player[1], "yupic\\players22.png");                  ///���2
    getimage(player[2], "yupic\\players33.png");                  ///���3
    getimage(player[3], "yupic\\players44.png");                  ///���4
    getimage(player[4], "yupic\\players55.png");                  ///���5
    getimage(player[5], "yupic\\players66.png");                  ///���6

    getimage(player[6], "yupic\\players1.png");                  ///���1��תͼ
    getimage(player[7], "yupic\\players2.png");                  ///���2
    getimage(player[8], "yupic\\players3.png");                  ///���3
    getimage(player[9], "yupic\\players4.png");                  ///���4
    getimage(player[10], "yupic\\players5.png");                  ///���5
    getimage(player[11], "yupic\\players6.png");                  ///���6


    getimage(numfish[0], "yupic\\oneyu2.png");   ///��תһ����

    getimage(numfish[7], "yupic\\oneyu1.png");    ///��תһ����

    getimage(numfish[1], "yupic\\twoyu1.png");   ///��ת������

    getimage(numfish[2], "yupic\\threeyu1.png");  ///��ת������

    getimage(numfish[3], "yupic\\fouryu1.png");   ///��ת�ĺ���

    getimage(numfish[4], "yupic\\fiveyu11.png");   ///��ת�����

    getimage(numfish[5], "yupic\\sixyu.png");        ///��ת������

    getimage(numfish[6], "yupic\\sevenyu.png");       ///��ת�ߺź���

    getimage(alarm[0], "yupic\\naozhong.png");     ///����
    getimage(boom[0], "yupic\\zhadan.png");        ///ը��


    p1size = 60;                      ///��ߴ�
    start_p1size = p1size;             ///���ʼ�ߴ�,��ֵ��ţ���ֹ�´α�ֵ

    starttime = fclock();

    players.position_x = length/2.0;   ///�������
    players.position_y = high/2.0;
    players.v_x = 0.77;              ///����ٶ�
    players.v_y = 0.77;

    paopao.position_x = players.position_x;    ///��������Ϊ�������
    paopao.position_y = players.position_y;
    paopao.v_y = 0.2;                          ///���������ٶ�

    food1.position_x = 0;           ///��ת1���������
    food1.position_y = rand() % 400;    ///��ת1��������������趨
    food1.v_x = 0.5;                  ///��ת1�����ٶ�

    food8.position_x = 1000;           ///��ת1���������
    food8.position_y = rand() % 400;    ///��ת1��������������趨
    food8.v_x = 0.5;                  ///��ת1�����ٶ�

    food2.position_x = 1200;        ///����������
    food2.position_y = rand() % 400;
    food2.v_x =0.4;

    food3.position_x = 1300;            ///����������
    food3.position_y = rand() % 400;
    food3.v_x = 0.35;

    food4.position_x = 1500;             ///�ĺ���
    food4.position_y = rand() % 400;
    food4.v_x = 0.4;

    food5.position_x = 3000;            ///�����
    food5.position_y = rand() % 400;
    food5.v_x = 0.6;

    food6.position_x = -1500;          ///������
    food6.position_y = rand() % 500;
    food6.v_x = 0.4;

    food7.position_x = -500;
    food7.position_y = rand() % 500;      ///�ߺź�����
    food7.v_x = 0.3;

    timer.position_x = -2000;     ///���Ӻ�����  ///�����������
    timer.position_y = rand() % 600; ///��������������趨
    timer.v_x = 0.5;    ///�����ٶ�

    zhadan.position_x = -500; ///ը��������
    zhadan.position_y = rand() % 400;
    zhadan.v_x = 0.3;



}

void formbackground()   ///����ҳ��
{

    mouse_msg lick = {0};
    while(1)
    {
        putimage(0, 0, enter);                   ///����ҳ��
        while(mousemsg())
        {
            lick = getmouse();
            if(lick.x >= 404 && lick.x <= 622 && lick.y >= 179 && lick.y <= 266)        ///��ȡ�����λ��
            {
                if(lick.is_down())
                {
                    putimage(622, 180, enterchange[2]);                           ///������ͼ��仯
                    Sleep(300);
                    flag = 1;
                }
                if(lick.is_up())
                {
                    backchange = 0;
                    flag = 2;
                }
            }
            else if(lick.x >= 404 && lick.x <= 622 && lick.y >= 299 && lick.y <= 385)
            {
                if(lick.is_down())
                {
                    putimage(309, 300, enterchange[1]);
                    Sleep(300);
                    flag = 3;
                }
                if(lick.is_up())
                {
                    backchange = 1;                ///����˵���������
                    goback = 1;
                    flag = 4;
                }
            }
            else if(lick.x >= 404 && lick.x <= 622 && lick.y >= 424 && lick.y <= 500)
            {
                if(lick.is_down())
                {
                    putimage(622, 420, enterchange[0]);
                    Sleep(300);
                    flag = 5;
                }
                if(lick.is_up())
                {
                    backchange = 2;                ///��Ϸ���ܱ������
                    goback = 2;
                    flag = 6;
                }
            }

        }
        if(flag == 2)
            break;
        if(flag == 4)
            break;
        if(flag == 6)
            break;
    }
}

void background_1()
{
        putimage(0, 0, background2);                   ///����˵��ҳ��

        setbkmode(TRANSPARENT);
        setcolor(RED);
        setfont(50, 0, "����");
        xyprintf(320, 40, "�� Ϸ �� �� ˵ ��");
        setcolor(GREEN);
        setfont(30, 0, "����");
        xyprintf(380, 180, "�� �� �� �� ����С���ƶ�");
        xyprintf(290, 280, "��P����ʹ��Ϸ��ͣ, ������Ϸ��Esc��");
        setcolor(RED);
        setfont(30, 0, "����");
        xyprintf(220, 400, "���ز˵�");
        xyprintf(760, 400, "������Ϸ");
        Sleep(1);

        mouse_msg lick_put = {0};                                  ///��ȡ�˵�ҳ1���������Ϣ
        while(1)
        {
            while(mousemsg())
         {
            lick_put = getmouse();
        if(lick_put.x >= 222 && lick_put.x <= 337 && lick_put.y >= 407 && lick_put.y <= 429)
        {
            if(lick_put.is_down())
            {
               goback = 1;
            }
            if(lick_put.is_down())
            {
                backchange = 0;
                goback = 0;
            }
        }
        else if(lick_put.x >= 762 && lick_put.x <= 878 && lick_put.y >= 407 && lick_put.y <= 429)
        {
            if(lick_put.is_down())
            {
                flag = 1;
            }
            if(lick_put.is_up())
            {
                flag = 2;
            }
        }
         }
        if((backchange == 0 && goback == 0) || flag == 2)
            break;
        }
}

void background_2()
{
        putimage(0, 0, background3);                ///��Ϸ���ܱ���ҳ��

        setbkmode(TRANSPARENT);
        setcolor(RED);
        setfont(50, 0, "����");
        xyprintf(320, 40, "�� Ϸ �� �� ˵ ��");
        setcolor(GREEN);
        setfont(30, 0, "����");
        xyprintf(380, 180, "�� �� �� �� ����С���ƶ�");
        xyprintf(290, 280, "��P����ʹ��Ϸ��ͣ, ������Ϸ��Esc��");
        xyprintf(500, 400, "���ز˵�");
        Sleep(1);

        mouse_msg lick_an = {0};
        while(1)
        {
            while(mousemsg())
            {
                lick_an = getmouse();
                if(lick_an.x >= 222 && lick_an.x <= 337 && lick_an.y >= 407 && lick_an.y <= 429)
                {
                    if(lick_an.is_down())
                    {
                        goback = 2;
                    }
                    if(lick_an.is_up())
                    {
                        goback = 0;
                        backchange = 0;
                    }
                }
            }
            if(backchange == 0 && goback == 0)
                break;
        }

}

void initdata1()    ///���±���
{
    mciSendString(TEXT("close backmusic\\music5.mp3"), NULL, 0, NULL);              ///���Ų˵�ҳ������3
    mciSendString(TEXT("close backmusic\\music1.mp3"), NULL, 0, NULL);              ///���Ų˵�ҳ������2
    mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///�رղ˵�ҳ������1
    mciSendString(TEXT("play backmusic\\huankuai.mp3 repeat"), NULL, 0, NULL);              ///���Ž�����Ϸҳ������4

    endtime = fclock();
    resttime = timelong - (endtime - starttime)/1000.0;
    if(backchange == 0)
    putimage(0, 0, background);                          ///��Ϸ����

    setbkmode(TRANSPARENT);                         ///��Ϸ����
    setcolor(RED);                                   ///������ɫ
    setfont(25, 0, "����");                          ///�����С������

    xyprintf(65, 10, "Score");
    xyprintf(80, 45, "%d", socre_p1);              ///����

    xyprintf(415, 10, "resttime");                 ///ʣ��ʱ��
    xyprintf(415, 45, "%d", resttime);

    xyprintf(750, 10, "The remaining life");
    xyprintf(860, 45, "%d", alive);                  ///����

    putimage(food1.position_x, food1.position_y, numfish[0], SRCAND);   ///����תһ������ʾ����
    putimage(food8.position_x, food8.position_y, numfish[7], SRCAND);   ///��תһ�����ӡ
    putimage(food2.position_x, food2.position_y, numfish[1], SRCAND);     ///������
    putimage(food3.position_x, food3.position_y, numfish[2], SRCAND);     ///������
    putimage(food4.position_x, food4.position_y, numfish[3], SRCAND);     ///�ĺ���
    putimage(food5.position_x, food5.position_y, numfish[4], SRCAND);     ///�����
    putimage(food6.position_x, food6.position_y, numfish[5], SRCAND);             ///������
    putimage(food7.position_x, food7.position_y, numfish[6], SRCAND);             ///�ߺ���
    putimage(zhadan.position_x, zhadan.position_y, boom[0], SRCAND);      ///ը��
    putimage(timer.position_x, timer.position_y, alarm[0], SRCAND);       ///����

    putimage(paopao.position_x, paopao.position_y , pao, SRCAND);         ///�µ�����
    putimage(paopao.position_x, paopao.position_y - 30, pao, SRCAND);
}


void initdata2()    ///�����㣨��̬ת����(ʹ������ʱ����ʾ�ĸ�����ʵ��
{
    if(yuturn == 0)                       ///��������仯
    {
        if(p1size < 65)
            putimage(players.position_x, players.position_y, player[0], SRCAND);
        else if(p1size >= 65 && p1size <75)
            putimage(players.position_x, players.position_y, player[1], SRCAND);
        else if(p1size >= 75 && p1size < 90)
            putimage(players.position_x, players.position_y, player[2], SRCAND);
        else if(p1size >= 90 && p1size < 105)
            putimage(players.position_x, players.position_y, player[3], SRCAND);
        else if(p1size >= 105 && p1size < 135)
            putimage(players.position_x, players.position_y, player[4], SRCAND);
        else if(p1size >= 135)
            putimage(players.position_x, players.position_y, player[5], SRCAND);
    }

    else
    {
        if(p1size < 65)
            putimage(players.position_x, players.position_y, player[6], SRCAND);
        else if(p1size >= 65 && p1size <75)
            putimage(players.position_x, players.position_y, player[7], SRCAND);
        else if(p1size >= 75 && p1size < 90)
            putimage(players.position_x, players.position_y, player[8], SRCAND);
        else if(p1size >= 90 && p1size < 105)
            putimage(players.position_x, players.position_y, player[9], SRCAND);
        else if(p1size >= 105 && p1size < 135)
            putimage(players.position_x, players.position_y, player[10], SRCAND);
        else if(p1size >=135)
            putimage(players.position_x, players.position_y, player[11], SRCAND);
    }

    char input_1;
    if(kbhit())                                            ///��Ϸ��ͣ����
    {
        input_1 = getch();
        if(input_1 == 'p' || input_1 == 'P')
        {
            gamestatus = 2;
        }

    }
}

void restart_menu()
{
        char input_2;
        if(kbhit())
        {
            input_2 = getch();
            if(input_2 == 27)
            {
                gamestatus = 0;
            }
        }
}


void data_withoutinput()  ///û����������ʱ
{
    paopao.position_y = paopao.position_y - paopao.v_y;         ///��������
    if(paopao.position_y < 0)
    {
        paopao.position_x = players.position_x;                 ///�����ظ�����
        paopao.position_y = players.position_y;
    }

    food1.position_x = food1.position_x + food1.v_x;             ///1���������ƶ�
    if(food1.position_x > length)
    {
        food1.position_x = -400;
        food1.position_y = rand() % 500;                        ///����1�����ظ�����
    }

    food8.position_x = food8.position_x - food8.v_x;              ///һ���������ƶ�
    if(food8.position_x < 0)
    {
        food8.position_x = 1000;
        food8.position_y = rand() % 400;                       ///�����ƶ�һ�����ظ�����
    }

    food2.position_x = food2.position_x - food2.v_x;       ///�����������ƶ�
    if(food2.position_x < 0)
    {
        food2.position_x = 1900;
        food2.position_y = rand() % 400;                   ///�������ظ�����
    }

    food3.position_x = food3.position_x - food3.v_x;       ///�����������ƶ�
    if(food3.position_x < 0)
    {
        food3.position_x = 2500;
        food3.position_y = rand() % 400;                    ///�ĺ����س���
    }

    food4.position_x = food4.position_x - food4.v_x;        ///�ĺ��������ƶ�
    if(food4.position_x < 0)
    {
        food4.position_x = 2800;
        food4.position_y = rand() % 400;                  ///�ĺ����ظ�����
    }

    food5.position_x = food5.position_x - food5.v_x;         ///����������ƶ�
    if(food5.position_x < 0)
    {
        food5.position_x = 3200;
        food5.position_y = rand() % 400;                     ///������ظ�����
    }

    food6.position_x = food6.position_x + food6.v_x;          ///�����������ƶ�
    if(food6.position_x > length)
    {
        food6.position_x = -2500;
        food6.position_y = rand() % 500;                                ///�������ظ�����
    }

    food7.position_x = food7.position_x + food7.v_x;             ///�ߺ��������ƶ�
    if(food7.position_x > length)
    {
        food7.position_x = -600;
        food7.position_y = rand() % 400;                        ///�ߺ����ظ�����

    }

    timer.position_x = timer.position_x + timer.v_x;         ///���������ƶ�
    if(timer.position_x > length)
    {
        timer.position_x = -2000;             ///���ӳ���һ�κ������ظ�����
        timer.position_y = rand() % 500;       ///�任���꣬ʹ���´γ���ʱ��ļ������
    }

    zhadan.position_x = zhadan.position_x + zhadan.v_x;     ///ը�������ƶ�
    if(zhadan.position_x > length)                               ///��������³���
    {
        zhadan.position_x = -1000;
        zhadan.position_y = rand() % 600;
    }


    ///�жϳԵ�����������ĵ�λ�������ķ�Χ��ʱ���Ե�
    if((timer.position_x + 45/2.0/*���ӳߴ�*/ >= players.position_x) && (timer.position_x + 45/2.0<= players.position_x + p1size)
            && (timer.position_y + 25 >= players.position_y + 20) && (timer.position_y + 25 <= players.position_y + p1size))
    {
        mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///��ͣ�Ե���Ч
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        socre_p1 += 5;                                           ///�Ե����ӷ�����5
        timer.position_x = -10000;
        timer.position_y = rand() % (high - 45);                    ///��ҳԵ�����
    }

    if((zhadan.position_x + 45/2.0/*ը���ߴ�*/ >= players.position_x) && (zhadan.position_x + 45/2.0 <= players.position_x +p1size)
            && (zhadan.position_y + 25 >= players.position_y) && (zhadan.position_y + 25 <= players.position_y + p1size))
    {
        mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);              ///��ͣ�Ե���Ч
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
        mciSendString(TEXT("close backmusic\\baozha.mp3"), NULL, 0, NULL);         ///ÿ���ڴ�ǰ�ر�ը����Ч
        mciSendString(TEXT("play backmusic\\baozha.mp3"), NULL, 0, NULL);

        alive--;
        p1size = start_p1size;
        players.position_x = length / 2.0;
        players.position_y = high - 100;                        ///�Ե�ը���������
        zhadan.position_x = -1000;                          ///��ҳԵ�ը��
        zhadan.position_y = rand() % (high - 45);
    }

    if((food1.position_x + 50/2.0/*��תС��ߴ�*/ >= players.position_x && food1.position_x + 50/2.0 <= players.position_x + p1size)
            && (food1.position_y + 25/2.0 >= players.position_y) && (food1.position_y + 25/2.0 <= players.position_y + p1size))
    {
        mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///��ͣ�Ե���Ч
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p1size += 2;
        socre_p1 += 10;                                                      ///�Ե�С�������10
        food1.position_x = -300;
        food1.position_y = rand() % (high - 25);                          ///��תС�㱻�ԣ�������������
    }

    if((food8.position_x + 50/2.0/*��תС��ߴ�*/>= players.position_x && food8.position_x + 50/2.0 <= players.position_x + p1size)
            && (food8.position_y + 25/2.0 >= players.position_y) && (food8.position_y + 25/2.0 <= players.position_y + p1size))
    {
        mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);                   ///�رձ�����Ч
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                ///��ͣ�Ե���Ч
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);                 ///�رճԵ���Ч
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p1size += 2;
        socre_p1 +=10;                                                                ///�Ե���תС�������10
        food8.position_x = 1300;
        food8.position_y = rand() % (high - 25);
    }

    if(p1size > 65)                            ///��С�ﵽ�ܳԵ�������
    {
        if((food2.position_x + 20/*������ߴ�*/ >= players.position_x && food2.position_x + 20 <= players.position_x + p1size)
                && (food2.position_y >= players.position_y && food2.position_y <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 3;
            socre_p1 += 20;                                               ///�Ե������������20
            food2.position_x = 1200;
            food2.position_y = rand() % (high - 40);
        }
    }
    else                                        ///û�ﵽ�������������򱻳�
    {
        if((players.position_x + p1size/2.0/*�������ߴ�һ��*/ >= food2.position_x && players.position_x + p1size/2.0 <= food2.position_x + 65)
                && (players.position_y + p1size/2.0 >= food2.position_y && players.position_y + p1size/2.0 <= food2.position_y + 40))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);            ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;     ///�������
            players.position_y = high - 100;
        }
    }


    if(p1size > 75)                              ///��С�ﵽ�ܳ����ź��ߺź�����
    {
        if((food3.position_x + 80/2.0/*������ߴ�һ��*/ >= players.position_x ) && (food3.position_x + 80/2.0 <= players.position_x + p1size)
                && (food3.position_y + 70/2.0 >= players.position_y )  && (food3.position_y + 70/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);                  ///�رձ�����Ч
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                 ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);               ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 3;
            socre_p1 += 30;                                   ///�Ե������������30
            food3.position_x = 1500;                        ///����������
            food3.position_y = rand() % (high - 70);
        }

        if((food7.position_x + 80/2.0 /*�ߺź�����ߴ�һ��*/>= players.position_x) && (food7.position_x + 80/2.0 <= players.position_x + p1size)
                && (food7.position_y + 70/2.0 >= players.position_y) && (food7.position_y + 70/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);                ///�رձ�����Ч
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);              ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 4;
            socre_p1 += 30;                                   ///�Ե��ߺ��������30
            food7.position_x = -500;                      ///�ߺ�������
            food7.position_y = rand() % (high - 70);
        }
    }
    else                                         ///û�ﵽ���������Ÿ��ߺ����򱻳�
    {
        if((players.position_x + p1size/2.0 >= food3.position_x) && (players.position_x + p1size/2.0 <= food3.position_x + 80)
                && (players.position_y + p1size/2.0 >= food3.position_y) && (players.position_y + p1size/2.0 <= food3.position_y + 70))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;            ///��ұ����ųԵ�����
            players.position_y = high - 100;
        }

        if((players.position_x + p1size/2.0 >= food7.position_x) && (players.position_x + p1size/2.0 <= food7.position_x + 80)
                && (players.position_y + p1size/2.0 >= food7.position_y) && (players.position_y + p1size/2.0 <= food7.position_y +70))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;              ///��ұ��ߺź�����Ե�����
        }
    }


    if(p1size > 90)                              ///��С�ﵽ�ܳ��ĺ���
    {
        if((food4.position_x + 105/2.0/*�ĺ���ߴ�*/ >= players.position_x) && (food4.position_x + 105/2.0 <= players.position_x + p1size)
                && (food4.position_y + 70/2.0 >= players.position_y) && (food4.position_y + 70/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 4;
            socre_p1 += 40;                                      ///�Ե��ĺ��������40
            food4.position_x = 1700;                          ///�ĺ�������
            food4.position_y = rand() & (high - 70);
        }
    }
    else                                         ///û�ﵽ�������ĺ����򱻳�
    {
        if((players.position_x + p1size/2.0 >= food4.position_x) && (players.position_x + p1size/2.0 <= food4.position_x + 105)
                && (players.position_y + p1size/2.0 >= food4.position_y) && (players.position_y + p1size/2.0 <= food4.position_y + 70))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;            ///��ұ�������
            players.position_y = high - 100;
        }
    }


    if(p1size > 105)                              ///��С�ﵽ�ܳ�������
    {
        if((food6.position_x + 150/2.0/*������ߴ�һ��*/ >= players.position_x)&& (food6.position_x + 150/2.0 <= players.position_x + p1size)
                && (food6.position_y + 110/2.0 >= players.position_y) && (food6.position_y + 110/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 4;
            socre_p1 += 50;                                  ///�Ե������������50
            food6.position_x = -1200;
            food6.position_y = rand() % 400;             ///����������
        }
    }
    else                                            ///û�ﵽ�������������򱻳�
    {
        if((players.position_x + p1size/2.0 >= food6.position_x) && (players.position_x + p1size/2.0 <= food6.position_x + 150)
                && (players.position_y + p1size/2.0 >= food6.position_y) && (players.position_y + p1size/2.0 <= food6.position_y + 110))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;          ///��������ұ�������
        }
    }


    if(p1size > 135)                             ///��Ҵ�С�ﵽ���������
    {
        if((food5.position_x + 275/2.0/*�����һ��ߴ�*/ >= players.position_x) && (food4.position_x + 275/2.0 <= players.position_x + p1size)
                && (food5.position_y + 125/2.0 >= players.position_y) && (food5.position_y + 125/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 5;
            socre_p1 += 60;                                             ///�Ե�����������60
            food5.position_x = 4000;                                 ///���������
            food5.position_y = rand() % (high - 100);
        }
    }
    else                                         ///û�ﵽ������������򱻳�
    {
        if((players.position_x + p1size/2.0 >= food5.position_x) && (players.position_x + p1size/2.0 <= food5.position_x + 275)
                && (players.position_y + p1size/2.0 >= food5.position_y) && (players.position_y + p1size/2.0 <= food5.position_y + 125))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;                  ///��ұ������Ա�����
        }
    }
}


void data_withinput()   ///����������ʱ
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (players.position_x > 0))
    {
        yuturn = 1;                                   ///��ת
        players.position_x = players.position_x - players.v_x;
    }

    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (players.position_x < length - 45))    ///��ֹ��ת����
    {
        yuturn = 0;                                          ///��ת
        players.position_x = players.position_x + players.v_x;
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  players.position_y > 0)
        players.position_y = players.position_y - players.v_y;             ///����
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  players.position_y < high - 45)         ///��ֹ��ת����
        players.position_y = players.position_y + players.v_y;            ///����
}


void background_over()    ///��Ϸ��������
{
    putimage(0, 0, gameover);
    mciSendString(TEXT("stop backmusic\\huankuai.mp3"), NULL, 0, NULL);    ///��ͣ�ر���Ϸ����
    mciSendString(TEXT("close backmusic\\huankuai.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play backmusic\\music3.mp3"), NULL, 0, NULL);       ///����Ϸ������������

    setbkmode(TRANSPARENT);                                              ///��Ϸ����������
    setcolor(YELLOW);
    setfont(50, 0, "����");
    xyprintf(120, 20, "�� ��");
    xyprintf(147, 80, "%d", socre_p1);
    xyprintf(300, 100, "G A M E   O V E R");
    xyprintf(340, 200, "~~~oo(^_^)oo~~~");
    xyprintf(380, 290, "�����Ŭ��!!");
    xyprintf(430, 370, "������");
    xyprintf(305, 450, "������С�㡣����");
    Sleep(10000);                                                 ///��ʱ��ͣ�ȴ���һ������
}


void game_over()
{
    getch();
    closegraph();
}


int main()
{
    srand((unsigned)time(NULL));
    initgraph(length, high);
    playmusic();
    every_data();
    while(1)
    {

    if(backchange == 0 && goback == 0)
    {
        mciSendString(TEXT("play backmusic\\music2.mp3 repeat"), NULL, 0, NULL);

        formbackground();

    }

    if(backchange == 1 && goback == 1)
    {
        mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///�رղ˵�ҳ������1
        mciSendString(TEXT("play backmusic\\music1.mp3 repeat"), NULL, 0, NULL);              ///���Ų˵�ҳ������2

        background_1();

        if(backchange == 0 && goback == 0)
        mciSendString(TEXT("close backmusic\\music1.mp3"), NULL, 0, NULL);
    }


    if(backchange == 2 && goback == 2)
    {
        mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///�رղ˵�ҳ������1
        mciSendString(TEXT("play backmusic\\music5.mp3 repeat"), NULL, 0, NULL);              ///���Ų˵�ҳ������3

        background_2();

        if(backchange == 0 && goback == 0)
        mciSendString(TEXT("close backmusic\\music5.mp3"), NULL, 0, NULL);
    }
    if(flag == 2)
        break;                                                     ///�Ƿ������Ϸҳ��
    }
    while(1)
    {
        if((backchange == 0 && gamestatus == 0) || flag == 2)
        {
        initdata1();
        initdata2();

        while(gamestatus == 2)           ///�ж���Ϸ�Ƿ����
        restart_menu();

        data_withoutinput();
        data_withinput();
        Sleep(1);                ///�����ͼƬ�л�ʱ����������
        cleardevice();
        if(alive < 0)
            break;
        }
    }
    while(1)                         ///��ʱ�䱣�����ҳ��
    {
        background_over();
    }
    game_over();
    return 0;
}
