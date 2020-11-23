#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>


#define length 1000   /// ��Ϸ����
#define high 640
#define fishnum 9      ///��Ϸ�������
#define changenum 10      ///���ͼ�β�����̬Ч��������
#define boomnum 2          ///ը������
#define alarmnum 2      ///��������

PIMAGE enter, enterchange[3], background, player[changenum];
PIMAGE numfish[fishnum], boom[boomnum], alarm[alarmnum];
PIMAGE pao;

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

int yuturn = 0;             ///�ж����Ƿ��ͷ   1  ��ͷ��   0 ����ͷ

double p1size;             ///������ߴ�
double start_p1size;      ///������ĳ�ʼ��С
int alive = 3;       ///�������
int gamestatus = 0;       ///��Ϸ״̬��0Ϊ��ʼ�˵����棬 1 Ϊ������Ϸ��2 Ϊ������Ϸ״̬��3 Ϊ��Ϸ��ͣ
double starttime;              ///��ʱ
double endtime;                ///��ʱ
double timelong = 150.0;       ///��Ϸʱ������
double resttime;          ///��Ϸʣ��ʱ��
int  socre_p1 = 0;         ///��Ϸ����

void playmusic()
{
    mciSendString(TEXT("open backmusic\\bit.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music1.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music3.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\huankuai.mp3"),NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\baozha.mp3"), NULL, 0, NULL);
}
void every_data()            ///��ʼ����
{
    enter = newimage();
    background = newimage();
    pao = newimage();
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
    getimage(enterchange[0], "yupic\\tietu22.png");      ///���ͣ����������ط�ͼƬ�仯
    getimage(enterchange[1], "yupic\\tietu33.png");
    getimage(enterchange[2], "yupic\\tietu44.png");
    getimage(background, "yupic\\background.png");        ///��Ϸ����
    getimage(pao, "yupic\\paopao.png");                    ///��������

    getimage(player[0], "yupic\\player1.png");                  ///�����תͼ
    getimage(player[1], "yupic\\player11.png");
    getimage(player[2], "yupic\\player2.png");                     ///�����תͼ

    getimage(player[3], "yupic\\player22.png");
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


    p1size = 55;                      ///��ߴ�
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

    food4.position_x = 1700;             ///�ĺ���
    food4.position_y = rand() % 400;
    food4.v_x = 0.3;

    food5.position_x = 5500;            ///�����
    food5.position_y = rand() % 400;
    food5.v_x = 0.2;

    food6.position_x = -2500;          ///������
    food6.position_y = rand() % 500;
    food6.v_x = 0.2;

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
    mciSendString(TEXT("play backmusic\\music2.mp3 repeat"), NULL, 0, NULL);
    int flag = 0;                        ///������¼�����λ��
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
                    flag = 2;
                }
            }
            else if(lick.x >= 405 && lick.x <= 622 && lick.y >= 299 && lick.y <= 385)
            {
                if(lick.is_down())
                {
                    putimage(309, 300, enterchange[1]);
                    Sleep(300);
                    flag = 3;
                }
                if(lick.is_up())
                {
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
                    flag = 6;
                }
            }

        }
        if(flag == 2)
            break;
        else if(flag == 4)
        {
            mciSendString(TEXT("stop backmusic\\music2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\music3.mp3"), NULL, 0, NULL);
        }
        else if(flag == 6)
        {
            mciSendString(TEXT("stop backmusic\\music2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\music1.mp3"), NULL, 0, NULL);
        }

    }
}


void initdata1()    ///���±���
{
    mciSendString(TEXT("stop backmusic\\music2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play backmusic\\huankuai.mp3 repeat"), NULL, 0, NULL);
    endtime = fclock();
    resttime = timelong - (endtime - starttime)/1000.0;
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
    //for(int i = 0 , j = 0; i < 1000 , j < 600; i += 177 , j += 70)
    putimage(food1.position_x, food1.position_y, numfish[0], SRCAND);   ///����תһ������ʾ����
    putimage(food8.position_x, food8.position_y, numfish[7], SRCAND);   ///��תһ�����ӡ
    //putimage(food1.position_x + 77, food1.position_y + 70, numfish[1], SRCAND);   ///����תһ����ּ���չʾ
    putimage(food2.position_x, food2.position_y, numfish[1], SRCAND);     ///������
    putimage(food3.position_x, food3.position_y, numfish[2], SRCAND);     ///������
    putimage(food4.position_x, food4.position_y, numfish[3], SRCAND);     ///�ĺ���
    putimage(food5.position_x, food5.position_y, numfish[4], SRCAND);     ///�����
    putimage(food6.position_x, food6.position_y, numfish[5], SRCAND);             ///������
    putimage(food7.position_x, food7.position_y, numfish[6], SRCAND);             ///�ߺ���
    putimage(zhadan.position_x, zhadan.position_y, boom[0], SRCAND);      ///ը��
    putimage(timer.position_x, timer.position_y, alarm[0], SRCAND);       ///����
    putimage(paopao.position_x, paopao.position_y , pao, SRCAND);         ///�µ�����
}


void initdata2()    ///�����㣨��̬ת����(ʹ������ʱ����ʾ�ĸ�����ʵ��
{
    if(yuturn == 0)
        putimage(players.position_x, players.position_y, player[2], SRCAND);
    else
        putimage(players.position_x, players.position_y, player[0], SRCAND);
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
        food1.position_y = rand() % 500;                  ///����1�����ظ�����
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
        food5.position_x = 5000;
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
        timer.position_x = -9000;             ///���ӳ���һ�κ������ظ�����
        timer.position_y = rand() % 500;       ///�任���꣬ʹ���´γ���ʱ��ļ������
    }

    zhadan.position_x = zhadan.position_x + zhadan.v_x;     ///ը�������ƶ�
    if(zhadan.position_x < 0)                               ///��������³���
    {
        zhadan.position_x = 5000;
        zhadan.position_y = rand() % 600;
    }


    ///�жϳԵ�����������ĵ�λ�������ķ�Χ��ʱ���Ե�
    if((timer.position_x + 45/2.0/*���ӳߴ�*/ >= players.position_x) && (timer.position_x + 45/2.0<= players.position_x + p1size)
            && (timer.position_y + 25 >= players.position_y + 20) && (timer.position_y + 25 <= players.position_y + p1size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
        socre_p1 += 5;                                           ///�Ե����ӷ�����5
        timer.position_x = -10000;
        timer.position_y = rand() % (high - 45);                    ///��ҳԵ�����
       // mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
    }

    if((zhadan.position_x + 45/2.0/*ը���ߴ�*/ >= players.position_x) && (zhadan.position_x + 45/2.0 <= players.position_x +p1size)
            && (zhadan.position_y + 25 >= players.position_y) && (zhadan.position_y + 25 <= players.position_y + p1size))
    {
        alive--;
        zhadan.position_x = -1000;                        ///��ҳԵ�ը��
        zhadan.position_y = rand() % (high - 45);
    }

    if((food1.position_x + 50/2.0/*��תС��ߴ�*/ >= players.position_x && food1.position_x + 50/2.0 <= players.position_x + p1size)
            && (food1.position_y + 25/2.0 >= players.position_y) && (food1.position_y + 25/2.0 <= players.position_y + p1size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
        p1size += 0.5;
        socre_p1 += 10;                                                      ///�Ե�С�������10
        food1.position_x = -300;
        food1.position_y = rand() % (high - 25);                          ///��תС�㱻�ԣ�������������
    }

    if((food8.position_x + 50/2.0/*��תС��ߴ�*/>= players.position_x && food8.position_x + 50/2.0 <= players.position_x + p1size)
            && (food8.position_y + 25/2.0 >= players.position_y) && (food8.position_y + 25/2.0 <= players.position_y + p1size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
        p1size += 0.5;
        socre_p1 +=10;                                                        ///�Ե���תС�������10
        food8.position_x = 1300;
        food8.position_y = rand() % (high - 25);
    }

    if(p1size > 65)                            ///��С�ﵽ�ܳԵ�������
    {
        if((food2.position_x + 20/*������ߴ�*/ >= players.position_x && food2.position_x + 20 <= players.position_x + p1size)
                && (food2.position_y >= players.position_y && food2.position_y <= players.position_y + p1size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size += 1;
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
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;     ///�������
            players.position_y = high / 2.0;
        }
    }


    if(p1size > 75)                              ///��С�ﵽ�ܳ����ź��ߺź�����
    {
        if((food3.position_x + 80/2.0/*������ߴ�һ��*/ >= players.position_x) && (food3.position_x + 80/2.0 <= players.position_x + p1size)
                && (food3.position_y + 70/2.0 >= players.position_y && (food3.position_y + 70/2.0 <= players.position_y + p1size)))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size += 2;
            socre_p1 += 30;                                   ///�Ե������������30
            food3.position_x = 1500;                        ///����������
            food3.position_y = rand() % (high - 70);
        }

        if((food7.position_x + 80/2.0 /*�ߺź�����ߴ�һ��*/>= players.position_x) && (food7.position_x + 80/2.0 <= players.position_x + p1size)
                && (food7.position_y + 70/2.0 >= players.position_y) && (food7.position_y + 70/2.0 <= players.position_y + p1size))
           {
               mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
               mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
               mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
               p1size += 1.5;
               socre_p1 += 30;                                   ///�Ե��ߺ��������30
               food7.position_x = -500;                      ///�ߺ�������
               food7.position_y = rand() % (high - 70);
           }
    }
    else                                         ///û�ﵽ���������Ÿ��ߺ����򱻳�
    {
        if((players.position_x + p1size/2.0 >= food3.position_x) && (players.position_x + p1size/2.0 <= food3.position_x + 80)
                && (players.position_y + p1size/2.0 >= food3.position_y) && (players.position_y + p1size/2.0 >= food3.position_y + 70))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;            ///��ұ����ųԵ�����
            players.position_y = high / 2.0;
        }

        if((players.position_x + p1size/2.0 >= food7.position_x) && (players.position_x + p1size/2.0 <= food7.position_x + 80)
                && (players.position_y + p1size/2.0 >= food7.position_y) && (players.position_y + p1size/2.0 >= food7.position_y +70))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high / 2.0;              ///��ұ��ߺź�����Ե�����
        }
    }


    if(p1size > 90)                              ///��С�ﵽ�ܳ��ĺ���
    {
        if((food4.position_x + 105/2.0/*�ĺ���ߴ�*/ >= players.position_x) && (food4.position_x + 105/2.0 <= players.position_x + p1size)
                && (food4.position_y + 70/2.0 >= players.position_y) && (food4.position_y + 70/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size += 3.5;
            socre_p1 += 40;                                      ///�Ե��ĺ��������40
            food4.position_x = 1700;                          ///�ĺ�������
            food4.position_y = rand() & (high - 70);
        }
    }
    else                                         ///û�ﵽ�������ĺ����򱻳�
    {
        if((players.position_x + p1size/2.0 >= food4.position_x) && players.position_x + p1size/2.0 <= food4.position_x + 105
                && (players.position_y + p1size/2.0 >= food4.position_y) && (players.position_y + p1size/2.0 <= food4.position_y + 70))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;            ///��ұ�������
            players.position_y = high / 2.0;
        }
    }


    if(p1size > 105)                              ///��С�ﵽ�ܳ�������
    {
        if((food6.position_x + 150/2.0/*������ߴ�һ��*/ >= players.position_x)&& (food6.position_x + 150/2.0 <= players.position_x + p1size)
               && (food6.position_y + 110/2.0 >= players.position_y) && (food6.position_y + 110/2.0 <= players.position_y + p1size))
        {
           mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
           mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
           mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
           p1size += 4;
           socre_p1 += 50;                                  ///�Ե������������50
           food6.position_x = -2000;
           food6.position_y = rand() % 400;             ///����������
        }
    }
    else                                            ///û�ﵽ�������������򱻳�
    {
        if((players.position_x + p1size/2.0 >= food6.position_x) && (players.position_x + p1size/2.0 <= food6.position_x + 150)
               && (players.position_y + p1size/2.0 >= food6.position_y) && (players.position_y + p1size/2.0 <= food6.position_y + 110))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high / 2.0;          ///��������ұ�������
        }
    }


    if(p1size > 135)                             ///��Ҵ�С�ﵽ���������
    {
        if((food5.position_x + 210/2.0/*�����һ��ߴ�*/ >= players.position_x) && (food4.position_x + 210/2.0 <= players.position_x + p1size)
                && (food5.position_y + 100/2.0 >= players.position_y) && (food5.position_y + 100/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size += 5;
            socre_p1 += 60;                                             ///�Ե�����������60
            food5.position_x = 4500;                              ///���������
            food5.position_y = rand() % (high - 100);
        }
    }
    else                                         ///û�ﵽ������������򱻳�
    {
        if((players.position_x + p1size/2.0 >= food5.position_x) && (players.position_x + p1size/2.0 <= food5.position_x + 210)
                && (players.position_y + p1size/2.0 >= food5.position_y) && (players.position_y + p1size/2.0 <= food5.position_y + 100))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);
            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high / 2.0;                  ///��ұ������Ա�����
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

void gameover()
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
    formbackground();
    while(1)
    {
        initdata1();
        initdata2();
        data_withoutinput();
        data_withinput();
        Sleep(1);                ///�����ͼƬ�л�ʱ����������
        cleardevice();
    }
    gameover();
    return 0;
}






