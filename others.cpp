#include "head.h"

void menu(int& sel) {
	char option[][20] = { "CXK���Թ�","FLAPPY CAI","CXK������","̰�Ե�CXK","CXK��������","�˳�" };
	//���ͣ��˵�ѡ����ı��������ַ�������
	char key = 0;
	//���ͣ������ֵ��key����
	int i, select = 0;
	//���ͣ�iΪѭ��������selectΪָ��
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//���ͣ���ÿ���̨
	while (1) {
		gotoxy(50, 2);
		//���ͣ��ƶ��˵���λ��
		puts("menu");
		for (i = 0; i < 6; i++) {
			//���ͣ�����ѡ��ѭ������
			if (i == select)
				SetConsoleTextAttribute(handle, BACKGROUND_BLUE | FOREGROUND_RED | BACKGROUND_INTENSITY);
			//���ͣ���SetConsoleTextAttribute������ɫ
			else if (i == select + 1)
				SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			//���ͣ��ָ��Ǹ�������
			gotoxy(47, 4 + i);
			puts(option[i]);
		}
		SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		key = _getch();
		//���ͣ��ȴ���������
		if (key == 0x1b)  //ESC ��
			return;
		if (key == 0xd)  //Enter ��
			break;
		if (key < 0) {  //��ascii���2���ֽ�
			key = _getch();
			switch (MapVirtualKey(key, 1)) {
			case VK_UP:
				select = (select + 5) % 6;
				break;
			case VK_DOWN:
				select = (select + 1) % 6;
				break;
			}
			//���ͣ��������ѭ������ָ���ƶ��ķ�ʽ��ͨ��ȡģ�ﵽѭ���ƶ���Ч��
		}
		system("cls");
	}
	system("cls");
	//���ͣ�����
	sel = select;
	//���ͣ�sel���ⲿ��switch�����
}

void gotoxy(int x, int y) //goto���
{
	COORD pos;
	pos.X = x - 1;
	pos.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void HideCursor() //���ع�� 
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
}