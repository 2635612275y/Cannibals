#include <stdio.h>
#include <graphics.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <mmsystem.h>

#define length 1000   /// 游戏窗口
#define high 640
#define fishnum 20      ///游戏鱼的数量
#define changenum 12      ///玩家图片数量
#define boomnum 2          ///炸弹数量
#define alarmnum 2      ///闹钟数量
#define SIZE 10

PIMAGE enterchange[3], player[changenum] /*第一关玩家*/ /*第二关玩家*/, player2[changenum], player3[changenum];
PIMAGE fish1[fishnum]/*第一关鱼*/, fish2[fishnum]/*第二关鱼*/, fish3[fishnum]/*第三关鱼*/;
PIMAGE boom[boomnum], alarm[alarmnum];
PIMAGE pao, wancheng, guanqia[3], next, life;
PIMAGE enter, guanqiaback, background2, background3, gameover;
PIMAGE game1, game2, game3;                   ///游戏第二关第三关

typedef struct games
{
    double position_x;   ///横坐标
    double position_y;    ///纵坐标
    double v_x;      ///水平速度
    double v_y;      ///竖直速度
} yu , yu1, yu2;
/*  第一关   */
yu players;///玩家
yu timer;///闹钟
yu paopao;///泡泡
yu zhadan;///随机炸弹
yu food1;///右转1号鱼
yu food8;///左转1号鱼
yu food2;///2号鱼
yu food3;///3号鱼
yu food4;///4号鱼
yu food5;///5号鱼
yu food6;///6号鱼
yu food7;///7号海马鱼
/*  第二关   */
yu1 players2; ///第二关玩家
yu1 food11;///1号鱼
yu1 food111;///1号鱼
yu1 food1111;///1号鱼
yu1 food22;///2号鱼
yu1 food33;///3号鱼
yu1 food44;///4号鱼
yu1 food55;///5号鱼
yu1 food66;///6号鱼
/*  第三关  */
yu2 players3; ///第二关玩家
yu2 fishone1;///1号鱼
yu2 fishone2;///1号鱼
yu2 fishone3;///1号鱼
yu2 fishtwo;///2号鱼
yu2 fishthree;///3号鱼
yu2 fishfour;///4号鱼
yu2 fishfive;///5号鱼
yu2 fishsix;///6号鱼
yu2 fishseven;///7号鱼
yu2 fisheight;///8号鱼

int yuturn = 0, yuturn1 = 0, yuturn2 = 0 ;             ///判断鱼是否掉头   1  掉头左，   0 不掉头右
int backchange = 0;              ///判断背景是否变换            0 为初始菜单页面 1为菜单1 2为菜单2
int goback = 0;                 ///菜单页面回到初始                0为初始菜单页面   1为菜单1    2为菜单2

double p1size, p2size, p3size;              ///储存鱼尺寸
double start_p1size, start_p2size, start_p3size;      ///储存鱼的初始大小
int alive = 3, alive1 = 3, alive2 = 3;                 ///玩家生命
int gamestatus = 0, gamestatus1 = 0, gamestatus2 = 0;    ///游戏状态， 0 为正常游戏，1 为结束游戏状态，2 为游戏暂停
double starttime, starttime1, starttime2, endtime, endtime1, endtime2;              ///计时
double timelong = 90.0, timelong2 = 80.0, timelong3 = 80.0;                  ///游戏时间限制
double resttime, resttime1, resttime2;          ///游戏剩余时间
int  socre_p1 = 0 , socre_p2 = 0, socre_p3 = 0;         ///游戏分数
int allsocre[SIZE] = {0};
int flag = 0;                        ///是否进入游戏
int passchange = 0;                ///关卡变化 1 第一关 2 第二关 3 第三关

void playmusic();
void every_data1();
void every_data2();
void every_data3();
void formbackground();
void background_1();
void background_2();
void initdata1();
void initdata2();
void initdata3();
void data_withoutinput1();
void data_withinput1();
void data_withoutinput2();
void data_withinput2();
void data_withoutinput3();
void data_withinput3();
void restart_menu1();
void restart_menu2();
void restart_menu3();
void choosepass();
void fistwin();
void secondwin();
void thirdwin();
void background_over();
void game_over();
void WriteFile();
void ReadFile();

void WriteFile()   ///存储游戏分数数据文件存档
{
	FILE *fp1;
	fp1 = fopen("scoredata.txt", "w");
	if(fp1 == NULL)
    {
        printf("error!!\n");
    }
    fwrite(allsocre, sizeof(int), SIZE, fp1);
    fclose(fp1);
}

void ReadFile()  ///读出排行榜
{
	FILE *fp2;
	fp2 = fopen("scoredata.txt","r");
	if(fp2 == NULL)
    {
        printf("error!!\n");
    }
	fread(allsocre, sizeof(int), SIZE, fp2);
	fclose(fp2);
}

void playmusic()             ///打开音乐文件夹
{
    mciSendString(TEXT("open backmusic\\bit.mp3"), NULL, 0, NULL);                    ///加载各音乐
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

void every_data1()
{
    ReadFile();
    wancheng = newimage();
    enter = newimage();
    guanqiaback = newimage();
    game1 = newimage();
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
        fish1[i] = newimage();
    for(int i = 0; i < boomnum; i++)
        boom[i] = newimage();
    for(int i = 0; i< alarmnum; i++)
        alarm[i] = newimage();
    for(int i = 0; i < 3; i++)
        guanqia[i] = newimage();
    getimage(guanqiaback, "yupic\\background.png");   ///关卡背景
    getimage(guanqia[0], "yupic\\pass1.png");   ///关卡1
    getimage(guanqia[1], "yupic\\pass2.png");   ///关卡2
    getimage(guanqia[2], "yupic\\pass3.png");   ///关卡3
    getimage(next, "yupic\\next1.png");          ///下一关
    getimage(enter, "yupic\\background1.png");    ///进场页面
    getimage(background2, "yupic\\background3.png");   ///菜单1页面
    getimage(background3, "yupic\\background4.png");   ///菜单2页面

    getimage(wancheng, "yupic\\wancheng.png");
    getimage(gameover, "yupic\\gameover.png");       ///游戏结束页面

    getimage(enterchange[0], "yupic\\tietu22.png");      ///鼠标停留点击进场地方图片变化
    getimage(enterchange[1], "yupic\\tietu33.png");
    getimage(enterchange[2], "yupic\\tietu44.png");

    getimage(game1, "yupic\\background.png");        ///游戏背景
    getimage(pao, "yupic\\paopao.png");                    ///鱼吐泡泡
    getimage(life, "yupic\\xieliang.png");

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


    getimage(fish1[0], "yupic\\oneyu2.png");   ///右转一号鱼

    getimage(fish1[7], "yupic\\oneyu1.png");    ///左转一号鱼

    getimage(fish1[1], "yupic\\twoyu1.png");   ///左转二号鱼

    getimage(fish1[2], "yupic\\threeyu1.png");  ///左转三号鱼

    getimage(fish1[3], "yupic\\fouryu1.png");   ///左转四号鱼

    getimage(fish1[4], "yupic\\fiveyu11.png");   ///右转五号鱼

    getimage(fish1[5], "yupic\\sixyu.png");        ///右转六号鱼

    getimage(fish1[6], "yupic\\sevenyu.png");       ///右转七号海马

    getimage(alarm[0], "yupic\\naozhong.png");     ///闹钟
    getimage(boom[0], "yupic\\zhadan.png");        ///炸弹


    starttime = clock();               ///计时

    p1size = 60;                      ///鱼尺寸
    start_p1size = p1size;             ///鱼初始尺寸,赋值存放，防止下次变值

    players.position_x = length/2.0;   ///玩家坐标
    players.position_y = high/2.0;
    players.v_x = 0.9;              ///玩家速度
    players.v_y = 0.9;

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
    timer.v_x = 0.7;    ///闹钟速度

    zhadan.position_x = -500; ///炸弹横坐标
    zhadan.position_y = rand() % 400;
    zhadan.v_x = 0.4;

}

void every_data2()
{
    game2 = newimage();
    for(int i = 0; i < fishnum; i++)
        fish2[i] = newimage();
    for(int i = 0; i< changenum; i++)
        player2[i] = newimage();

        getimage(player2[0], "yupic1\\players11.png");   ///玩家右
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

        getimage(fish2[0], "yupic1\\oneyu1.png");   ///左转一号鱼
        getimage(fish2[1], "yupic1\\oneyu2.png");   ///右转一号鱼
        getimage(fish2[2], "yupic1\\oneyu3.png");   ///左转一号鱼
        getimage(fish2[3], "yupic1\\twoyu.png");
        getimage(fish2[4], "yupic1\\threeyu.png");
        getimage(fish2[5], "yupic1\\fouryu.png");
        getimage(fish2[6], "yupic1\\fiveyu.png");
        getimage(fish2[7], "yupic1\\sixyu.png");

        getimage(game2, "yupic1\\bei1.png");

        starttime1 = clock();

    p2size = 60;                      ///鱼尺寸
    start_p2size = p2size;             ///鱼初始尺寸,赋值存放，防止下次变值

    players2.position_x = length/2.0;   ///玩家坐标
    players2.position_y = high/2.0;
    players2.v_x = 0.9;              ///玩家速度
    players2.v_y = 0.9;

    paopao.position_x = players2.position_x;    ///泡泡坐标为鱼的坐标
    paopao.position_y = players2.position_y;
    paopao.v_y = 0.2;                          ///泡泡上升速度

    food11.position_x = 0;           ///右转1号鱼横坐标
    food11.position_y = rand() % 400;    ///右转1号鱼纵坐标随机设定
    food11.v_x = 0.7;                  ///右转1号鱼速度

    food111.position_x = 1000;           ///左转1号鱼横坐标
    food111.position_y = rand() % 400;    ///左转1号鱼纵坐标随机设定
    food111.v_x = 0.8;                  ///左转1号鱼速度

    food1111.position_x = -500;
    food1111.position_y = rand() % 500;      ///左转一号鱼
    food1111.v_x = 0.7;

    food22.position_x = 1200;        ///二号鱼坐标
    food22.position_y = rand() % 400;
    food22.v_x =0.6;

    food33.position_x = 1200;            ///三号鱼坐标
    food33.position_y = rand() % 400;
    food33.v_x = 0.55;

    food44.position_x = -1800;             ///四号鱼
    food44.position_y = rand() % 400;
    food44.v_x = 0.4;

    food55.position_x = -2200;            ///五号鱼
    food55.position_y = rand() % 400;
    food55.v_x = 0.6;

    food66.position_x = 3000;          ///六号鱼
    food66.position_y = rand() % 500;
    food66.v_x = 0.8;


    timer.position_x = rand() % 900;     ///闹钟纵坐标
    timer.position_y = -1000;    ///闹钟衡坐标随机设定
    timer.v_y = 0.7;            ///闹钟速度

    zhadan.position_x = rand() % 900; ///炸弹纵坐标
    zhadan.position_y = - 200;
    zhadan.v_y = 0.3;
}

void every_data3()
{
    game3 = newimage();
    for(int i = 0; i < fishnum; i++)
        fish3[i] = newimage();
    for(int i = 0; i <changenum; i++)
        player3[i] = newimage();

    getimage(game3, "yupic3\\bei2.png");
    getimage(fish3[0], "yupic3\\one1.png");
    getimage(fish3[1], "yupic3\\one2.png");
    getimage(fish3[2], "yupic3\\one3.png");
    getimage(fish3[3], "yupic3\\two.png");
    getimage(fish3[4], "yupic3\\three.png");
    getimage(fish3[5], "yupic3\\four.png");
    getimage(fish3[6], "yupic3\\five.png");
    getimage(fish3[7], "yupic3\\six.png");
    getimage(fish3[8], "yupic3\\seven.png");
    getimage(fish3[9], "yupic3\\eight.png");

    getimage(player3[0], "yupic3\\player11.png");   ///玩家右
    getimage(player3[1], "yupic3\\player22.png");
    getimage(player3[2], "yupic3\\player33.png");
    getimage(player3[3], "yupic3\\player44.png");
    getimage(player3[4], "yupic3\\player55.png");
    getimage(player3[5], "yupic3\\player66.png");

    getimage(player3[6], "yupic3\\player1.png");
    getimage(player3[7], "yupic3\\player2.png");
    getimage(player3[8], "yupic3\\player3.png");
    getimage(player3[9], "yupic3\\player4.png");
    getimage(player3[10], "yupic3\\player5.png");
    getimage(player3[11], "yupic3\\player6.png");

    starttime2 = clock();

    p3size = 60;                      ///鱼尺寸
    start_p3size = p3size;             ///鱼初始尺寸,赋值存放，防止下次变值

    players3.position_x = length/2.0;   ///玩家坐标
    players3.position_y = high/2.0;
    players3.v_x = 0.9;              ///玩家速度
    players3.v_y = 0.9;

    paopao.position_x = players3.position_x;    ///泡泡坐标为鱼的坐标
    paopao.position_y = players3.position_y;
    paopao.v_y = 0.2;                          ///泡泡上升速度

    fishone1.position_x = 1000;
    fishone1.position_y = rand() % 400;
    fishone1.v_x = 1.5;

    fishone2.position_x = 0;
    fishone2.position_y = rand() % 400;
    fishone2.v_x = 0.8;

    fishone3.position_x = 1000;
    fishone3.position_y = rand() % 500;
    fishone3.v_x = 0.7;

    fishtwo.position_x = 1200;        ///二号鱼坐标
    fishtwo.position_y = rand() % 400;
    fishtwo.v_x =0.8;

    fishthree.position_x = -300;            ///三号鱼坐标
    fishthree.position_y = rand() % 400;
    fishthree.v_x = 0.65;

    fishfour.position_x = -1800;             ///四号鱼
    fishfour.position_y = rand() % 400;
    fishfour.v_x = 0.4;

    fishfive.position_x = 2000;            ///五号鱼
    fishfive.position_y = rand() % 400;
    fishfive.v_x = 0.6;

    fishsix.position_x = -2800;          ///六号鱼
    fishsix.position_y = rand() % 500;
    fishsix.v_x = 0.8;

    fishseven.position_x = 4200;          ///七号鱼
    fishseven.position_y = rand() % 500;
    fishseven.v_x = 0.8;

    fisheight.position_x = -3300;
    fisheight.position_y = rand() % 500;
    fisheight.v_x = 0.6;


    timer.position_x = rand() % 900;     ///闹钟纵坐标
    timer.position_y = -1000;    ///闹钟衡坐标随机设定
    timer.v_y = 1.2;            ///闹钟速度

    zhadan.position_x = rand() % 900; ///炸弹纵坐标
    zhadan.position_y = - 200;
    zhadan.v_y = 0.5;
}

void formbackground()   ///进场页面
{
    mouse_msg lick = {0};
    while(1)
    {
        putimage(0, 0, enter);                   ///进场页面
        setbkmode(TRANSPARENT);
        setfont(30, 0, "宋体");
        setcolor(GREEN);
        xyprintf(70, 225, "上局分数");
        xyprintf(120, 270, "%d", allsocre[0]);
        Sleep(1);
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

void background_1()    ///菜单1
{
        putimage(0, 0, background2);                   ///操作说明页面

        setbkmode(TRANSPARENT);
        setcolor(RED);
        setfont(50, 0, "楷体");
        xyprintf(320, 40, "游 戏 操 作 说 明");
        setcolor(GREEN);
        setfont(30, 0, "楷体");
        xyprintf(370, 180, "↑ ↓ ← → 控制小鱼移动");
        xyprintf(290, 280, "按P键可使游戏暂停, 继续游戏按Esc键");
        setcolor(RED);
        setfont(30, 0, "楷体");
        xyprintf(220, 400, "返回菜单");
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
        xyprintf(350, 40, "游 戏 介 绍");
        setfont(30, 0, "宋体");
        xyprintf(200, 150, "该游戏为经典的大鱼吃小鱼游戏，总共分为三关！");
        xyprintf(160, 220, "吃掉比自己体型小的鱼得分，吃掉比自己体型大的鱼生命值 -1 ");
        xyprintf(80, 280, "玩家生命值每关为三条，吃掉炸弹 - 1 条生命值，不能增加生命值");
        xyprintf(0, 350, "游戏为限时游戏!!!吃掉第一关时钟加10s，第二关加15s，第三关加20s~~~");
        xyprintf(160, 420, "第一关限时为 90s 第二关限时为 80s 第三关限时为 80s！！");
        xyprintf(50, 470, "当分数达到620分通过第一关，当分数达到645分时通过第二关");
        xyprintf(270, 530, "第三关则要达到1000分哦！！！");
        setcolor(YELLOW);
        xyprintf(420, 590, "返回菜单");
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

void choosepass()   ///选择关卡
{
    putimage(0, 0, guanqiaback);
    putimage(300, 260, guanqia[0]);
    putimage(450, 260, guanqia[1]);
    putimage(600, 260, guanqia[2]);
    Sleep(1);
    mouse_msg in = {0};
    while(1)
    {
    while(mousemsg())
      {
          in = getmouse();
          if(in.x >= 300 && in.x <= 370 && in.y >= 260 && in.y <= 330)
        {
            if(in.is_down())
            passchange = 0;
            if(in.is_up())
            passchange = 1;
        }
      }
      if(passchange == 1)
        break;
    }

}

void initdata1()    ///游戏1
{
    mciSendString(TEXT("stop backmusic\\music2.mp3"), NULL, 0, NULL);              ///暂停菜单页面音乐1
    mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///关闭菜单页面音乐1
    mciSendString(TEXT("play backmusic\\huankuai.mp3 repeat"), NULL, 0, NULL);              ///播放进入游戏页面音乐4

    endtime = clock();
    resttime = timelong - (endtime - starttime)/1000.0;          ///计时

    if(backchange == 0)
    putimage(0, 0, game1);                          ///游戏背景

    setbkmode(TRANSPARENT);                         ///游戏分数
    setcolor(RED);                                   ///字体颜色
    setfont(25, 0, "楷体");                          ///字体大小与种类

    xyprintf(65, 10, "Score");
    xyprintf(80, 45, "%d", socre_p1);              ///分数

    xyprintf(415, 10, "resttime");                 ///剩余时间
    xyprintf(427, 45, "%.2f", resttime);

    xyprintf(750, 10, "The remaining life");
    for(int i = 0, j = 0; i < alive; i++, j+= 80)
    putimage_transparent(NULL, life, 770 + j, 45, 0);                  ///生命

    putimage(food1.position_x, food1.position_y, fish1[0], SRCAND);   ///将右转一号鱼显示出来
    putimage(food8.position_x, food8.position_y, fish1[7], SRCAND);   ///左转一号鱼打印
    putimage(food2.position_x, food2.position_y, fish1[1], SRCAND);     ///二号鱼
    putimage(food3.position_x, food3.position_y, fish1[2], SRCAND);     ///三号鱼
    putimage(food4.position_x, food4.position_y, fish1[3], SRCAND);     ///四号鱼
    putimage(food5.position_x, food5.position_y, fish1[4], SRCAND);     ///五号鱼
    putimage(food6.position_x, food6.position_y, fish1[5], SRCAND);             ///六号鱼
    putimage(food7.position_x, food7.position_y, fish1[6], SRCAND);             ///七号鱼
    putimage_transparent(NULL, boom[0], zhadan.position_x, zhadan.position_y, 0);      ///炸弹
    putimage_transparent(NULL, alarm[0], timer.position_x, timer.position_y, 0);       ///闹钟

    putimage_transparent(NULL, pao, paopao.position_x, paopao.position_y , 0);         ///吐的泡泡
    putimage_transparent(NULL, pao, paopao.position_x, paopao.position_y - 30, 0);

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
}

void initdata2()
{
    endtime1 = clock();
    resttime1 = timelong2 - (endtime1 - starttime1)/1000.0;        ///第二关计时

    putimage_transparent(NULL, game2, 0, 0, 0);                          ///游戏背景

    setbkmode(TRANSPARENT);                         ///游戏分数
    setcolor(RED);                                   ///字体颜色
    setfont(25, 0, "楷体");                          ///字体大小与种类

    xyprintf(65, 10, "Score");
    xyprintf(80, 45, "%d", socre_p2);              ///分数

    xyprintf(415, 10, "resttime");                 ///剩余时间
    xyprintf(426, 45, "%.2f", resttime1);

    xyprintf(750, 10, "The remaining life");
    for(int i = 0, j = 0; i < alive1; i++, j+= 80)
    putimage_transparent(NULL, life, 770 + j, 45, 0);                  ///生命

    putimage_transparent(NULL, fish2[0], food11.position_x, food11.position_y, 0);   ///将左转一号鱼显示出来
    putimage_transparent(NULL, fish2[1], food111.position_x, food111.position_y, 0);   ///右转一号鱼打印
    putimage_transparent(NULL, fish2[2], food1111.position_x, food1111.position_y, 0);     ///左转一号鱼
    putimage_transparent(NULL, fish2[3], food22.position_x, food22.position_y, 0);     ///二号鱼
    putimage_transparent(NULL, fish2[4], food33.position_x, food33.position_y, 0);     ///三号鱼
    putimage_transparent(NULL, fish2[5], food44.position_x, food44.position_y, 0);             ///四号鱼
    putimage_transparent(NULL, fish2[6], food55.position_x, food55.position_y, 0);             ///五号鱼
    putimage_transparent(NULL, fish2[7], food66.position_x, food66.position_y, 0);

    putimage_transparent(NULL, boom[0], zhadan.position_x, zhadan.position_y, 0);      ///炸弹
    putimage_transparent(NULL, alarm[0], timer.position_x, timer.position_y, 0);       ///闹钟
    putimage_transparent(NULL, pao, paopao.position_x, paopao.position_y, 0);         ///吐的泡泡
    putimage_transparent(NULL, pao, paopao.position_x, paopao.position_y - 30, 0);


    if(yuturn1 == 0)                       ///进行鱼变大变化
    {
        if(p2size < 65)
            putimage_transparent(NULL, player2[0], players2.position_x, players2.position_y, 0);
        else if(p2size >= 65 && p2size <75)
            putimage_transparent(NULL, player2[1], players2.position_x, players2.position_y, 0);
        else if(p2size >= 75 && p2size < 90)
            putimage_transparent(NULL, player2[2], players2.position_x, players2.position_y, 0);
        else if(p2size >= 90 && p2size < 105)
            putimage_transparent(NULL, player2[3], players2.position_x, players2.position_y, 0);
        else if(p2size >= 105 && p2size < 135)
            putimage_transparent(NULL, player2[4], players2.position_x, players2.position_y, 0);
        else if(p2size >= 135)
            putimage_transparent(NULL, player2[5], players2.position_x, players2.position_y, 0);
    }
    else
    {
        if(p2size < 65)
            putimage_transparent(NULL, player2[6], players2.position_x, players2.position_y, 0);
        else if(p2size >= 65 && p2size <75)
            putimage_transparent(NULL, player2[7], players2.position_x, players2.position_y, 0);
        else if(p2size >= 75 && p2size < 90)
            putimage_transparent(NULL, player2[8], players2.position_x, players2.position_y, 0);
        else if(p2size >= 90 && p2size < 105)
            putimage_transparent(NULL, player2[9], players2.position_x, players2.position_y, 0);
        else if(p2size >= 105 && p2size < 135)
            putimage_transparent(NULL, player2[10], players2.position_x, players2.position_y, 0);
        else if(p2size >= 135)
            putimage_transparent(NULL, player2[11], players2.position_x, players2.position_y, 0);
    }
}

void initdata3()
{
    endtime2 = clock();
    resttime2 = timelong3 - (endtime2 - starttime2)/1000.0;        ///第二关计时

    putimage_transparent(NULL, game3, 0, 0, 0);                          ///游戏背景

    setbkmode(TRANSPARENT);                         ///游戏分数
    setcolor(RED);                                   ///字体颜色
    setfont(25, 0, "楷体");                          ///字体大小与种类

    xyprintf(65, 10, "Score");
    xyprintf(80, 45, "%d", socre_p3);              ///分数

    xyprintf(415, 10, "resttime");                 ///剩余时间
    xyprintf(426, 45, "%.2f", resttime2);

    xyprintf(750, 10, "The remaining life");
    for(int i = 0, j = 0; i < alive2; i++, j+= 80)
    putimage_transparent(NULL, life, 770 + j, 45, 0);                  ///生命

    putimage_transparent(NULL, fish3[0], fishone1.position_x, fishone1.position_y, 0);
    putimage_transparent(NULL, fish3[1], fishone2.position_x, fishone2.position_y, 0);
    putimage_transparent(NULL, fish3[2], fishone3.position_x, fishone3.position_y, 0);
    putimage_transparent(NULL, fish3[3], fishtwo.position_x, fishtwo.position_y, 0);
    putimage_transparent(NULL, fish3[4], fishthree.position_x, fishthree.position_y, 0);
    putimage_transparent(NULL, fish3[5], fishfour.position_x, fishfour.position_y, 0);
    putimage_transparent(NULL, fish3[6], fishfive.position_x, fishfive.position_y, 0);
    putimage_transparent(NULL, fish3[7], fishsix.position_x, fishsix.position_y, 0);
    putimage_transparent(NULL, fish3[8], fishseven.position_x, fishseven.position_y, 0);
    putimage_transparent(NULL, fish3[9], fisheight.position_x, fisheight.position_y, 0);

    putimage_transparent(NULL, boom[0], zhadan.position_x, zhadan.position_y, 0);      ///炸弹
    putimage_transparent(NULL, alarm[0], timer.position_x, timer.position_y, 0);       ///闹钟
    putimage_transparent(NULL, pao, paopao.position_x, paopao.position_y, 0);         ///吐的泡泡
    putimage_transparent(NULL, pao, paopao.position_x, paopao.position_y - 30, 0);


    if(yuturn2 == 0)                       ///进行鱼变大变化
    {
        if(p3size < 65)
            putimage_transparent(NULL, player3[0], players3.position_x, players3.position_y, 0);
        else if(p3size >= 65 && p3size < 85)
            putimage_transparent(NULL, player3[1], players3.position_x, players3.position_y, 0);
        else if(p3size >= 85 && p3size < 110)
            putimage_transparent(NULL, player3[2], players3.position_x, players3.position_y, 0);
        else if(p3size >= 110 && p3size < 130)
            putimage_transparent(NULL, player3[3], players3.position_x, players3.position_y, 0);
        else if(p3size >= 130 && p3size < 200)
            putimage_transparent(NULL, player3[4], players3.position_x, players3.position_y, 0);
        else if(p3size >= 135)
            putimage_transparent(NULL, player3[5], players3.position_x, players3.position_y, 0);
    }
    else
    {
        if(p3size < 65)
            putimage_transparent(NULL, player3[6], players3.position_x, players3.position_y, 0);
        else if(p3size >= 65 && p3size < 85)
            putimage_transparent(NULL, player3[7], players3.position_x, players3.position_y, 0);
        else if(p3size >= 85 && p3size < 110)
            putimage_transparent(NULL, player3[8], players3.position_x, players3.position_y, 0);
        else if(p3size >= 110 && p3size < 130)
            putimage_transparent(NULL, player3[9], players3.position_x, players3.position_y, 0);
        else if(p3size >= 130 && p3size < 200)
            putimage_transparent(NULL, player3[10], players3.position_x, players3.position_y, 0);
        else if(p3size >= 200)
            putimage_transparent(NULL, player3[11], players3.position_x, players3.position_y, 0);
    }
}

void restart_menu1()  ///继续游戏1
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

void restart_menu2()
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

void restart_menu3()
{
    char input_4;
    if(kbhit())
    {
        input_4 = getch();
        if(input_4 == 27)
        {
            gamestatus2 = 0;
        }
    }
}

void data_withoutinput1()  ///没有数据输入时1
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
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        timelong += 10;                               ///吃掉闹钟时间加十秒
        socre_p1 += 5;                                           ///吃掉闹钟分数加5
        timer.position_x = -1500;
        timer.position_y = rand() % (high - 45);                    ///玩家吃掉闹钟
    }

    if((zhadan.position_x + 45/2.0/*炸弹尺寸*/ >= players.position_x) && (zhadan.position_x + 45/2.0 <= players.position_x +p1size)
            && (zhadan.position_y + 25 >= players.position_y) && (zhadan.position_y + 25 <= players.position_y + p1size))
    {
        mciSendString(TEXT("stop backmusic\\baozha.mp3"), NULL, 0, NULL);
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);               ///关闭被吃音效
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;            ///玩家被三号吃掉重置
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
            players.position_y = high - 100;              ///玩家被七号海马鱼吃掉重置
        }
    }


    if(p1size > 90)                              ///大小达到能吃四号鱼
    {
        if((food4.position_x + 105/2.0/*四号鱼尺寸*/ >= players.position_x) && (food4.position_x + 105/2.0 <= players.position_x + p1size)
                && (food4.position_y + 70/2.0 >= players.position_y) && (food4.position_y + 70/2.0 <= players.position_y + p1size))
        {
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;          ///不够吃玩家被吃重置
        }
    }


    if(p1size > 135)                             ///玩家大小达到够吃五号鱼
    {
        if((food5.position_x + 300/2.0/*五号鱼一半尺寸*/ >= players.position_x) && (food5.position_x + 300/2.0 <= players.position_x + p1size)
                && (food5.position_y + 160/2.0 >= players.position_y) && (food5.position_y + 160/2.0 <= players.position_y + p1size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p1size += 10;
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
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p1size = start_p1size;
            alive--;
            players.position_x = length / 2.0;
            players.position_y = high - 100;                  ///玩家被五号鱼吃被重置
        }
    }
}

void data_withinput1()   ///有数据输入时1
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

void data_withoutinput2()
{
    paopao.position_y = paopao.position_y - paopao.v_y;         ///泡泡上升
    if(paopao.position_y < 0)
    {
        paopao.position_x = players2.position_x;                 ///泡泡重复出现
        paopao.position_y = players2.position_y;
    }

    food11.position_x = food11.position_x - food11.v_x;             ///1号鱼向左移动
    if(food11.position_x < 0)
    {
        food11.position_x = 1300;
        food11.position_y = rand() % 500;                        ///向左1号鱼重复出现
    }

    food111.position_x = food111.position_x + food111.v_x;              ///一号鱼向右移动
    if(food111.position_x > length)
    {
        food111.position_x = 0;
        food111.position_y = rand() % 400;                         ///向右移动一号鱼重复出现
    }

    food1111.position_x = food1111.position_x - food1111.v_x;        ///一号鱼向左移动
    if(food1111.position_x < 0)
    {
        food1111.position_x = 1200;
        food1111.position_y = rand() % 500;                  ///左转一号鱼重复出现
    }

    food22.position_x = food22.position_x - food22.v_x;       ///二号鱼向左移动
    if(food2.position_x < 0)
    {
        food22.position_x = 1900;
        food22.position_y = rand() % 400;                   ///二号鱼重复出现
    }

    food33.position_x = food33.position_x - food33.v_x;       ///三号鱼向左移动
    if(food33.position_x < 0)
    {
        food33.position_x = 2500;
        food33.position_y = rand() % 400;                    ///三号鱼重出现
    }

    food44.position_x = food44.position_x + food44.v_x;          ///四号鱼向右移动
    if(food44.position_x > length)
    {
        food44.position_x = -1800;
        food44.position_y = rand() % 500;                                ///四号鱼重复出现
    }

    food55.position_x = food55.position_x + food55.v_x;         ///五号鱼向右移动
    if(food55.position_x > length)
    {
        food55.position_x = -2200;
        food55.position_y = rand() % 400;                     ///五号鱼重复出现
    }

    food66.position_x = food66.position_x - food66.v_x;             ///六号鱼向左移动
    if(food66.position_x < 0)
    {
        food66.position_x = 3100;
        food66.position_y = rand() % 400;                        ///六号鱼重复出现

    }

    timer.position_y = timer.position_y + timer.v_y;         ///闹钟向下移动
    if(timer.position_y > high)
    {
        timer.position_x =  rand() % 900;           ///闹钟出现一次后让它重复出现
        timer.position_y = -2000;       ///变换坐标，使到下次出现时间的间隔长点
    }

    zhadan.position_y = zhadan.position_y + zhadan.v_y;     ///炸弹向下移动
    if(zhadan.position_y > high)                               ///出界后重新出现
    {
        zhadan.position_x = rand() % 800;
        zhadan.position_y = -200;
    }

    ///判断吃的情况，当中心点位于玩家鱼的范围内时被吃掉
    if((timer.position_x + 45/2.0/*闹钟尺寸*/ >= players2.position_x) && (timer.position_x + 45/2.0<= players2.position_x + p2size)
            && (timer.position_y + 25 >= players2.position_y + 20) && (timer.position_y + 25 <= players2.position_y + p2size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        timelong2 += 15;                                ///吃掉闹钟时间加十五秒
        socre_p2 += 5;                                           ///吃掉闹钟分数加5
        timer.position_x = rand() % 900;
        timer.position_y = -2000;                    ///玩家吃掉闹钟
    }

    if((zhadan.position_x + 45/2.0/*炸弹尺寸*/ >= players2.position_x) && (zhadan.position_x + 45/2.0 <= players2.position_x +p2size)
            && (zhadan.position_y + 25 >= players2.position_y) && (zhadan.position_y + 25 <= players2.position_y + p2size))
    {
        mciSendString(TEXT("stop backmusic\\baozha.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("close backmusic\\baozha.mp3"), NULL, 0, NULL);         ///每次在打开前关闭炸弹音效
        mciSendString(TEXT("play backmusic\\baozha.mp3"), NULL, 0, NULL);

        alive1--;
        p2size = start_p2size;
        players2.position_x = length / 2.0;
        players2.position_y = high - 100;                        ///吃掉炸弹玩家重置
        zhadan.position_x = rand() % 1000;                          ///玩家吃掉炸弹
        zhadan.position_y = -1000;
    }

    if((food11.position_x + 50/2.0/*右转小鱼尺寸*/ >= players2.position_x && food11.position_x + 50/2.0 <= players2.position_x + p2size)
            && (food11.position_y + 25/2.0 >= players2.position_y) && (food11.position_y + 25/2.0 <= players2.position_y + p2size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p2size += 2;
        socre_p2 += 10;                                                      ///吃掉小鱼分数加10
        food11.position_x = 1300;
        food11.position_y = rand() % (high - 25);                          ///左转小鱼被吃，立马重新生成
    }

    if((food111.position_x + 50/2.0/*左转小鱼尺寸*/>= players2.position_x && food111.position_x + 50/2.0 <= players2.position_x + p2size)
            && (food111.position_y + 25/2.0 >= players2.position_y) && (food111.position_y + 25/2.0 <= players2.position_y + p2size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);                 ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p2size += 2;
        socre_p2 +=10;                                                                ///吃掉右转小鱼分数加10
        food111.position_x = -200;
        food111.position_y = rand() % (high - 25);
    }

    if((food1111.position_x + 50/2.0 >= players2.position_x) && (food1111.position_x + 50/2.0 <= players2.position_x + p2size)
                && (food1111.position_y + 25/2.0 >= players2.position_y) && (food1111.position_y + 25/2.0 <= players2.position_y + p2size))
    {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);              ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p2size += 2;
            socre_p2 += 10;
            food1111.position_x = 1300;
            food1111.position_y = rand() % (high - 70);
    }

    if(p2size > 65)                            ///大小达到能吃掉二号鱼
    {
        if((food22.position_x + 65/2.0/*二号鱼尺寸*/ >= players2.position_x && food22.position_x + 65/2.0 <= players2.position_x + p2size)
                && (food22.position_y + 40/2.0 >= players2.position_y && food22.position_y + 40/2.0<= players2.position_y + p2size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p2size += 3;
            socre_p2 += 20;                                               ///吃掉二号鱼分数加20
            food22.position_x = 1200;
            food22.position_y = rand() % (high - 40);
        }
    }
    else                                        ///没达到，遇到二号鱼则被吃
    {
        if((players2.position_x + p2size/2.0/*玩家自身尺寸一半*/ >= food22.position_x && players2.position_x + p2size/2.0 <= food22.position_x + 65)
                && (players2.position_y + p2size/2.0 >= food22.position_y && players2.position_y + p2size/2.0 <= food22.position_y + 40))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);             ///每次打开被吃音效前关掉
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p2size = start_p2size;
            alive1--;
            players2.position_x = length / 2.0;     ///玩家重置
            players2.position_y = high - 100;
        }
    }


    if(p2size > 75)                              ///大小达到能吃三号
    {
        if((food33.position_x + 80/2.0/*三号鱼尺寸一半*/ >= players2.position_x ) && (food33.position_x + 80/2.0 <= players2.position_x + p2size)
                && (food33.position_y + 70/2.0 >= players2.position_y )  && (food33.position_y + 70/2.0 <= players2.position_y + p2size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                 ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);               ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p2size += 4;
            socre_p2 += 30;                                   ///吃掉三号鱼分数加30
            food33.position_x = 1500;                        ///三号鱼重置
            food33.position_y = rand() % (high - 70);
        }

    }
    else                                         ///没达到，遇到三号被吃
    {
        if((players2.position_x + p2size/2.0 >= food33.position_x) && (players2.position_x + p2size/2.0 <= food33.position_x + 80)
                && (players2.position_y + p2size/2.0 >= food33.position_y) && (players2.position_y + p2size/2.0 <= food33.position_y + 70))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p2size = start_p2size;
            alive1--;
            players2.position_x = length / 2.0;            ///玩家被三号吃掉重置
            players2.position_y = high - 100;
        }
    }

    if(p2size > 90)                              ///大小达到能吃四号鱼
    {
        if((food44.position_x + 105/2.0/*四号鱼尺寸*/ >= players2.position_x) && (food44.position_x + 105/2.0 <= players2.position_x + p2size)
                && (food44.position_y + 70/2.0 >= players2.position_y) && (food44.position_y + 70/2.0 <= players2.position_y + p2size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p2size += 4;
            socre_p2 += 40;                                      ///吃掉四号鱼分数加40
            food44.position_x = -700;                          ///四号鱼重置
            food44.position_y = rand() & (high - 70);
        }
    }
    else                                         ///没达到，遇到四号鱼则被吃
    {
        if((players2.position_x + p2size/2.0 >= food44.position_x) && (players2.position_x + p2size/2.0 <= food44.position_x + 105)
                && (players2.position_y + p2size/2.0 >= food44.position_y) && (players2.position_y + p2size/2.0 <= food44.position_y + 70))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p2size = start_p2size;
            alive1--;
            players2.position_x = length / 2.0;            ///玩家被吃重置
            players2.position_y = high - 100;
        }
    }

    if(p2size > 110)                             ///玩家大小达到够吃五号鱼
    {
        if((food55.position_x + 200/2.0/*五号鱼一半尺寸*/ >= players2.position_x) && (food55.position_x + 200/2.0 <= players2.position_x + p2size)
                && (food55.position_y + 160/2.0 >= players2.position_y) && (food55.position_y + 160/2.0 <= players2.position_y + p2size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p2size += 8;
            socre_p2 += 45;                                             ///吃掉五号鱼分数加60
            food55.position_x = -2000;                                 ///五号鱼重置
            food55.position_y = rand() % (high - 100);
        }
    }
    else                                         ///没达到，遇到五号鱼则被吃
    {
        if((players2.position_x + p2size/2.0 >= food55.position_x) && (players2.position_x + p2size/2.0 <= food55.position_x + 200)
                && (players2.position_y + p2size/2.0 >= food55.position_y) && (players2.position_y + p2size/2.0 <= food55.position_y + 160))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p2size = start_p2size;
            alive1--;
            players2.position_x = length / 2.0;
            players2.position_y = high - 100;                  ///玩家被五号鱼吃被重置
        }
    }

    if(p2size > 140)                              ///大小达到能吃六号鱼
    {
        if((food66.position_x + 275/2.0/*六号鱼尺寸一半*/ >= players2.position_x)&& (food66.position_x + 275/2.0 <= players2.position_x + p2size)
                && (food66.position_y + 150/2.0 >= players2.position_y) && (food66.position_y + 150/2.0 <= players2.position_y + p2size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p2size += 15;
            socre_p2 += 60;                                  ///吃掉六号鱼分数加50
            food66.position_x = 3400;
            food66.position_y = rand() % 400;             ///六号鱼重置
        }
    }
    else                                            ///没达到，遇到六号鱼则被吃
    {
        if((players2.position_x + p2size/2.0 >= food66.position_x) && (players2.position_x + p2size/2.0 <= food66.position_x + 275)
                && (players2.position_y + p2size/2.0 >= food66.position_y) && (players2.position_y + p2size/2.0 <= food66.position_y + 150))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p2size = start_p2size;
            alive1--;
            players2.position_x = length / 2.0;
            players2.position_y = high - 100;          ///不够吃玩家被吃重置
        }
    }
}

void data_withinput2()
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (players2.position_x > 0))
    {
        yuturn1 = 1;                                   ///左转
        players2.position_x = players2.position_x - players2.v_x;
    }

    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (players2.position_x < length - 45))    ///防止右转出界
    {
        yuturn1 = 0;                                          ///右转
        players2.position_x = players2.position_x + players2.v_x;
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  players2.position_y > 0)
        players2.position_y = players2.position_y - players2.v_y;             ///上移
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  players2.position_y < high - 45)         ///防止左转出界
        players2.position_y = players2.position_y + players2.v_y;            ///下移

    char input_4;
    if(kbhit())                                            ///游戏暂停操作
    {
        input_4 = getch();
        if(input_4 == 'p' || input_4 == 'P')
        {
            gamestatus1 = 2;
        }

    }
}

void data_withoutinput3()
{
    paopao.position_y = paopao.position_y - paopao.v_y;         ///泡泡上升
    if(paopao.position_y < 0)
    {
        paopao.position_x = players3.position_x;                 ///泡泡重复出现
        paopao.position_y = players3.position_y;
    }

    fishone1.position_x = fishone1.position_x - fishone1.v_x;             ///1号鱼向左移动
    if(fishone1.position_x < 0)
    {
        fishone1.position_x = 1200;
        fishone1.position_y = rand() % 500;                        ///向左1号鱼重复出现
    }

    fishone2.position_x = fishone2.position_x + fishone2.v_x;              ///一号鱼向右移动
    if(fishone2.position_x > length)
    {
        fishone2.position_x = 0;
        fishone2.position_y = rand() % 400;                         ///向右移动一号鱼重复出现
    }

    fishone3.position_x = fishone3.position_x - fishone3.v_x;        ///一号鱼向左移动
    if(fishone3.position_x < 0)
    {
        fishone3.position_x = 1200;
        fishone3.position_y = rand() % 500;                  ///左转一号鱼重复出现
    }

    fishtwo.position_x = fishtwo.position_x - fishtwo.v_x;       ///二号鱼向左移动
    if(fishtwo.position_x < 0)
    {
        fishtwo.position_x = 1600;
        fishtwo.position_y = rand() % 400;                   ///二号鱼重复出现
    }

    fishthree.position_x = fishthree.position_x + fishthree.v_x;
    if(fishthree.position_x > length)
    {
        fishthree.position_x = -1500;
        fishthree.position_y = rand() % 400;
    }

    fishfour.position_x = fishfour.position_x + fishfour.v_x;          ///四号鱼向右移动
    if(fishfour.position_x > length)
    {
        fishfour.position_x = -1800;
        fishfour.position_y = rand() % 500;                                ///四号鱼重复出现
    }

    fishfive.position_x = fishfive.position_x - fishfive.v_x;
    if(fishfive.position_x < 0)
    {
        fishfive.position_x = 3000;
        fishfive.position_y = rand() % 400;
    }

    fishsix.position_x = fishsix.position_x + fishsix.v_x;
    if(fishsix.position_x > length)
    {
        fishsix.position_x = -2100;
        fishsix.position_y = rand() % 400;                        ///六号鱼重复出现
    }

    fishseven.position_x = fishseven.position_x - fishseven.v_x;
    if(fishseven.position_x < 0)
    {
        fishseven.position_x = 3500;
        fishseven.position_y = rand() % 500;
    }
    fisheight.position_x = fisheight.position_x - fisheight.v_x;
    if(fisheight.position_x > length)
    {
        fisheight.position_x = 5000;
        fisheight.position_y = rand() % 600;
    }

    timer.position_y = timer.position_y + timer.v_y;         ///闹钟向下移动
    if(timer.position_y > high)
    {
        timer.position_x =  rand() % 900;           ///闹钟出现一次后让它重复出现
        timer.position_y = -4000;       ///变换坐标，使到下次出现时间的间隔长点
    }

    zhadan.position_y = zhadan.position_y + zhadan.v_y;     ///炸弹向下移动
    if(zhadan.position_y > high)                               ///出界后重新出现
    {
        zhadan.position_x = rand() % 800;
        zhadan.position_y = -200;
    }

    ///判断吃的情况，当中心点位于玩家鱼的范围内时被吃掉
    if((timer.position_x + 45/2.0/*闹钟尺寸*/ >= players3.position_x) && (timer.position_x + 45/2.0<= players3.position_x + p3size)
            && (timer.position_y + 25 >= players3.position_y + 20) && (timer.position_y + 25 <= players3.position_y + p3size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        timelong3 += 15;                                ///吃掉闹钟时间加十五秒
        socre_p3 += 5;                                           ///吃掉闹钟分数加5
        timer.position_x = rand() % 900;
        timer.position_y = -2500;                    ///玩家吃掉闹钟
    }

    if((zhadan.position_x + 45/2.0/*炸弹尺寸*/ >= players3.position_x) && (zhadan.position_x + 45/2.0 <= players3.position_x +p3size)
            && (zhadan.position_y + 25 >= players3.position_y) && (zhadan.position_y + 25 <= players3.position_y + p3size))
    {
        mciSendString(TEXT("stop backmusic\\baozha.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("close backmusic\\baozha.mp3"), NULL, 0, NULL);         ///每次在打开前关闭炸弹音效
        mciSendString(TEXT("play backmusic\\baozha.mp3"), NULL, 0, NULL);

        alive2--;
        p3size = start_p3size;
        players3.position_x = length / 2.0;
        players3.position_y = high - 100;                        ///吃掉炸弹玩家重置
        zhadan.position_x = rand() % 1000;                          ///玩家吃掉炸弹
        zhadan.position_y = -1000;
    }

    if((fishone1.position_x + 50/2.0/*左转小鱼尺寸*/ >= players3.position_x && fishone1.position_x + 50/2.0 <= players3.position_x + p3size)
            && (fishone1.position_y + 25/2.0 >= players3.position_y) && (fishone1.position_y + 25/2.0 <= players3.position_y + p3size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p3size += 2;
        socre_p3 += 15;                                                      ///吃掉小鱼分数加10
        fishone1.position_x = 1300;
        fishone1.position_y = rand() % (high - 25);                          ///左转小鱼被吃，立马重新生成
    }

    if((fishone2.position_x + 50/2.0/*右转小鱼尺寸*/>= players3.position_x && fishone2.position_x + 50/2.0 <= players3.position_x + p3size)
            && (fishone2.position_y + 25/2.0 >= players3.position_y) && (fishone2.position_y + 25/2.0 <= players3.position_y + p3size))
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                ///暂停吃的音效
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);                 ///关闭吃的音效
        mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

        p3size += 2;
        socre_p3 +=15;                                                                ///吃掉右转小鱼分数加10
        fishone2.position_x = -200;
        fishone2.position_y = rand() % (high - 25);
    }

    if((fishone3.position_x + 50/2.0 >= players3.position_x) && (fishone3.position_x + 50/2.0 <= players3.position_x + p3size)
                && (fishone3.position_y + 25/2.0 >= players3.position_y) && (fishone3.position_y + 25/2.0 <= players3.position_y + p3size))
    {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);              ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p3size += 2;
            socre_p3 += 15;
            fishone3.position_x = 1300;
            fishone3.position_y = rand() % (high - 70);
    }

    if(p3size > 65)                            ///大小达到能吃掉二号鱼
    {
        if((fishtwo.position_x + 65/2.0/*二号鱼尺寸*/ >= players3.position_x && fishtwo.position_x + 65/2.0 <= players3.position_x + p3size)
                && (fishtwo.position_y + 40/2.0 >= players3.position_y && fishtwo.position_y + 40/2.0<= players3.position_y + p3size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);             ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);             ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p3size += 3;
            socre_p3 += 25;                                               ///吃掉二号鱼分数加20
            fishtwo.position_x = 1400;
            fishtwo.position_y = rand() % (high - 40);
        }
    }
    else                                        ///没达到，遇到二号鱼则被吃
    {
        if((players3.position_x + p3size/2.0/*玩家自身尺寸一半*/ >= fishtwo.position_x && players3.position_x + p3size/2.0 <= fishtwo.position_x + 65)
                && (players3.position_y + p3size/2.0 >= fishtwo.position_y && players3.position_y + p3size/2.0 <= fishtwo.position_y + 40))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);             ///每次打开被吃音效前关掉
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p3size = start_p3size;
            alive2--;
            players3.position_x = length / 2.0;     ///玩家重置
            players3.position_y = high - 100;
        }
    }


    if(p3size > 85)                              ///大小达到能吃三号
    {
        if((fishthree.position_x + 80/2.0/*三号鱼尺寸一半*/ >= players3.position_x ) && (fishthree.position_x + 80/2.0 <= players3.position_x + p3size)
                && (fishthree.position_y + 70/2.0 >= players3.position_y )  && (fishthree.position_y + 70/2.0 <= players3.position_y + p3size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);                 ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);               ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p3size += 4;
            socre_p3 += 40;                                   ///吃掉三号鱼分数加30
            fishthree.position_x = -800;                        ///三号鱼重置
            fishthree.position_y = rand() % (high - 70);
        }

    }
    else                                         ///没达到，遇到三号被吃
    {
        if((players3.position_x + p3size/2.0 >= fishthree.position_x) && (players3.position_x + p3size/2.0 <= fishthree.position_x + 80)
                && (players3.position_y + p3size/2.0 >= fishthree.position_y) && (players3.position_y + p3size/2.0 <= fishthree.position_y + 70))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p3size = start_p3size;
            alive2--;
            players3.position_x = length / 2.0;            ///玩家被三号吃掉重置
            players3.position_y = high - 100;
        }
    }

    if(p3size > 110)                              ///大小达到能吃四号鱼
    {
        if((fishfour.position_x + 105/2.0/*四号鱼尺寸*/ >= players3.position_x) && (fishfour.position_x + 105/2.0 <= players3.position_x + p3size)
                && (fishfour.position_y + 70/2.0 >= players3.position_y) && (fishfour.position_y + 70/2.0 <= players3.position_y + p3size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p3size += 4;
            socre_p3 += 50;                                      ///吃掉四号鱼分数加40
            fishfour.position_x = -900;                          ///四号鱼重置
            fishfour.position_y = rand() & (high - 70);
        }
    }
    else                                         ///没达到，遇到四号鱼则被吃
    {
        if((players3.position_x + p3size/2.0 >= fishfour.position_x) && (players3.position_x + p3size/2.0 <= fishfour.position_x + 105)
                && (players3.position_y + p3size/2.0 >= fishfour.position_y) && (players3.position_y + p3size/2.0 <= fishfour.position_y + 70))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p3size = start_p3size;
            alive2--;
            players3.position_x = length / 2.0;            ///玩家被吃重置
            players3.position_y = high - 100;
        }
    }

    if(p3size > 130)                             ///玩家大小达到够吃五号鱼
    {
        if((fishfive.position_x + 200/2.0/*五号鱼一半尺寸*/ >= players3.position_x) && (fishfive.position_x + 200/2.0 <= players3.position_x + p3size)
                && (fishfive.position_y + 150/2.0 >= players3.position_y) && (fishfive.position_y + 150/2.0 <= players3.position_y + p3size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p3size += 8;
            socre_p3 += 65;                                             ///吃掉五号鱼分数加60
            fishfive.position_x = 3000;                                 ///五号鱼重置
            fishfive.position_y = rand() % (high - 100);
        }
    }
    else                                         ///没达到，遇到五号鱼则被吃
    {
        if((players3.position_x + p3size/2.0 >= fishfive.position_x) && (players3.position_x + p3size/2.0 <= fishfive.position_x + 200)
                && (players3.position_y + p3size/2.0 >= fishfive.position_y) && (players3.position_y + p3size/2.0 <= fishfive.position_y + 150))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p3size = start_p3size;
            alive2--;
            players3.position_x = length / 2.0;
            players3.position_y = high - 100;                  ///玩家被五号鱼吃被重置
        }
    }

    if(p3size > 170)                              ///大小达到能吃六号鱼
    {
        if((fishsix.position_x + 275/2.0/*六号鱼尺寸一半*/ >= players3.position_x) && (fishsix.position_x + 275/2.0 <= players3.position_x + p3size)
                && (fishsix.position_y + 150/2.0 >= players3.position_y) && (fishsix.position_y + 150/2.0 <= players3.position_y + p3size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p3size += 10;
            socre_p3 += 80;                                  ///吃掉六号鱼分数加50
            fishsix.position_x = -2500;
            fishsix.position_y = rand() % 400;             ///六号鱼重置
        }
    }
    else                                            ///没达到，遇到六号鱼则被吃
    {
        if((players3.position_x + p3size/2.0 >= fishsix.position_x) && (players3.position_x + p3size/2.0 <= fishsix.position_x + 275)
                && (players3.position_y + p3size/2.0 >= fishsix.position_y) && (players3.position_y + p3size/2.0 <= fishsix.position_y + 150))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p3size = start_p3size;
            alive2--;
            players3.position_x = length / 2.0;
            players3.position_y = high - 100;          ///不够吃玩家被吃重置
        }
    }
    if(p3size > 200)                              ///大小达到能吃七号鱼
    {
        if((fishseven.position_x + 300/2.0/*六号鱼尺寸一半*/ >= players3.position_x) && (fishseven.position_x + 300/2.0 <= players3.position_x + p3size)
                && (fishseven.position_y + 150/2.0 >= players3.position_y) && (fishseven.position_y + 150/2.0 <= players3.position_y + p3size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p3size += 15;
            socre_p3 += 100;
            fishseven.position_x = 3800;
            fishseven.position_y = rand() % 400;
        }
    }
    else
    {
        if((players3.position_x + p3size/2.0 >= fishseven.position_x) && (players3.position_x + p3size/2.0 <= fishseven.position_x + 300)
                && (players3.position_y + p3size/2.0 >= fishseven.position_y) && (players3.position_y + p3size/2.0 <= fishseven.position_y + 150))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p3size = start_p3size;
            alive2--;
            players3.position_x = length / 2.0;
            players3.position_y = high - 100;
        }
    }
    if(p3size > 230)                              ///大小达到能吃七号鱼
    {
        if((fisheight.position_x + 400/2.0 >= players3.position_x) && (fisheight.position_x + 400/2.0 <= players3.position_x + p3size)
                && (fisheight.position_y + 220/2.0 >= players3.position_y) && (fisheight.position_y + 220/2.0 <= players3.position_y + p3size))
        {
            mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);            ///暂停吃的音效
            mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);           ///关闭吃的音效
            mciSendString(TEXT("play backmusic\\bit.mp3"), NULL, 0, NULL);

            p3size += 20;
            socre_p3 += 120;
            fisheight.position_x = -3000;
            fisheight.position_y = rand() % 400;
        }
    }
    else
    {
        if((players3.position_x + p3size/2.0 >= fisheight.position_x) && (players3.position_x + p3size/2.0 <= fisheight.position_x + 400)
                && (players3.position_y + p3size/2.0 >= fisheight.position_y) && (players3.position_y + p3size/2.0 <= fisheight.position_y + 220))
        {
            mciSendString(TEXT("stop backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\2.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("play backmusic\\2.mp3"), NULL, 0, NULL);

            p3size = start_p3size;
            alive2--;
            players3.position_x = length / 2.0;
            players3.position_y = high - 100;
        }
    }
}

void data_withinput3()
{
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000)  &&  (players3.position_x > 0))
    {
        yuturn2 = 1;                                   ///左转
        players3.position_x = players3.position_x - players3.v_x;
    }

    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000)  &&  (players3.position_x < length - 45))    ///防止右转出界
    {
        yuturn2 = 0;                                          ///右转
        players3.position_x = players3.position_x + players3.v_x;
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000)  &&  players3.position_y > 0)
        players3.position_y = players3.position_y - players3.v_y;             ///上移

    if ((GetAsyncKeyState(VK_DOWN) & 0x8000)  &&  players3.position_y < high - 45)         ///防止左转出界
        players3.position_y = players3.position_y + players3.v_y;            ///下移

    char input_5;
    if(kbhit())                                            ///游戏暂停操作
    {
        input_5 = getch();
        if(input_5 == 'p' || input_5 == 'P')
        {
            gamestatus2 = 2;
        }

    }
}

void background_over()    ///游戏结束背景
{
    putimage(0, 0, gameover);
    mciSendString(TEXT("stop backmusic\\music4.mp3"), NULL, 0, NULL);     ///暂停关闭游戏音乐3
    mciSendString(TEXT("close backmusic\\music4.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("stop backmusic\\music5.mp3"), NULL, 0, NULL);    ///暂停关闭游戏音乐2
    mciSendString(TEXT("close backmusic\\music5.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("stop backmusic\\huankuai.mp3"), NULL, 0, NULL);    ///暂停关闭游戏音乐1
    mciSendString(TEXT("close backmusic\\huankuai.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play backmusic\\music3.mp3 repeat"), NULL, 0, NULL);       ///打开游戏结束背景音乐

    setbkmode(TRANSPARENT);                                              ///游戏结束背景字
    setcolor(YELLOW);
    setfont(50, 0, "楷体");
    xyprintf(120, 20, "得 分");
    xyprintf(147, 80, "%d", allsocre[0]);
    xyprintf(300, 100, "G A M E   O V E R");
    xyprintf(340, 200, "~~~oo(^_^)oo~~~");
    xyprintf(380, 290, "请继续努力!!");
    xyprintf(430, 370, "可怜的");
    xyprintf(305, 450, "。。。小鱼。。。");
}

void fistwin()      ///第一关过关
{
    if(socre_p1 >= 620)
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
                    passchange = 1;
                }
                if(lick_1.is_up())
                {
                    passchange = 2;
                }
            }
          }
          if(passchange == 2) break;
       }
     }
}

void secondwin()
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
            putimage_transparent(NULL, wancheng, 380, 200, 0);
            putimage_transparent(NULL, next, 480, 300, 0);
            while(mousemsg())
            {
                lick_2 = getmouse();
                if(lick_2.x >= 480 && lick_2.x <= 542 && lick_2.y >= 300 && lick_2.y <= 356)
                {
                    if(lick_2.is_down())
                    {
                        passchange = 2;
                    }
                    if(lick_2.is_down())
                    {
                        passchange = 3;
                    }
                }
            }
            if(passchange == 3)
                break;
        }
    }
}

void thirdwin()
{
    if(socre_p3 >= 1000)
    {
        mciSendString(TEXT("stop backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("close backmusic\\bit.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("stop backmusic\\win.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("close backmusic\\win.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("play backmusic\\win.mp3"), NULL, 0, NULL);
        while(1)
        {
            setbkmode(TRANSPARENT);
            setcolor(RED);
            setfont(40, 0, "楷体");
            xyprintf(360, 200, "恭  喜  过  关！！！！");
            putimage_transparent(NULL, wancheng, 380, 300, 0);
            Sleep(3000);
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
    while(1)           ///进入菜单页面
    {
    if(backchange == 0 && goback == 0)
    {
        mciSendString(TEXT("play backmusic\\music2.mp3 repeat"), NULL, 0, NULL);

        formbackground();
    }

    if(backchange == 1 && goback == 1)
    {
        mciSendString(TEXT("stop backmusic\\music2.mp3"), NULL, 0, NULL);
        mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///关闭菜单页面音乐1
        mciSendString(TEXT("play backmusic\\music1.mp3 repeat"), NULL, 0, NULL);              ///播放菜单页面音乐2

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
        mciSendString(TEXT("colse backmusic\\music2.mp3"), NULL, 0, NULL);              ///关闭菜单页面音乐1
        mciSendString(TEXT("play backmusic\\music5.mp3 repeat"), NULL, 0, NULL);              ///播放菜单页面音乐3

        background_2();

        if(backchange == 0 && goback == 0)
        {
            mciSendString(TEXT("stop backmusic\\music5.mp3"), NULL, 0, NULL);
            mciSendString(TEXT("close backmusic\\music5.mp3"), NULL, 0, NULL);
        }

    }
    if(flag == 2)
        break;                                                     ///是否进入游戏页面
    }

    while(1)                ///进入选择关卡
    {
        choosepass();
        if(passchange == 1)
            break;
    }

    while(1)        ///第一关数据
    {
        if((backchange == 0 && gamestatus == 0))
        {
        initdata1();
        data_withoutinput1();
        data_withinput1();

        while(gamestatus == 2)           ///判断游戏是否继续
        restart_menu1();

        fistwin();
        if(passchange == 2)           ///第一关是否结束
            break;

        Sleep(1);                     ///解决对图片切换时的闪屏问题
        cleardevice();
        if(alive == 0 || resttime < 0.0)
            break;
        }
    }

    if(alive > 0 && resttime >= 0.0)    ///第二关
    {

    mciSendString(TEXT("close backmusic\\win.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("stop backmusic\\huankuai.mp3"), NULL, 0, NULL);              ///关闭第一关背景音乐
    mciSendString(TEXT("colse backmusic\\huankuai.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play backmusic\\music5.mp3 repeat"), NULL, 0, NULL);           ///打开第二关背景音乐
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
            if(passchange == 3)
                    break;

             Sleep(1);
             cleardevice();
             if(alive1 == 0 || resttime1 < 0.0)
                break;
         }
    }
    }

    if(alive > 0 && resttime >= 0.0 && alive1 > 0 && resttime1 >= 0.0)  ///第三关
    {

    mciSendString(TEXT("close backmusic\\win.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("stop backmusic\\music5.mp3"), NULL, 0, NULL);              ///关闭第一关背景音乐
    mciSendString(TEXT("colse backmusic\\music5.mp3"), NULL, 0, NULL);
    mciSendString(TEXT("play backmusic\\music4.mp3 repeat"), NULL, 0, NULL);           ///打开第二关背景音乐

      every_data3();
       while(1)
       {
          if(gamestatus2 == 0)
          {
             initdata3();
             data_withoutinput3();
             data_withinput3();

             while(gamestatus2 == 2)
                restart_menu3();

             thirdwin();
             if(socre_p3 >= 1000)
                break;

              Sleep(1);
            cleardevice();
            if(alive2 == 0 || resttime2 < 0.0)
                break;
          }
       }
    }

    allsocre[0] = socre_p1 + socre_p2 + socre_p3;
    WriteFile();          ///存储分数数据

    if(alive == 0 || alive1 == 0 || alive2 == 0 || resttime < 0.0 || resttime1 < 0.0 || resttime2 < 0.0)
       background_over();
    Sleep(4000);

    game_over();
    return 0;
}



