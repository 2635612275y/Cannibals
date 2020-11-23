#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define length 1000   /// ��Ϸ����
#define high 640
#define fishnum 5      ///��Ϸ�������
#define changenum 10      ///���ͼ�β�����̬Ч��������
PIMAGE enter, background, player[changenum];
PIMAGE numfish[fishnum];

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
yu food1;///1����
yu food2;///2����
yu food3;///3����
yu food4;///4����
yu food5;///5����

int yuturn = 0;           ///�ж����Ƿ��ͷ   1  ��ͷ��   0 ����ͷ

double p1size;           ///������ߴ�
double strat_p1size;    ///������ĳ�ʼ��С

void every_data()         ///��ʼ����
{
    for(int i = 0; i < changenum; i++)
        player[i] = newimage();
    for(int i = 0; i < fishnum; i++)
        numfish[i] = newimage();
    background = newimage();
    getimage(background, "yupic\\background.png");
    getimage(player[0], "yupic\\player1.png");
    getimage(player[1], "yupic\\player11.png");
    getimage(player[2], "yupic\\player2.png");
    getimage(player[3], "yupic\\player22.png");
    getimage(numfish[0], "yupic\\oneyu1.png");   ///��תһ����
    getimage(numfish[1], "yupic\\oneyu2.png");   ///��תһ����
    p1size = 45;                     ///��ߴ�
    strat_p1size = p1size;          ///���ʼ�ߴ�
    players.position_x = length/2.0;   ///�������
    players.position_y = high/2.0;
    players.v_x = 0.77;              ///����ٶ�
    players.v_y = 0.77;

    food1.position_x = 0;           ///1���������
	food1.position_y = rand() % 500;    ///1��������������趨
	food1.v_x = 0.3;                  ///1�����ٶ�

}

void initdata1()    ///���±���
{
    putimage(0, 0, background);
    putimage(food1.position_x, food1.position_y, numfish[1]);
}
void initdata2()    ///�����㣨��̬ת����
{
        if(yuturn == 0)
            putimage(players.position_x, players.position_y, player[0]);
        else
            putimage(players.position_x, players.position_y, player[2]);
}

void data_withoutinput()  ///û����������ʱ
{
       food1.position_x = food1.position_x + food1.v_x;         ///1���������ƶ�
       if(food1.position_x > length)
	    {
		food1.position_x = -400;
		food1.position_y = rand() % 500;      ///1�����ظ�����
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

void gameover()
{
    getch();
    closegraph();
}

int main()
{
    srand((unsigned)time(NULL));
    initgraph(length, high);
    every_data();
    while(1)
    {
        initdata1();
        initdata2();
        data_withoutinput();
        data_withinput();
        Sleep(1);        ///�����ͼƬ�л�ʱ����������
    }
    gameover();
    return 0;
}




