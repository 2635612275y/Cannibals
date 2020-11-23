#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>


#define length 1000   /// 游戏窗口
#define high 640
#define fishnum 9      ///游戏鱼的数量
#define changenum 12      ///输出图形产生动态效果的数量
#define boomnum 2          ///炸弹数量
#define alarmnum 2      ///闹钟数量

PIMAGE enter, enterchange[3], background, player[changenum];
PIMAGE numfish[fishnum], boom[boomnum], alarm[alarmnum];
PIMAGE pao, wancheng;
PIMAGE background2, background3, gameover;

typedef struct games
{
    double position_x;   ///横坐标
    double position_y;    ///纵坐标
    double v_x;      ///水平速度
    double v_y;      ///竖直速度
} yu;


yu players;///玩家
yu timer;///闹钟
yu zhadan;///随机炸弹
yu food1;///右转1号鱼
yu food2;///2号鱼
yu food3;///3号鱼
yu food4;///4号鱼
yu food5;///5号鱼
yu food6;///6号鱼
yu food7;///7号海马鱼
yu food8;///左转1号鱼
yu paopao;///泡泡


int yuturn = 0;             ///判断鱼是否掉头   1  掉头左，   0 不掉头右
int backchange = 0;              ///判断背景是否变换            0 为初始菜单页面 1为菜单1 2为菜单2
int goback = 0;            ///菜单页面回到初始                0为初始菜单页面   1为菜单1    2为菜单2

double p1size;             ///储存鱼尺寸
double start_p1size;      ///储存鱼的初始大小
int alive = 3;            ///玩家生命
int gamestatus = 0;       ///游戏状态， 0 为正常游戏，1 为结束游戏状态，2 为游戏暂停
double starttime;              ///计时
double endtime;                ///计时
double timelong = 150.0;       ///游戏时间限制
double resttime;          ///游戏剩余时间
int  socre_p1 = 0;         ///游戏分数
int flag = 0;                        ///用来记录鼠标点击位置
char remake;              ///游戏重开


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


void playmusic()             ///打开音乐文件夹
{
    mciSendString(TEXT("open backmusic\\bit.mp3"), NULL, 0, NULL);                    ///加载各音乐
    mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music1.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music2.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music3.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\huankuai.mp3"),NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\baozha.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("open backmusic\\music5.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("opne backmusic\\music6.mp3"), NULL, 0, NULL);
}

void every_data()            ///初始数据
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

    getimage(enter, "yupic\\background1.png");    ///进场页面
    getimage(background2, "yupic\\background3.png");   ///菜单1页面
    getimage(background3, "yupic\\background4.png");   ///菜单2页面

    getimage(wancheng, "yupic\\wancheng.png");
    getimage(gameover, "yupic\\gameover.png");       ///游戏结束页面

    getimage(enterchange[0], "yupic\\tietu22.png");      ///鼠标停留点击进场地方图片变化
    getimage(enterchange[1], "yupic\\tietu33.png");
    getimage(enterchange[2], "yupic\\tietu44.png");

    getimage(background, "yupic\\background.png");        ///游戏背景
    getimage(pao, "yupic\\paopao.png");                    ///鱼吐泡泡

    getimage(player[0], "yupic\\players11.png");                  ///玩家1右转图
    getimage(player[1], "yupic\\players22.png");                  ///玩家2
    getimage(player[2], "yupic\\players33.png");                  ///玩家3
    getimage(player[3], "yupic\\players44.png");                  ///玩家4
    getimage(player[4], "yupic\\players55.png");                  ///玩家5
    getimage(player[5], "yupic\\players66.png");                  ///玩家6

    getimage(player[6], "yupic\\players1.png");                  ///玩家1左转图
    getimage(player[7], "yupic\\players2.png");                  ///玩家2
    getimage(player[8], "yupic\\players3.png");                  ///玩家3
    getimage(player[9], "yupic\\players4.png");                  ///玩家4
    getimage(player[10], "yupic\\players5.png");                  ///玩家5
    getimage(player[11], "yupic\\players6.png");                  ///玩家6


    getimage(numfish[0], "yupic\\oneyu2.png");   ///右转一号鱼

    getimage(numfish[7], "yupic\\oneyu1.png");    ///左转一号鱼

    getimage(numfish[1], "yupic\\twoyu1.png");   ///左转二号鱼

    getimage(numfish[2], "yupic\\threeyu1.png");  ///左转三号鱼

    getimage(numfish[3], "yupic\\fouryu1.png");   ///左转四号鱼

    getimage(numfish[4], "yupic\\fiveyu11.png");   ///右转五号鱼

    getimage(numfish[5], "yupic\\sixyu.png");        ///右转六号鱼

    getimage(numfish[6], "yupic\\sevenyu.png");       ///右转七号海马

    getimage(alarm[0], "yupic\\naozhong.png");     ///闹钟
    getimage(boom[0], "yupic\\zhadan.png");        ///炸弹


    p1size = 60;                      ///鱼尺寸
    start_p1size = p1size;             ///鱼初始尺寸,赋值存放，防止下次变值

    starttime = fclock();

    players.position_x = length/2.0;   ///玩家坐标
    players.position_y = high/2.0;
    players.v_x = 0.77;              ///玩家速度
    players.v_y = 0.77;

    paopao.position_x = players.position_x;    ///泡泡坐标为鱼的坐标
    paopao.position_y = players.position_y;
    paopao.v_y = 0.2;                          ///泡泡上升速度

    food1.position_x = 0;           ///右转1号鱼横坐标
    food1.position_y = rand() % 400;    ///右转1号鱼纵坐标随机设定
    food1.v_x = 0.5;                  ///右转1号鱼速度

    food8.position_x = 1000;           ///左转1号鱼横坐标
    food8.position_y = rand() % 400;    ///左转1号鱼纵坐标随机设定
    food8.v_x = 0.5;                  ///左转1号鱼速度

    food2.position_x = 1200;        ///二号鱼坐标
    food2.position_y = rand() % 400;
    food2.v_x =0.4;

    food3.position_x = 1300;            ///三号鱼坐标
    food3.position_y = rand() % 400;
    food3.v_x = 0.35;

    food4.position_x = 1500;             ///四号鱼
    food4.position_y = rand() % 400;
    food4.v_x = 0.4;

    food5.position_x = 3000;            ///五号鱼
    food5.position_y = rand() % 400;
    food5.v_x = 0.6;

    food6.position_x = -1500;          ///六号鱼
    food6.position_y = rand() % 500;
    food6.v_x = 0.4;

    food7.position_x = -500;
    food7.position_y = rand() % 500;      ///七号海马鱼
    food7.v_x = 0.3;

    timer.position_x = -2000;     ///闹钟横坐标  ///从左边往右走
    timer.position_y = rand() % 600; ///闹钟纵坐标随机设定
    timer.v_x = 0.5;    ///闹钟速度

    zhadan.position_x = -500; ///炸弹横坐标
    zhadan.position_y = rand() % 400;
    zhadan.v_x = 0.3;



}

void formbackground()   ///进场页面
{

    mouse_msg lick = {0};
    while(1)
    {
        putimage(0, 0, enter);                   ///进场页面
        while(mousemsg())
        {
            lick = getmouse();
            if(lick.x >= 404 && lick.x <= 622 && lick.y >= 179 && lick.y <= 266)        ///获取鼠标点击位置
            {
                if(lick.is_down())
                {
                    putimage(622, 180, enterchange[2]);                           ///点击板块图像变化
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
                    backchange = 1;                ///操作说明背景标记
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
                    backchange = 2;                ///游戏介绍背景标记
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
        putimage(0, 0, background2);                   ///操作说明页面

        setbkmode(TRANSPARENT);
        setcolor(RED);
        setfont(50, 0, "楷体");
        xyprintf(320, 40, "游 戏 操 作 说 明");
        setcolor(GREEN);
        setfont(30, 0, "楷体");
        xyprintf(380, 180, "↑ ↓ ← → 控制小鱼移动");
        xyprintf(290, 280, "按P键可使游戏暂停, 继续游戏按Esc键");
        setcolor(RED);
        setfont(30, 0, "楷体");
        xyprintf(220, 400, "返回菜单");
        xyprintf(760, 400, "进入游戏");
        Sleep(1);

        mouse_msg lick_put = {0};                                  ///获取菜单页1的鼠标点击信息
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
        putimage(0, 0, background3);                ///游戏介绍背景页面

        setbkmode(TRANSPARENT);
        setcolor(RED);
        setfont(50, 0, "楷体");
        xyprintf(320, 40, "游 戏 操 作 说 明");
        setcolor(GREEN);
        setfont(30, 0, "楷体");
        xyprintf(380, 180, "↑ ↓ ← → 控制小鱼移动");
        xyprintf(290, 280, "按P键可使游戏暂停, 继续游戏按Esc键");
        xyprintf(500, 400, "返回菜单");
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

void initdata1()    ///更新背景
{
    mciSendString(TEXT("close backmusic\\music5.mp3"), NULL, 0, NULL);              ///播放菜单页面音乐3
    mciSendString(TEXT("close backmusic\\music1.mp3"), NULL, 0, NULL);              ///播放菜单页面音乐2
    mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///关闭菜单页面音乐1
    mciSendString(TEXT("play backmusic\\huankuai.mp3 repeat"), NULL, 0, NULL);              ///播放进入游戏页面音乐4

    endtime = fclock();
    resttime = timelong - (endtime - starttime)/1000.0;
    if(backchange == 0)
    putimage(0, 0, background);                          ///游戏背景

    setbkmode(TRANSPARENT);                         ///游戏分数
    setcolor(RED);                                   ///字体颜色
    setfont(25, 0, "楷体");                          ///字体大小与种类

    xyprintf(65, 10, "Score");
    xyprintf(80, 45, "%d", socre_p1);              ///分数

    xyprintf(415, 10, "resttime");                 ///剩余时间
    xyprintf(415, 45, "%d", resttime);

    xyprintf(750, 10, "The remaining life");
    xyprintf(860, 45, "%d", alive);                  ///生命

    putimage(food1.position_x, food1.position_y, numfish[0], SRCAND);   ///将右转一号鱼显示出来
    putimage(food8.position_x, food8.position_y, numfish[7], SRCAND);   ///左转一号鱼打印
    putimage(food2.position_x, food2.position_y, numfish[1], SRCAND);     ///二号鱼
    putimage(food3.position_x, food3.position_y, numfish[2], SRCAND);     ///三号鱼
    putimage(food4.position_x, food4.position_y, numfish[3], SRCAND);     ///四号鱼
    putimage(food5.position_x, food5.position_y, numfish[4], SRCAND);     ///五号鱼
    putimage(food6.position_x, food6.position_y, numfish[5], SRCAND);             ///六号鱼
    putimage(food7.position_x, food7.position_y, numfish[6], SRCAND);             ///七号鱼
    putimage(zhadan.position_x, zhadan.position_y, boom[0], SRCAND);      ///炸弹
    putimage(timer.position_x, timer.position_y, alarm[0], SRCAND);       ///闹钟

    putimage(paopao.position_x, paopao.position_y , pao, SRCAND);         ///吐的泡泡
    putimage(paopao.position_x, paopao.position_y - 30, pao, SRCAND);
}


void initdata2()    ///更新鱼（动态转换）(使鱼吃鱼的时候显示的更加真实）
{
    if(yuturn == 0)                       ///进行鱼变大变化
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
    if(kbhit())                                            ///游戏暂停操作
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


void data_withoutinput()  ///没有数据输入时
{
    paopao.position_y = paopao.position_y - paopao.v_y;         ///泡泡上升
    if(paopao.position_y < 0)
    {
        paopao.position_x = players.position_x;                 ///泡泡重复出现
        paopao.position_y = players.position_y;
    }

    food1.position_x = food1.position_x + food1.v_x;             ///1号鱼向右移动
    if(food1.position_x > length)
    {
        food1.position_x = -400;
        food1.position_y = rand() % 500;                        ///向右1号鱼重复出现
    }

    food8.position_x = food8.position_x - food8.v_x;              ///一号鱼向左移动
    if(food8.position_x < 0)
    {
        food8.position_x = 1000;
        food8.position_y = rand() % 400;                       ///向左移动一号鱼重复出现
    }

    food2.position_x = food2.position_x - food2.v_x;       ///二号鱼向左移动
    if(food2.position_x < 0)
    {
        food2.position_x = 1900;
        food2.position_y = rand() % 400;                   ///二号鱼重复出现
    }

    food3.position_x = food3.position_x - food3.v_x;       ///三号鱼向左移动
    if(food3.position_x < 0)
    {
        food3.position_x = 2500;
        food3.position_y = rand() % 400;                    ///四号鱼重出现
    }

    food4.position_x = food4.position_x - food4.v_x;        ///四号鱼向左移动
    if(food4.position_x < 0)
    {
        food4.position_x = 2800;
        food4.position_y = rand() % 400;                  ///四号鱼重复出现
    }

    food5.position_x = food5.position_x - food5.v_x;         ///五号鱼向左移动
    if(food5.position_x < 0)
    {
        food5.position_x = 3200;
        food5.position_y = rand() % 400;                     ///五号鱼重复出现
    }

    food6.position_x = food6.position_x + food6.v_x;          ///六号鱼向右移动
    if(food6.position_x > length)
    {
        food6.position_x = -2500;
        food6.position_y = rand() % 500;                                ///六号鱼重复出现
    }

    food7.position_x = food7.position_x + food7.v_x;             ///七号鱼向右移动
    if(food7.position_x > length)
    {
        food7.position_x = -600;
        food7.position_y = rand() % 400;                        ///七号鱼重复出现

    }

    timer.position_x = timer.position_x + timer.v_x;         ///闹钟向右移动
    if(timer.position_x > length)
    {
        timer.position_x = -2000;             ///闹钟出现一次后让它重复出现
        timer.position_y = rand() % 500;       ///变换坐标，使到下次出现时间的间隔长点
    }

    zhadan.position_x = zhadan.position_x + zhadan.v_x;     ///炸弹向右移动
    if(zhadan.position_x > length)                               ///出界后重新出现
    {
        zhadan.position_x = -1000;
        zhadan.position_y = rand() % 600;
    }


    ///判断吃的情况，当中心点位于玩家鱼的范围内时被吃掉
    if((timer.position_x + 45/2.0/*闹钟尺寸*/ >= players.position_x) && (timer.position_x + 45/2.0<= players.position_x + p1size)
            && (timer.position_y + 25 >= players.position_y + 20) && (timer.position_y + 25 <= players.position_y + p1size))
    {
        mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        socre_p1 += 5;                                           ///吃掉闹钟分数加5
        timer.position_x = -10000;
        timer.position_y = rand() % (high - 45);                    ///玩家吃掉闹钟
    }

    if((zhadan.position_x + 45/2.0/*炸弹尺寸*/ >= players.position_x) && (zhadan.position_x + 45/2.0 <= players.position_x +p1size)
            && (zhadan.position_y + 25 >= players.position_y) && (zhadan.position_y + 25 <= players.position_y + p1size))
    {
        mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);              ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("close backmusic\\baozha.mp3"), NULL, 0, NULL);         ///每次在打开前关闭炸弹音效
        mciSendString(TEXT("play backmusic\\baozha.mp3"), NULL, 0, NULL);

        alive--;
        p1size = start_p1size;
        players.position_x = length / 2.0;
        players.position_y = high - 100;                        ///吃掉炸弹玩家重置
        zhadan.position_x = -1000;                          ///玩家吃掉炸弹
        zhadan.position_y = rand() % (high - 45);
    }

    if((food1.position_x + 50/2.0/*右转小鱼尺寸*/ >= players.position_x && food1.position_x + 50/2.0 <= players.position_x + p1size)
            && (food1.position_y + 25/2.0 >= players.position_y) && (food1.position_y + 25/2.0 <= players.position_y + p1size))
    {
        mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p1size += 2;
        socre_p1 += 10;                                                      ///吃掉小鱼分数加10
        food1.position_x = -300;
        food1.position_y = rand() % (high - 25);                          ///右转小鱼被吃，立马重新生成
    }

    if((food8.position_x + 50/2.0/*左转小鱼尺寸*/>= players.position_x && food8.position_x + 50/2.0 <= players.position_x + p1size)
            && (food8.position_y + 25/2.0 >= players.position_y) && (food8.position_y + 25/2.0 <= players.position_y + p1size))
    {
        mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);                   ///关闭被吃音效
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);                 ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p1size += 2;
        socre_p1 +=10;                                                                ///吃掉左转小鱼分数加10
        food8.position_x = 1300;
        food8.position_y = rand() % (high - 25);
    }

    if(p1size > 65)                            ///大小达到能吃掉二号鱼
    {
        if((food2.position_x + 20/*二号鱼尺寸*/ >= players.position_x && food2.position_x + 20 <= players.position_x + p1size)
                && (food2.position_y >= players.position_y && food2.position_y <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 3;
            socre_p1 += 20;                                               ///吃掉二号鱼分数加20
            food2.position_x = 1200;
            food2.position_y = rand() % (high - 40);
        }
    }
    else                                        ///没达到，遇到二号鱼则被吃
    {
        if((players.position_x + p1size/2.0/*玩家自身尺寸一半*/ >= food2.position_x && players.position_x + p1size/2.0 <= food2.position_x + 65)
                && (players.position_y + p1size/2.0 >= food2.position_y && players.position_y + p1size/2.0 <= food2.position_y + 40))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);            ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;     ///玩家重置
            players.position_y = high - 100;
        }
    }


    if(p1size > 75)                              ///大小达到能吃三号和七号海马鱼
    {
        if((food3.position_x + 80/2.0/*三号鱼尺寸一半*/ >= players.position_x ) && (food3.position_x + 80/2.0 <= players.position_x + p1size)
                && (food3.position_y + 70/2.0 >= players.position_y )  && (food3.position_y + 70/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);                  ///关闭被吃音效
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                 ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);               ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 3;
            socre_p1 += 30;                                   ///吃掉三号鱼分数加30
            food3.position_x = 1500;                        ///三号鱼重置
            food3.position_y = rand() % (high - 70);
        }

        if((food7.position_x + 80/2.0 /*七号海马鱼尺寸一半*/>= players.position_x) && (food7.position_x + 80/2.0 <= players.position_x + p1size)
                && (food7.position_y + 70/2.0 >= players.position_y) && (food7.position_y + 70/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);                ///关闭被吃音效
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);              ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 4;
            socre_p1 += 30;                                   ///吃掉七号鱼分数加30
            food7.position_x = -500;                      ///七号鱼重置
            food7.position_y = rand() % (high - 70);
        }
    }
    else                                         ///没达到，遇到三号跟七号鱼则被吃
    {
        if((players.position_x + p1size/2.0 >= food3.position_x) && (players.position_x + p1size/2.0 <= food3.position_x + 80)
                && (players.position_y + p1size/2.0 >= food3.position_y) && (players.position_y + p1size/2.0 <= food3.position_y + 70))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;            ///玩家被三号吃掉重置
            players.position_y = high - 100;
        }

        if((players.position_x + p1size/2.0 >= food7.position_x) && (players.position_x + p1size/2.0 <= food7.position_x + 80)
                && (players.position_y + p1size/2.0 >= food7.position_y) && (players.position_y + p1size/2.0 <= food7.position_y +70))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;              ///玩家被七号海马鱼吃掉重置
        }
    }


    if(p1size > 90)                              ///大小达到能吃四号鱼
    {
        if((food4.position_x + 105/2.0/*四号鱼尺寸*/ >= players.position_x) && (food4.position_x + 105/2.0 <= players.position_x + p1size)
                && (food4.position_y + 70/2.0 >= players.position_y) && (food4.position_y + 70/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 4;
            socre_p1 += 40;                                      ///吃掉四号鱼分数加40
            food4.position_x = 1700;                          ///四号鱼重置
            food4.position_y = rand() & (high - 70);
        }
    }
    else                                         ///没达到，遇到四号鱼则被吃
    {
        if((players.position_x + p1size/2.0 >= food4.position_x) && (players.position_x + p1size/2.0 <= food4.position_x + 105)
                && (players.position_y + p1size/2.0 >= food4.position_y) && (players.position_y + p1size/2.0 <= food4.position_y + 70))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;            ///玩家被吃重置
            players.position_y = high - 100;
        }
    }


    if(p1size > 105)                              ///大小达到能吃六号鱼
    {
        if((food6.position_x + 150/2.0/*六号鱼尺寸一半*/ >= players.position_x)&& (food6.position_x + 150/2.0 <= players.position_x + p1size)
                && (food6.position_y + 110/2.0 >= players.position_y) && (food6.position_y + 110/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 4;
            socre_p1 += 50;                                  ///吃掉六号鱼分数加50
            food6.position_x = -1200;
            food6.position_y = rand() % 400;             ///六号鱼重置
        }
    }
    else                                            ///没达到，遇到六号鱼则被吃
    {
        if((players.position_x + p1size/2.0 >= food6.position_x) && (players.position_x + p1size/2.0 <= food6.position_x + 150)
                && (players.position_y + p1size/2.0 >= food6.position_y) && (players.position_y + p1size/2.0 <= food6.position_y + 110))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;          ///不够吃玩家被吃重置
        }
    }


    if(p1size > 135)                             ///玩家大小达到够吃五号鱼
    {
        if((food5.position_x + 275/2.0/*五号鱼一半尺寸*/ >= players.position_x) && (food4.position_x + 275/2.0 <= players.position_x + p1size)
                && (food5.position_y + 125/2.0 >= players.position_y) && (food5.position_y + 125/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("open backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 5;
            socre_p1 += 60;                                             ///吃掉五号鱼分数加60
            food5.position_x = 4000;                                 ///五号鱼重置
            food5.position_y = rand() % (high - 100);
        }
    }
    else                                         ///没达到，遇到五号鱼则被吃
    {
        if((players.position_x + p1size/2.0 >= food5.position_x) && (players.position_x + p1size/2.0 <= food5.position_x + 275)
                && (players.position_y + p1size/2.0 >= food5.position_y) && (players.position_y + p1size/2.0 <= food5.position_y + 125))
        {
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;                  ///玩家被五号鱼吃被重置
        }
    }
}


void data_withinput()   ///有数据输入时
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (players.position_x > 0))
    {
        yuturn = 1;                                   ///左转
        players.position_x = players.position_x - players.v_x;
    }

    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (players.position_x < length - 45))    ///防止右转出界
    {
        yuturn = 0;                                          ///右转
        players.position_x = players.position_x + players.v_x;
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  players.position_y > 0)
        players.position_y = players.position_y - players.v_y;             ///上移
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  players.position_y < high - 45)         ///防止左转出界
        players.position_y = players.position_y + players.v_y;            ///下移
}


void background_over()    ///游戏结束背景
{
    putimage(0, 0, gameover);
    mciSendString(TEXT("stop backmusic\\huankuai.mp3"), NULL, 0, NULL);    ///暂停关闭游戏音乐
    mciSendString(TEXT("close backmusic\\huankuai.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play backmusic\\music3.mp3"), NULL, 0, NULL);       ///打开游戏结束背景音乐

    setbkmode(TRANSPARENT);                                              ///游戏结束背景字
    setcolor(YELLOW);
    setfont(50, 0, "楷体");
    xyprintf(120, 20, "得 分");
    xyprintf(147, 80, "%d", socre_p1);
    xyprintf(300, 100, "G A M E   O V E R");
    xyprintf(340, 200, "~~~oo(^_^)oo~~~");
    xyprintf(380, 290, "请继续努力!!");
    xyprintf(430, 370, "可怜的");
    xyprintf(305, 450, "。。。小鱼。。。");
    Sleep(10000);                                                 ///暂时暂停等待下一步按键
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
        mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///关闭菜单页面音乐1
        mciSendString(TEXT("play backmusic\\music1.mp3 repeat"), NULL, 0, NULL);              ///播放菜单页面音乐2

        background_1();

        if(backchange == 0 && goback == 0)
        mciSendString(TEXT("close backmusic\\music1.mp3"), NULL, 0, NULL);
    }


    if(backchange == 2 && goback == 2)
    {
        mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///关闭菜单页面音乐1
        mciSendString(TEXT("play backmusic\\music5.mp3 repeat"), NULL, 0, NULL);              ///播放菜单页面音乐3

        background_2();

        if(backchange == 0 && goback == 0)
        mciSendString(TEXT("close backmusic\\music5.mp3"), NULL, 0, NULL);
    }
    if(flag == 2)
        break;                                                     ///是否进入游戏页面
    }
    while(1)
    {
        if((backchange == 0 && gamestatus == 0) || flag == 2)
        {
        initdata1();
        initdata2();

        while(gamestatus == 2)           ///判断游戏是否继续
        restart_menu();

        data_withoutinput();
        data_withinput();
        Sleep(1);                ///解决对图片切换时的闪屏问题
        cleardevice();
        if(alive < 0)
            break;
        }
    }
    while(1)                         ///长时间保留最后页面
    {
        background_over();
    }
    game_over();
    return 0;
}
