#include "head.h"
#define MAXSTAR 100
Star star[200];

void menu(int& sel) {
	char option[][20] = { "CXK走迷宫","FLAPPY CAI","CXK推箱子","贪吃的CXK","CXK的连连看","退出" };
	//解释：菜单选项的文本保存在字符数组中
	char key = 0;
	//解释：保存键值的key变量
	int i, select = 0;
	//解释：i为循环变量，select为指针
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//解释：获得控制台
	while (1) {
		gotoxy(50, 2);
		//解释：制定菜单的位置
		puts("menu");
		for (i = 0; i < 6; i++) {
			//解释：六个选项循环输入
			if (i == select)
				SetConsoleTextAttribute(handle, BACKGROUND_BLUE | FOREGROUND_RED | BACKGROUND_INTENSITY);
			//解释：用SetConsoleTextAttribute函数调色
			else if (i == select + 1)
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			//解释：恢复非高亮设置
			gotoxy(47, 4 + i);
			puts(option[i]);
		}
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		key = _getch();
		//解释：等待键盘输入
		if (key == 0x1b)  //ESC 键
			return;
		if (key == 0xd)  //Enter 键
			break;
		if (key < 0) {  //非ascii码键2个字节
			key = _getch();
			switch (MapVirtualKey(key, 1)) {
			case VK_UP:
				select = (select + 5) % 6;
				break;
			case VK_DOWN:
				select = (select + 1) % 6;
				break;
			}
			//解释：这里采用循环队列指针移动的方式，通过取模达到循环移动的效果
		}
		system("cls");
	}
	system("cls");
	//解释：清屏
	sel = select;
	//解释：sel给外部的switch语句用
}

void gotoxy(int x, int y) //goto语句
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void HideCursor() //隐藏光标 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}

//游戏结束界面的主体代码部分
void InitStar(int i)
{
	star[i].x = 0;
	star[i].y = rand() % 480;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}
//解释：初始化星星（像素点），因为要铺满平面，所以y值是小于画面纵坐标的随机数，星星是一个结构体，它的step是每一次循环向前走的长度，表现为速度，color是RGB调色，此次调成白色。
void MoveStar(int i)
{
	putpixel((int)star[i].x, star[i].y, 0);
	//解释：画像素点的函数
	star[i].x += star[i].step;
	//解释：每一次都要向前走
	if (star[i].x > 640)	InitStar(i);
	//解释：如果星星的x坐标超过画面的横坐标，就初始化位置
	putpixel((int)star[i].x, star[i].y, star[i].color);
}

void enDgame()
{
	srand((unsigned)time(NULL));	// 随机种子
	initgraph(640, 480);			// 创建绘图窗口

	//解释：初始化画布，确定大小
	for (int i = 0; i < MAXSTAR; i++)
	{
		InitStar(i);
		star[i].x = rand() % 640;
	}

	while (!_kbhit())
	{
		IMAGE img;
		loadimage(&img, _T("C:\\Users\\Hyxpillow\\Desktop\\timg.jpg"));
		putimage(240, 160, &img);
		outtextxy(260, 300, TEXT("game over"));
		for (int i = 0; i < MAXSTAR; i++)
			MoveStar(i);
		Sleep(20);
	}
	//解释：当没有键盘敲击的时候，在制定位置加载一张图片，和一行game over文字，并依次移动每一个星星，速度是随机数的形式
	closegraph();
	getchar();
}