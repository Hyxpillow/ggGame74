#include "head.h"
#define MAXSTAR 100

int Map[100][100];
int Map_height;
int Map_width;
int bird_x;
int bird_y;
int tube_x;
int tube_y;
int Score = 0;

Star star[200];

void InitData() {
	Map_height = 30;
	Map_width = 50;
	bird_x = Map_width / 4;
	bird_y = Map_height / 2;
	tube_x = Map_width / 4 * 3;
	tube_y = Map_height / 2;
	HideCursor();
	//���ͣ����õ�ͼ���ȣ�������꣬ˮ�ܣ��ϰ���������
}
void InitMap() {
	system("cls");
	for (int i = 1; i <= Map_height - 1; i++) {
		Map[i][1] = 4;
		for (int j = 2; j < Map_width - 1; j++)
			Map[i][j] = 0;
		Map[i][Map_width] = 4;
	}
	for (int j = 1; j < tube_y; j++) {
		Map[j][tube_x] = 2;
	}
	for (int j = tube_y + 2; j < Map_height; j++) {
		Map[j][tube_x] = 2;
	}
	for (int j = 1; j <= Map_width; j++) {
		Map[Map_height][j] = 3;
	}
	Map[bird_x][bird_y] = 1;
}
//���ͣ��������յĽ����Ǻ�һ����ά������ȫ��Ӧ�����Գ�ʼ��������Ե÷ǳ���Ҫ�����ｫΧǽ��ˮ�ܣ�С���Ӧ�Ķ�ά�����ϵ�λ�ö��趨�˲�ͬ��ֵ�����ڶ�Ӧ��ͼ��
void draw() {
	gotoxy(0, 0);
	for (int i = 1; i <= Map_height; i++) {
		for (int j = 1; j <= Map_width; j++) {
			switch (Map[i][j]) {
			case 0:
				printf(" ");
				break;
			case 1:
				printf("@");
				break;
			case 2:
				printf("+");
				break;
			case 3:
				printf("-");
				break;
			case 4:
				printf("|");
				break;
			}
		}
		printf("\n");
	}
	printf("Flappy Bird\n");
	printf("����ǰ�ķ�����%d", Score);
}
//���ͣ�gotoxy�ҵ���ʼλ�ã�Ȼ���Ӧ�����ϵ�ֵ����ͼ������һ��������ʾ�÷�
bool Update() {
	char input;
	if (_kbhit()) {
		//���ͣ�_kbhit()ֻҪ�м����û�����Ϊ�棬Ȼ��ͬʱΪ_getch����
			input = _getch();
		if (input == ' ');
		bird_x = bird_x - 1;
		return true;
	}
	return false;
}
//���ͣ�������ֵ�йصĸ���
bool Isdie() {
	if (bird_x >= Map_height || Map[bird_x][bird_y] == 2)
		return true;
	else return false;
}
//���ͣ��ж��������������Ҳ�Ƕ�ά����������ϵ
void Update1() {
	bird_x++;//С������һ������
	tube_x--;//ˮ����ǰһ������
	Sleep(150);
}
//���ͣ��������޹صĸ��£�����������ζ�����еĸ���
void GameRunner() {
	while (1) {
		InitMap();
		//���ͣ�ÿ�θ��ݸ��º�������ֵ�ı仯�����µ�ͼ
			draw();
		Update1();
		if (Isdie()) {
			return;
		}
		else {
			if (Update()) {
				bird_x--;
				if (bird_x < 2) bird_x = 1;
				Map[bird_x][bird_y] = 1;

			}
			if (bird_y == tube_x + 1) {
				Score++;
			}
			if (tube_x < 0) {
				srand(time(NULL));
				tube_x = 3 * Map_width / 4;
				do {
					tube_y = rand() % 20;
				} while (tube_y <= 4 || tube_y >= 16);
			}
		}
	}
}
void bird() {
	char buf[20];
	//���ͣ��û�������ַ�������
		while (1) {
			InitData();
			GameRunner();
			InputBox((LPTSTR)buf, 20, TEXT("������(Y/N)"));
			//���ͣ��������ڣ����û���Ҫ��Ҫ�����棬��һ�������ǻ����������飨���ݶ���ǿ������ת�������ڶ��������������ַ����ƣ��������Ǵ����ϵ�����
				if (buf[0] != 'Y') {

					enDgame();
					break;
				}
			Score = 0;
		}

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
