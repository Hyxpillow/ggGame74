#include "head.h"
#define MAXSTAR 100
Star star[200];

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

//��Ϸ���������������벿��
void InitStar(int i)
{
	star[i].x = 0;
	star[i].y = rand() % 480;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}
//���ͣ���ʼ�����ǣ����ص㣩����ΪҪ����ƽ�棬����yֵ��С�ڻ�����������������������һ���ṹ�壬����step��ÿһ��ѭ����ǰ�ߵĳ��ȣ�����Ϊ�ٶȣ�color��RGB��ɫ���˴ε��ɰ�ɫ��
void MoveStar(int i)
{
	putpixel((int)star[i].x, star[i].y, 0);
	//���ͣ������ص�ĺ���
	star[i].x += star[i].step;
	//���ͣ�ÿһ�ζ�Ҫ��ǰ��
	if (star[i].x > 640)	InitStar(i);
	//���ͣ�������ǵ�x���곬������ĺ����꣬�ͳ�ʼ��λ��
	putpixel((int)star[i].x, star[i].y, star[i].color);
}

void enDgame()
{
	srand((unsigned)time(NULL));	// �������
	initgraph(640, 480);			// ������ͼ����

	//���ͣ���ʼ��������ȷ����С
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
	//���ͣ���û�м����û���ʱ�����ƶ�λ�ü���һ��ͼƬ����һ��game over���֣��������ƶ�ÿһ�����ǣ��ٶ������������ʽ
	closegraph();
	getchar();
}