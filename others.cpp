#include "head.h"

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