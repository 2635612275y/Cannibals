#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define length 1000   /// 游戏窗口
#define high 640
#define fishnum 5      ///游戏鱼的数量
#define changenum 10      ///输出图形产生动态效果的数量
PIMAGE enter, background, player[changenum];
PIMAGE numfish[fishnum];

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
yu food1;///1号鱼
yu food2;///2号鱼
yu food3;///3号鱼
yu food4;///4号鱼
yu food5;///5号鱼

int yuturn = 0;           ///判断鱼是否掉头   1  掉头，   0 不掉头

double p1size;           ///储存鱼尺寸
double strat_p1size;    ///储存鱼的初始大小

void every_data()         ///初始数据
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
    getimage(numfish[0], "yupic\\oneyu1.png");   ///左转一号鱼
    getimage(numfish[1], "yupic\\oneyu2.png");   ///右转一号鱼
    p1size = 45;                     ///鱼尺寸
    strat_p1size = p1size;          ///鱼初始尺寸
    players.position_x = length/2.0;   ///玩家坐标
    players.position_y = high/2.0;
    players.v_x = 0.77;              ///玩家速度
    players.v_y = 0.77;

    food1.position_x = 0;           ///1号鱼横坐标
	food1.position_y = rand() % 500;    ///1号鱼纵坐标随机设定
	food1.v_x = 0.3;                  ///1号鱼速度

}

void initdata1()    ///更新背景
{
    putimage(0, 0, background);
    putimage(food1.position_x, food1.position_y, numfish[1]);
}
void initdata2()    ///更新鱼（动态转换）
{
        if(yuturn == 0)
            putimage(players.position_x, players.position_y, player[0]);
        else
            putimage(players.position_x, players.position_y, player[2]);
}

void data_withoutinput()  ///没有数据输入时
{
       food1.position_x = food1.position_x + food1.v_x;         ///1号鱼向右移动
       if(food1.position_x > length)
	    {
		food1.position_x = -400;
		food1.position_y = rand() % 500;      ///1号鱼重复出现
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
        Sleep(1);        ///解决对图片切换时的闪屏问题
    }
    gameover();
    return 0;
}




