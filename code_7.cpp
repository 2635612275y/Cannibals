#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>

#define length 1000   /// ��Ϸ����
#define high 640
#define fishnum 20      ///��һ����Ϸ�������
#define fishsum  20      ///�ڶ�����Ϸ�������
#define changenum 12      ///��һ��������ͼ�β�����̬Ч��������
#define changesum 12       ///�ڶ������
#define boomnum 2          ///ը������
#define alarmnum 2      ///��������

PIMAGE enter, enterchange[3], background, player[changenum] /*��һ�����*/ /*�ڶ������*/, player2[changesum];
PIMAGE numfish[fishnum]/*��һ����*/, boom[boomnum], alarm[alarmnum], /*�ڶ�����*/sumfish[fishsum], boom1[boomnum], alarm1[alarmnum];
PIMAGE pao, pao1,  wancheng, wancheng2, guanqia[3], next, next2, life, life2;
PIMAGE guanqiaback, background2, background3, gameover;
PIMAGE game2, game3;                   ///��Ϸ�ڶ��ص�����

typedef struct games
{
    double position_x;   ///������
    double position_y;    ///������
    double v_x;      ///ˮƽ�ٶ�
    double v_y;      ///��ֱ�ٶ�
} yu , yu1;

yu players;///���
/*  ��һ��   */
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
/*  �ڶ���   */

yu1 timer2;///����
yu1 paopao1;///����
yu1 zhadan1;///ը��
yu1 players2; ///�ڶ������
yu1 food11;///1����
yu1 food111;///һ����
yu1 food1111;///һ����
yu1 food22;///2����
yu1 food33;///3����
yu1 food44;///4����
yu1 food55;///5����
yu1 food66;///6����

int yuturn = 0, yuturn1 = 0;             ///�ж����Ƿ��ͷ   1  ��ͷ��   0 ����ͷ��
int backchange = 0;              ///�жϱ����Ƿ�任            0 Ϊ��ʼ�˵�ҳ�� 1Ϊ�˵�1 2Ϊ�˵�2
int goback = 0;                 ///�˵�ҳ��ص���ʼ                0Ϊ��ʼ�˵�ҳ��   1Ϊ�˵�1    2Ϊ�˵�2

double p1size, p1size1;              ///������ߴ�
double start_p1size, start_p1size1;      ///������ĳ�ʼ��С
int alive = 3;                 ///�������
int alive1 = 3;                 ///�ڶ����������
int gamestatus = 0;              ///��Ϸ״̬�� 0 Ϊ������Ϸ��1 Ϊ������Ϸ״̬��2 Ϊ��Ϸ��ͣ
int gamestatus1 = 0;
double starttime, starttime1, endtime, endtime1;              ///��ʱ
double timelong = 70.0, timelong2 = 60.0, timelong3 = 60.0;                  ///��Ϸʱ������
double resttime, resttime1;          ///��Ϸʣ��ʱ��
int  socre_p1 = 0 , socre_p2;         ///��Ϸ����
int flag = 0;                        ///������¼�����λ��
int passchange = 0;                ///�ؿ��仯
int passchange1 = 0;

void playmusic();
void every_data1();
void every_data2();
void formbackground();
void initdata1();
void initdata2();
void data_withoutinput1();
void data_withinput1();
void data_withoutinput2();
void data_withinput2();
void background_over();
void background_1();
void background_2();
void restart_menu1();
void restart_menu2();
void passbei();
void choosepass();
void fistwin();
void secondwin();
void thirdwin();
void game_over();

void playmusic()             ///�������ļ���
{
    mciSendString(TEXT("open backmusic\\bit.mp3"), NULL, 0, NULL);                    ///���ظ�����
    mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\win.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\huankuai.mp3"),NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\baozha.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music1.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music3.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music4.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music5.mp3"), NULL, 0, NULL);
}

void every_data1()            ///��һ�س�ʼ����
{
    wancheng = newimage();
    enter = newimage();
    guanqiaback = newimage();
    background = newimage();
    background2 = newimage();
    background3 = newimage();
    pao = newimage();
    gameover = newimage();
    next = newimage();
    life = newimage();
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
    for(int i = 0; i < 3; i++)
        guanqia[i] = newimage();
    getimage(guanqiaback, "yupic\\background.png");   ///�ؿ�����
    getimage(guanqia[0], "yupic\\pass1.png");   ///�ؿ�1
    getimage(guanqia[1], "yupic\\pass2.png");   ///�ؿ�2
    getimage(guanqia[2], "yupic\\pass3.png");   ///�ؿ�3
    getimage(next, "yupic\\next1.png");          ///��һ��
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
    getimage(life, "yupic\\xieliang.png");

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


    starttime = clock();               ///��ʱ

    p1size = 60;                      ///��ߴ�
    start_p1size = p1size;             ///���ʼ�ߴ�,��ֵ��ţ���ֹ�´α�ֵ

    players.position_x = length/2.0;   ///�������
    players.position_y = high/2.0;
    players.v_x = 0.9;              ///����ٶ�
    players.v_y = 0.9;

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

void every_data2()          ///�ڶ��س�ʼ����
{
    pao1 = newimage();
    game2 = newimage();
    life2 = newimage();
    next2 = newimage();
    wancheng2 = newimage();
    for(int i = 0; i < alarmnum; i++)
        alarm1[i] = newimage();
    for(int i = 0; i < boomnum; i++)
        boom1[i] = newimage();
    for(int i = 0; i < fishsum; i++)
        sumfish[i] = newimage();
    for(int i = 0; i< changesum; i++)
        player2[i] = newimage();

        getimage(player2[0], "yupic1\\players11.png");   ///�����
        getimage(player2[1], "yupic1\\players22.png");
        getimage(player2[2], "yupic1\\players33.png");
        getimage(player2[3], "yupic1\\players44.png");
        getimage(player2[4], "yupic1\\players55.png");
        getimage(player2[5], "yupic1\\players66.png");

        getimage(player2[6], "yupic1\\players1.png");
        getimage(player2[7], "yupic1\\players2.png");
        getimage(player2[8], "yupic1\\players3.png");
        getimage(player2[9], "yupic1\\players4.png");
        getimage(player2[10], "yupic1\\players5.png");
        getimage(player2[11], "yupic1\\players6.png");

        getimage(sumfish[0], "yupic1\\oneyu1.png");   ///��תһ����
        getimage(sumfish[1], "yupic1\\oneyu2.png");   ///��תһ����
        getimage(sumfish[2], "yupic1\\oneyu3.png");   ///��תһ����
        getimage(sumfish[3], "yupic1\\twoyu.png");
        getimage(sumfish[4], "yupic1\\threeyu.png");
        getimage(sumfish[5], "yupic1\\fouryu.png");
        getimage(sumfish[6], "yupic1\\fiveyu.png");
        getimage(sumfish[7], "yupic1\\sixyu.png");

        getimage(pao1, "yupic1\\paopao1.png");
        getimage(game2, "yupic1\\bei1.png");
        getimage(alarm1[0], "yupic1\\naozhong1.png");
        getimage(boom1[0], "yupic1\\zhadan1.png");
        getimage(life2, "yupic1\\xieliang.png");
        getimage(wancheng2, "yupic1\\wancheng2.png");
        getimage(next2, "yupic1\\next2.png");

        starttime1 = clock();

    p1size1 = 60;                      ///��ߴ�
    start_p1size1 = p1size1;             ///���ʼ�ߴ�,��ֵ��ţ���ֹ�´α�ֵ

    players2.position_x = length/2.0;   ///�������
    players2.position_y = high/2.0;
    players2.v_x = 0.9;              ///����ٶ�
    players2.v_y = 0.9;

    paopao1.position_x = players2.position_x;    ///��������Ϊ�������
    paopao1.position_y = players2.position_y;
    paopao1.v_y = 0.2;                          ///���������ٶ�

    food11.position_x = 0;           ///��ת1���������
    food11.position_y = rand() % 400;    ///��ת1��������������趨
    food11.v_x = 0.7;                  ///��ת1�����ٶ�

    food111.position_x = 1000;           ///��ת1���������
    food111.position_y = rand() % 400;    ///��ת1��������������趨
    food111.v_x = 0.8;                  ///��ת1�����ٶ�

    food1111.position_x = -500;
    food1111.position_y = rand() % 500;      ///��תһ����
    food1111.v_x = 0.7;

    food22.position_x = 1200;        ///����������
    food22.position_y = rand() % 400;
    food22.v_x =0.6;

    food33.position_x = 1200;            ///����������
    food33.position_y = rand() % 400;
    food33.v_x = 0.55;

    food44.position_x = -1800;             ///�ĺ���
    food44.position_y = rand() % 400;
    food44.v_x = 0.4;

    food55.position_x = -2200;            ///�����
    food55.position_y = rand() % 400;
    food55.v_x = 0.6;

    food66.position_x = 3000;          ///������
    food66.position_y = rand() % 500;
    food66.v_x = 0.8;


    timer2.position_x = rand() % 900;     ///����������
    timer2.position_y = -1000;    ///���Ӻ���������趨
    timer2.v_y = 0.5;            ///�����ٶ�

    zhadan1.position_x = rand() % 900; ///ը��������
    zhadan1.position_y = - 200;
    zhadan1.v_y = 0.3;

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

void background_1()    ///�˵�1
{
        putimage(0, 0, background2);                   ///����˵��ҳ��

        setbkmode(TRANSPARENT);
        setcolor(RED);
        setfont(50, 0, "����");
        xyprintf(320, 40, "�� Ϸ �� �� ˵ ��");
        setcolor(GREEN);
        setfont(30, 0, "����");
        xyprintf(370, 180, "�� �� �� �� ����С���ƶ�");
        xyprintf(290, 280, "��P����ʹ��Ϸ��ͣ, ������Ϸ��Esc��");
        setcolor(RED);
        setfont(30, 0, "����");
        xyprintf(220, 400, "���ز˵�");
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

void background_2()    ///�˵�2
{
        putimage(0, 0, background3);                ///��Ϸ���ܱ���ҳ��

        setbkmode(TRANSPARENT);
        setcolor(RED);
        setfont(50, 0, "����");
        xyprintf(350, 40, "�� Ϸ �� ��");
        setfont(30, 0, "����");
        xyprintf(200, 150, "����ϷΪ����Ĵ����С����Ϸ���ܹ���Ϊ���أ�");
        xyprintf(160, 220, "�Ե����Լ�����С����÷֣��Ե����Լ����ʹ��������ֵ -1 ");
        xyprintf(80, 280, "�������ֵÿ��Ϊ�������Ե�ը�� - 1 ������ֵ��������������ֵ");
        xyprintf(0, 350, "��ϷΪ��ʱ��Ϸ!!!�Ե���һ��ʱ�Ӽ�10s���ڶ��ؼ�15s�������ؼ�20s~~~");
        xyprintf(160, 420, "��һ����ʱΪ 70s �ڶ�����ʱΪ 60s ��������ʱΪ 60s����");
        xyprintf(50, 470, "�������ﵽ620��ͨ����һ�أ��������ﵽ645��ʱͨ���ڶ���");
        xyprintf(270, 530, "��������Ҫ�ﵽ1000��Ŷ������");
        setcolor(YELLOW);
        xyprintf(420, 590, "���ز˵�");
        Sleep(1);

        mouse_msg lick_an = {0};
        while(1)
        {
            while(mousemsg())
            {
                lick_an = getmouse();
                if(lick_an.x >= 420 && lick_an.x <= 537 && lick_an.y >= 595 && lick_an.y <= 620)
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

void passbei()         ///�ؿ�
{
    putimage(0, 0, guanqiaback);
    putimage(300, 260, guanqia[0]);
    putimage(450, 260, guanqia[1]);
    putimage(600, 260, guanqia[2]);
    Sleep(1);
}

void choosepass()   ///ѡ��ؿ�
{
    mouse_msg in = {0};
    while(1)
    {
    while(mousemsg())
      {
          in = getmouse();
          if(in.x >= 300 && in.x <= 370 && in.y >= 260 && in.y <= 330)
        {
            if(in.is_down())
            passchange = 2;
            if(in.is_up())
            passchange = 1;
        }
      }
      if(passchange == 1)
        break;
    }

}

void initdata1()    ///���±���
{
    mciSendString(TEXT("stop backmusic\\music2.mp3"), NULL, 0, NULL);              ///��ͣ�˵�ҳ������1
    mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///�رղ˵�ҳ������1
    mciSendString(TEXT("play backmusic\\huankuai.mp3 repeat"), NULL, 0, NULL);              ///���Ž�����Ϸҳ������4

    endtime = clock();
    resttime = timelong - (endtime - starttime)/1000.0;          ///��ʱ

    if(backchange == 0)
    putimage(0, 0, background);                          ///��Ϸ����

    setbkmode(TRANSPARENT);                         ///��Ϸ����
    setcolor(RED);                                   ///������ɫ
    setfont(25, 0, "����");                          ///�����С������

    xyprintf(65, 10, "Score");
    xyprintf(80, 45, "%d", socre_p1);              ///����

    xyprintf(415, 10, "resttime");                 ///ʣ��ʱ��
    xyprintf(427, 45, "%.2f", resttime);

    xyprintf(750, 10, "The remaining life");
    for(int i = 0, j = 0; i < alive; i++, j+= 80)
    putimage_transparent(NULL, life, 770 + j, 45, 0);                  ///����

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
}

void initdata2()    ///�����㣨��̬ת����(ʹ������ʱ����ʾ�ĸ�����ʵ��
{
    mciSendString(TEXT("close backmusic\\win.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("stop backmusic\\huankuai.mp3"), NULL, 0, NULL);              ///�رյ�һ�ر�������
    mciSendString(TEXT("colse backmusic\\huankuai.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play backmusic\\music5.mp3 repeat"), NULL, 0, NULL);           ///�򿪵ڶ��ر�������

    endtime1 = clock();
    resttime1 = timelong2 - (endtime1 - starttime1)/1000.0;        ///�ڶ��ؼ�ʱ

    putimage_transparent(NULL, game2, 0, 0, 0);                          ///��Ϸ����

    setbkmode(TRANSPARENT);                         ///��Ϸ����
    setcolor(RED);                                   ///������ɫ
    setfont(25, 0, "����");                          ///�����С������

    xyprintf(65, 10, "Score");
    xyprintf(80, 45, "%d", socre_p2);              ///����

    xyprintf(415, 10, "resttime");                 ///ʣ��ʱ��
    xyprintf(426, 45, "%.2f", resttime1);

    xyprintf(750, 10, "The remaining life");
    for(int i = 0, j = 0; i < alive1; i++, j+= 80)
    putimage_transparent(NULL, life2, 750 + j, 45, 0);                  ///����

    putimage_transparent(NULL, sumfish[0], food11.position_x, food11.position_y, 0);   ///����תһ������ʾ����
    putimage_transparent(NULL, sumfish[1], food111.position_x, food111.position_y, 0);   ///��תһ�����ӡ
    putimage_transparent(NULL, sumfish[2], food1111.position_x, food1111.position_y, 0);     ///��תһ����
    putimage_transparent(NULL, sumfish[3], food22.position_x, food22.position_y, 0);     ///������
    putimage_transparent(NULL, sumfish[4], food33.position_x, food33.position_y, 0);     ///������
    putimage_transparent(NULL, sumfish[5], food44.position_x, food44.position_y, 0);             ///�ĺ���
    putimage_transparent(NULL, sumfish[6], food55.position_x, food55.position_y, 0);             ///�����
    putimage_transparent(NULL, sumfish[7], food66.position_x, food66.position_y, 0);

    putimage_transparent(NULL, boom1[0], zhadan1.position_x, zhadan1.position_y, 0);      ///ը��
    putimage_transparent(NULL, alarm1[0], timer2.position_x, timer2.position_y, 0);       ///����
    putimage(paopao1.position_x, paopao1.position_y, pao, SRCAND);         ///�µ�����
    putimage(paopao1.position_x, paopao1.position_y - 30, pao, SRCAND);


    if(yuturn1 == 0)                       ///��������仯
    {
        if(p1size1 < 65)
            putimage_transparent(NULL, player2[0], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 65 && p1size1 <75)
            putimage_transparent(NULL, player2[1], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 75 && p1size1 < 90)
            putimage_transparent(NULL, player2[2], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 90 && p1size1 < 105)
            putimage_transparent(NULL, player2[3], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 105 && p1size1 < 135)
            putimage_transparent(NULL, player2[4], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 135)
            putimage_transparent(NULL, player2[5], players2.position_x, players2.position_y, 0);
    }
    else
    {
        if(p1size1 < 65)
            putimage_transparent(NULL, player2[6], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 65 && p1size1 <75)
            putimage_transparent(NULL, player2[7], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 75 && p1size1 < 90)
            putimage_transparent(NULL, player2[8], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 90 && p1size1 < 105)
            putimage_transparent(NULL, player2[9], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 105 && p1size1 < 135)
            putimage_transparent(NULL, player2[10], players2.position_x, players2.position_y, 0);
        else if(p1size1 >= 135)
            putimage_transparent(NULL, player2[11], players2.position_x, players2.position_y, 0);
    }
}

void restart_menu1()  ///������Ϸ1
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

void restart_menu2()  ///������Ϸ2
{
    char input_3;
        if(kbhit())
        {
            input_3 = getch();
            if(input_3 == 27)
            {
                gamestatus1 = 0;
            }
        }
}

void data_withoutinput1()  ///û����������ʱ1
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
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///��ͣ�Ե���Ч
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        timelong += 10;                               ///�Ե�����ʱ���ʮ��
        socre_p1 += 5;                                           ///�Ե����ӷ�����5
        timer.position_x = -10000;
        timer.position_y = rand() % (high - 45);                    ///��ҳԵ�����
    }

    if((zhadan.position_x + 45/2.0/*ը���ߴ�*/ >= players.position_x) && (zhadan.position_x + 45/2.0 <= players.position_x +p1size)
            && (zhadan.position_y + 25 >= players.position_y) && (zhadan.position_y + 25 <= players.position_y + p1size))
    {
        mciSendString(TEXT("stop backmusic\\baozha.mp3"), NULL, 0, NULL);
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);               ///�رձ�����Ч
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;            ///��ұ����ųԵ�����
            players.position_y = high - 100;
        }

        if((players.position_x + p1size/2.0 >= food7.position_x) && (players.position_x + p1size/2.0 <= food7.position_x + 80)
                && (players.position_y + p1size/2.0 >= food7.position_y) && (players.position_y + p1size/2.0 <= food7.position_y +70))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;          ///��������ұ�������
        }
    }


    if(p1size > 135)                             ///��Ҵ�С�ﵽ���������
    {
        if((food5.position_x + 300/2.0/*�����һ��ߴ�*/ >= players.position_x) && (food5.position_x + 300/2.0 <= players.position_x + p1size)
                && (food5.position_y + 160/2.0 >= players.position_y) && (food5.position_y + 160/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 10;
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;                  ///��ұ������Ա�����
        }
    }
}

void data_withinput1()   ///����������ʱ1
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

void data_withoutinput2()  ///û����������ʱ����2
{
    paopao1.position_y = paopao1.position_y - paopao1.v_y;         ///��������
    if(paopao1.position_y < 0)
    {
        paopao1.position_x = players2.position_x;                 ///�����ظ�����
        paopao1.position_y = players2.position_y;
    }

    food11.position_x = food11.position_x - food11.v_x;             ///1���������ƶ�
    if(food11.position_x < 0)
    {
        food11.position_x = 1300;
        food11.position_y = rand() % 500;                        ///����1�����ظ�����
    }

    food111.position_x = food111.position_x + food111.v_x;              ///һ���������ƶ�
    if(food111.position_x > length)
    {
        food111.position_x = 0;
        food111.position_y = rand() % 400;                         ///�����ƶ�һ�����ظ�����
    }

    food1111.position_x = food1111.position_x - food1111.v_x;        ///һ���������ƶ�
    if(food1111.position_x < 0)
    {
        food1111.position_x = 1200;
        food1111.position_y = rand() % 500;                  ///��תһ�����ظ�����
    }

    food22.position_x = food22.position_x - food22.v_x;       ///�����������ƶ�
    if(food2.position_x < 0)
    {
        food22.position_x = 1900;
        food22.position_y = rand() % 400;                   ///�������ظ�����
    }

    food33.position_x = food33.position_x - food33.v_x;       ///�����������ƶ�
    if(food33.position_x < 0)
    {
        food33.position_x = 2500;
        food33.position_y = rand() % 400;                    ///�ĺ����س���
    }

    food44.position_x = food44.position_x + food44.v_x;          ///�ĺ��������ƶ�
    if(food6.position_x > length)
    {
        food44.position_x = -1800;
        food44.position_y = rand() % 500;                                ///�ĺ����ظ�����
    }

    food55.position_x = food55.position_x + food55.v_x;         ///����������ƶ�
    if(food55.position_x > length)
    {
        food55.position_x = -2200;
        food55.position_y = rand() % 400;                     ///������ظ�����
    }

    food66.position_x = food66.position_x - food66.v_x;             ///�����������ƶ�
    if(food66.position_x < 0)
    {
        food66.position_x = 3100;
        food66.position_y = rand() % 400;                        ///�������ظ�����

    }

    timer2.position_y = timer2.position_y + timer2.v_y;         ///���������ƶ�
    if(timer2.position_y > high)
    {
        timer2.position_x =  rand() % 900;           ///���ӳ���һ�κ������ظ�����
        timer2.position_y = -2000;       ///�任���꣬ʹ���´γ���ʱ��ļ������
    }

    zhadan1.position_y = zhadan1.position_y + zhadan1.v_y;     ///ը�������ƶ�
    if(zhadan1.position_y > high)                               ///��������³���
    {
        zhadan1.position_x = rand() % 800;
        zhadan1.position_y = -200;
    }

    ///�жϳԵ�����������ĵ�λ�������ķ�Χ��ʱ���Ե�
    if((timer2.position_x + 45/2.0/*���ӳߴ�*/ >= players2.position_x) && (timer2.position_x + 45/2.0<= players2.position_x + p1size1)
            && (timer2.position_y + 25 >= players2.position_y + 20) && (timer2.position_y + 25 <= players2.position_y + p1size1))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///��ͣ�Ե���Ч
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        timelong2 += 15;                                ///�Ե�����ʱ���ʮ����
        socre_p2 += 5;                                           ///�Ե����ӷ�����5
        timer2.position_x = rand() % 900;
        timer2.position_y = -2200;                    ///��ҳԵ�����
    }

    if((zhadan1.position_x + 45/2.0/*ը���ߴ�*/ >= players2.position_x) && (zhadan1.position_x + 45/2.0 <= players2.position_x +p1size1)
            && (zhadan1.position_y + 25 >= players2.position_y) && (zhadan1.position_y + 25 <= players2.position_y + p1size1))
    {
        mciSendString(TEXT("stop backmusic\\baozha.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
        mciSendString(TEXT("close backmusic\\baozha.mp3"), NULL, 0, NULL);         ///ÿ���ڴ�ǰ�ر�ը����Ч
        mciSendString(TEXT("play backmusic\\baozha.mp3"), NULL, 0, NULL);

        alive1--;
        p1size1 = start_p1size1;
        players2.position_x = length / 2.0;
        players2.position_y = high - 100;                        ///�Ե�ը���������
        zhadan1.position_x = rand() % 1000;                          ///��ҳԵ�ը��
        zhadan1.position_y = -1000;
    }

    if((food11.position_x + 50/2.0/*��תС��ߴ�*/ >= players2.position_x && food11.position_x + 50/2.0 <= players2.position_x + p1size1)
            && (food11.position_y + 25/2.0 >= players2.position_y) && (food11.position_y + 25/2.0 <= players2.position_y + p1size1))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///��ͣ�Ե���Ч
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p1size1 += 2;
        socre_p2 += 10;                                                      ///�Ե�С�������10
        food11.position_x = 1300;
        food11.position_y = rand() % (high - 25);                          ///��תС�㱻�ԣ�������������
    }

    if((food111.position_x + 50/2.0/*��תС��ߴ�*/>= players2.position_x && food111.position_x + 50/2.0 <= players2.position_x + p1size1)
            && (food111.position_y + 25/2.0 >= players2.position_y) && (food111.position_y + 25/2.0 <= players2.position_y + p1size1))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                ///��ͣ�Ե���Ч
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);                 ///�رճԵ���Ч
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p1size1 += 2;
        socre_p2 +=10;                                                                ///�Ե���תС�������10
        food111.position_x = -200;
        food111.position_y = rand() % (high - 25);
    }

    if((food1111.position_x + 50/2.0 >= players2.position_x) && (food1111.position_x + 50/2.0 <= players2.position_x + p1size1)
                && (food1111.position_y + 25/2.0 >= players2.position_y) && (food1111.position_y + 25/2.0 <= players2.position_y + p1size1))
    {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);              ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size1 += 2;
            socre_p2 += 10;
            food1111.position_x = 1300;
            food1111.position_y = rand() % (high - 70);
    }

    if(p1size1 > 65)                            ///��С�ﵽ�ܳԵ�������
    {
        if((food22.position_x + 65/2.0/*������ߴ�*/ >= players2.position_x && food22.position_x + 65/2.0 <= players2.position_x + p1size1)
                && (food22.position_y + 40/2.0 >= players2.position_y && food22.position_y + 40/2.0<= players2.position_y + p1size1))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size1 += 3;
            socre_p2 += 20;                                               ///�Ե������������20
            food22.position_x = 1200;
            food22.position_y = rand() % (high - 40);
        }
    }
    else                                        ///û�ﵽ�������������򱻳�
    {
        if((players2.position_x + p1size1/2.0/*�������ߴ�һ��*/ >= food22.position_x && players2.position_x + p1size1/2.0 <= food22.position_x + 65)
                && (players2.position_y + p1size1/2.0 >= food22.position_y && players2.position_y + p1size1/2.0 <= food22.position_y + 40))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);             ///ÿ�δ򿪱�����Чǰ�ص�
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size1 = start_p1size1;
            alive1--;
            players2.position_x = length / 2.0;     ///�������
            players2.position_y = high - 100;
        }
    }


    if(p1size1 > 75)                              ///��С�ﵽ�ܳ�����
    {
        if((food33.position_x + 80/2.0/*������ߴ�һ��*/ >= players2.position_x ) && (food33.position_x + 80/2.0 <= players2.position_x + p1size1)
                && (food33.position_y + 70/2.0 >= players2.position_y )  && (food33.position_y + 70/2.0 <= players2.position_y + p1size1))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                 ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);               ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size1 += 4;
            socre_p2 += 30;                                   ///�Ե������������30
            food33.position_x = 1500;                        ///����������
            food33.position_y = rand() % (high - 70);
        }

    }
    else                                         ///û�ﵽ���������ű���
    {
        if((players2.position_x + p1size1/2.0 >= food33.position_x) && (players2.position_x + p1size1/2.0 <= food33.position_x + 80)
                && (players2.position_y + p1size1/2.0 >= food33.position_y) && (players2.position_y + p1size1/2.0 <= food33.position_y + 70))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size1 = start_p1size1;
            alive1--;
            players2.position_x = length / 2.0;            ///��ұ����ųԵ�����
            players2.position_y = high - 100;
        }
    }

    if(p1size1 > 90)                              ///��С�ﵽ�ܳ��ĺ���
    {
        if((food44.position_x + 105/2.0/*�ĺ���ߴ�*/ >= players2.position_x) && (food44.position_x + 105/2.0 <= players2.position_x + p1size1)
                && (food44.position_y + 70/2.0 >= players2.position_y) && (food44.position_y + 70/2.0 <= players2.position_y + p1size1))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size1 += 4;
            socre_p2 += 40;                                      ///�Ե��ĺ��������40
            food44.position_x = -700;                          ///�ĺ�������
            food44.position_y = rand() & (high - 70);
        }
    }
    else                                         ///û�ﵽ�������ĺ����򱻳�
    {
        if((players2.position_x + p1size1/2.0 >= food44.position_x) && (players2.position_x + p1size1/2.0 <= food44.position_x + 105)
                && (players2.position_y + p1size1/2.0 >= food44.position_y) && (players2.position_y + p1size1/2.0 <= food44.position_y + 70))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size1 = start_p1size1;
            alive1--;
            players2.position_x = length / 2.0;            ///��ұ�������
            players2.position_y = high - 100;
        }
    }

    if(p1size1 > 110)                             ///��Ҵ�С�ﵽ���������
    {
        if((food55.position_x + 200/2.0/*�����һ��ߴ�*/ >= players2.position_x) && (food55.position_x + 200/2.0 <= players2.position_x + p1size1)
                && (food55.position_y + 160/2.0 >= players2.position_y) && (food55.position_y + 160/2.0 <= players2.position_y + p1size1))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size1 += 8;
            socre_p2 += 45;                                             ///�Ե�����������60
            food55.position_x = -2000;                                 ///���������
            food55.position_y = rand() % (high - 100);
        }
    }
    else                                         ///û�ﵽ������������򱻳�
    {
        if((players2.position_x + p1size1/2.0 >= food55.position_x) && (players2.position_x + p1size1/2.0 <= food55.position_x + 200)
                && (players2.position_y + p1size1/2.0 >= food55.position_y) && (players2.position_y + p1size1/2.0 <= food55.position_y + 160))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size1 = start_p1size1;
            alive1--;
            players2.position_x = length / 2.0;
            players2.position_y = high - 100;                  ///��ұ������Ա�����
        }
    }

    if(p1size > 140)                              ///��С�ﵽ�ܳ�������
    {
        if((food66.position_x + 275/2.0/*������ߴ�һ��*/ >= players2.position_x)&& (food66.position_x + 275/2.0 <= players2.position_x + p1size1)
                && (food66.position_y + 150/2.0 >= players2.position_y) && (food66.position_y + 150/2.0 <= players2.position_y + p1size1))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///��ͣ�Ե���Ч
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///�رճԵ���Ч
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size1 += 15;
            socre_p2 += 60;                                  ///�Ե������������50
            food66.position_x = 3400;
            food66.position_y = rand() % 400;             ///����������
        }
    }
    else                                            ///û�ﵽ�������������򱻳�
    {
        if((players2.position_x + p1size1/2.0 >= food66.position_x) && (players2.position_x + p1size1/2.0 <= food66.position_x + 275)
                && (players2.position_y + p1size1/2.0 >= food66.position_y) && (players2.position_y + p1size1/2.0 <= food66.position_y + 150))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size1 = start_p1size1;
            alive1--;
            players2.position_x = length / 2.0;
            players2.position_y = high - 100;          ///��������ұ�������
        }
    }

}

void data_withinput2()    ///����������ʱ����2
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (players2.position_x > 0))
    {
        yuturn1 = 1;                                   ///��ת
        players2.position_x = players2.position_x - players2.v_x;
    }

    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (players2.position_x < length - 45))    ///��ֹ��ת����
    {
        yuturn1 = 0;                                          ///��ת
        players2.position_x = players2.position_x + players2.v_x;
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  players2.position_y > 0)
        players2.position_y = players2.position_y - players2.v_y;             ///����
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  players2.position_y < high - 45)         ///��ֹ��ת����
        players2.position_y = players2.position_y + players2.v_y;            ///����

    char input_4;
    if(kbhit())                                            ///��Ϸ��ͣ����
    {
        input_4 = getch();
        if(input_4 == 'p' || input_4 == 'P')
        {
            gamestatus1 = 2;
        }

    }

}

void background_over()    ///��Ϸ��������
{
    putimage(0, 0, gameover);
    mciSendString(TEXT("stop backmusic\\music5.mp3"), NULL, 0, NULL);    ///��ͣ�ر���Ϸ����2
    mciSendString(TEXT("close backmusic\\music5.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("stop backmusic\\huankuai.mp3"), NULL, 0, NULL);    ///��ͣ�ر���Ϸ����1
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

void fistwin()      ///��һ�ع���
{
    if(socre_p1 >= 1)
    {
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("play backmusic\\win.mp3"), NULL, 0, NULL);
        mouse_msg lick_1 = {0};
      while(1)
      {
           putimage_transparent(NULL, wancheng, 380, 200, 0);
           putimage_transparent(NULL, next, 480, 300, 0);
           while(mousemsg())
          {
            lick_1 = getmouse();
            if(lick_1.x >= 480 && lick_1.x <= 542 && lick_1.y >= 300 && lick_1.y <= 356)
            {
                if(lick_1.is_down())
                {
                    passchange1 = 1;
                }
                if(lick_1.is_up())
                {
                    passchange1 = 2;
                }
            }
          }
          if(passchange1 == 2) break;
       }
     }
}

void secondwin()  ///�ڶ��ع���
{
    if(socre_p2 >= 645)
    {
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("stop backmusic\\win.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("close backmusic\\win.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("play backmusic\\win.mp3"), NULL, 0, NULL);
        mouse_msg lick_2 = {0};
        while(1)
        {
            putimage_transparent(NULL, wancheng2, 380, 200, 0);
            putimage_transparent(NULL, next2, 480, 300, 0);
            while(mousemsg())
            {
                lick_2 = getmouse();
                if(lick_2.x >= 480 && lick_2.x <= 542 && lick_2.y >= 300 && lick_2.y <= 356)
                {
                    if(lick_2.is_down())
                    {
                        passchange1 = 2;
                    }
                    if(lick_2.is_down())
                    {
                        passchange1 = 3;
                    }
                }
            }
            if(passchange1 == 3)
                break;
        }
    }
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
    every_data1();
    while(1)           ///����˵�ҳ��
    {
    if(backchange == 0 && goback == 0)
    {
        mciSendString(TEXT("play backmusic\\music2.mp3 repeat"), NULL, 0, NULL);

        formbackground();
    }

    if(backchange == 1 && goback == 1)
    {
        mciSendString(TEXT("stop backmusic\\music2.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///�رղ˵�ҳ������1
        mciSendString(TEXT("play backmusic\\music1.mp3 repeat"), NULL, 0, NULL);              ///���Ų˵�ҳ������2

        background_1();

        if(backchange == 0 && goback == 0)
        {
            mciSendString(TEXT("stop backmusic\\music1.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\music1.mp3"), NULL, 0, NULL);
        }

    }

    if(backchange == 2 && goback == 2)
    {
        mciSendString(TEXT("stop backmusic\\music2.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///�رղ˵�ҳ������1
        mciSendString(TEXT("play backmusic\\music5.mp3 repeat"), NULL, 0, NULL);              ///���Ų˵�ҳ������3

        background_2();

        if(backchange == 0 && goback == 0)
        {
            mciSendString(TEXT("stop backmusic\\music5.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\music5.mp3"), NULL, 0, NULL);
        }

    }
    if(flag == 2)
        break;                                                     ///�Ƿ������Ϸҳ��
    }

    while(1)                ///����ѡ��ؿ�
    {
        passbei();
        choosepass();
        if(passchange == 1)
            break;
    }

    while(1)        ///��һ������
    {
        if((backchange == 0 && gamestatus == 0))
        {
        initdata1();
        data_withoutinput1();
        data_withinput1();

        while(gamestatus == 2)           ///�ж���Ϸ�Ƿ����
        restart_menu1();

        fistwin();
        if(passchange1 == 2)           ///��һ���Ƿ����
            break;

        Sleep(1);                     ///�����ͼƬ�л�ʱ����������
        cleardevice();
        if(alive == 0 || resttime < 0.0)
            break;
        }
    }

    if(alive > 0 && resttime >= 0.0)    ///�ڶ���
    {
    every_data2();
    while(1)
    {
         if(gamestatus1 == 0)
         {
             initdata2();
             data_withoutinput2();
             data_withinput2();

             while(gamestatus1 == 2)
                restart_menu2();

            secondwin();
            if(passchange1 == 3)
                    break;

             Sleep(1);
             cleardevice();
             if(alive1 == 0 || resttime1 < 0.0)
                break;
         }
    }
    }
    if(alive == 0 || alive1 == 0 || resttime < 0.0 || resttime1 < 0.0)
    {
    while(1)                           ///��ʱ�䱣��ʧ��ҳ��
    {
        background_over();
    }
    }

    game_over();
    return 0;
}


