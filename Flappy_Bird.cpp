#include "head.h"
#include "Flappy_Bird.h"


int bird_Map[100][100];
int bird_Map_height;
int bird_Map_width;
int bird_x;
int bird_y;
int tube_x;
int tube_y;
int bird_Score;
int bird_flag;


void InitData() {
	bird_Map_height = 20;
	bird_Map_width = 40;
	bird_x = bird_Map_width / 4;
	bird_y = bird_Map_height / 2;
	tube_x = bird_Map_width / 4 * 3;
	tube_y = bird_Map_height / 2;
	bird_Score = 0;
	bird_flag = 0;
	HideCursor();
	//���ͣ����õ�ͼ���ȣ�������꣬ˮ�ܣ��ϰ���������
}
void InitMap() {
	for (int i = 1; i <= bird_Map_height - 1; i++) {
		bird_Map[i][1] = 4;
		for (int j = 2; j < bird_Map_width - 1; j++)
			bird_Map[i][j] = 0;
		bird_Map[i][bird_Map_width] = 4;
	}
	for (int j = 1; j < tube_y; j++) {
		bird_Map[j][tube_x] = 2;
	}
	for (int j = tube_y + 4; j < bird_Map_height; j++) {
		bird_Map[j][tube_x] = 2;
	}
	for (int j = 1; j <= bird_Map_width; j++) {
		bird_Map[bird_Map_height][j] = 3;
	}
	bird_Map[bird_x][bird_y] = 1;
}
//���ͣ��������յĽ����Ǻ�һ����ά������ȫ��Ӧ�����Գ�ʼ��������Ե÷ǳ���Ҫ�����ｫΧǽ��ˮ�ܣ�С���Ӧ�Ķ�ά�����ϵ�λ�ö��趨�˲�ͬ��ֵ�����ڶ�Ӧ��ͼ��
void draw() {
	system("cls");
	for (int i = 1; i <= bird_Map_height; i++) {
		for (int j = 1; j <= bird_Map_width; j++) {
			switch (bird_Map[i][j]) {
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
	printf("����ǰ�ķ�����%d", bird_Score);
}
//���ͣ�gotoxy�ҵ���ʼλ�ã�Ȼ���Ӧ�����ϵ�ֵ����ͼ������һ��������ʾ�÷�
bool Update() {
	char input;
	if (_kbhit()) {
		//���ͣ�_kbhit()ֻҪ�м����û�����Ϊ�棬Ȼ��ͬʱΪ_getch����
		input = _getch();
		//if (input == ' ');
		gotoxy(bird_y, bird_x);
		putchar(' ');
		bird_x -= 2;
		gotoxy(bird_y, bird_x);
		putchar('@');
		return true;
	}
	return false;
}
//���ͣ�������ֵ�йصĸ���
bool Isdie() {
	if (bird_x >= bird_Map_height || bird_Map[bird_x][bird_y] == 2)
		return true;
	else return false;
}
//���ͣ��ж��������������Ҳ�Ƕ�ά����������ϵ
void Update1() {
	Sleep(150);
	gotoxy(bird_y, bird_x);
	putchar(' ');
	bird_Map[bird_x][bird_y] = 0;
	bird_x++;//С������һ������
	gotoxy(bird_y, bird_x);
	putchar('@');
	bird_Map[bird_x][bird_y] = 1;

	if (tube_x > 1) {
		for (int j = 1; j < tube_y; j++) {
			gotoxy(tube_x, j);
			putchar(' ');
			bird_Map[j][tube_x] = 0;
		}
		for (int j = tube_y + 4; j < bird_Map_height; j++) {
			gotoxy(tube_x, j);
			putchar(' ');
			bird_Map[j][tube_x] = 0;
		}
	}
	tube_x--;//ˮ����ǰһ������
	if (tube_x > 1){
		for (int j = 1; j < tube_y; j++) {
			gotoxy(tube_x, j);
			putchar('+');
			bird_Map[j][tube_x] = 2;
		}
		for (int j = tube_y + 4; j < bird_Map_height; j++) {
			gotoxy(tube_x, j);
			putchar('+');
			bird_Map[j][tube_x] = 2;
		}
	}
}
//���ͣ��������޹صĸ��£�����������ζ�����еĸ���
void GameRunner() {
	InitMap();
	//���ͣ�ÿ�θ��ݸ��º�������ֵ�ı仯�����µ�ͼ
	draw();
	while (1) {
		Update1();
		if (Isdie()) {
			return;
		}
		else {
			if (Update()) {
				if (bird_x < 2) bird_x = 1;
				bird_Map[bird_x][bird_y] = 1;
			}
			if (bird_y == tube_x + 1) {
				bird_Score++;
				gotoxy(15, 22);
				printf("%d",bird_Score);
			}
			if (tube_x < 0) {
				srand((unsigned int)time(NULL));
				tube_y = rand() % 11 + 5;
				tube_x = 4 * bird_Map_width / 5;
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
		bird_Score = 0;
	}

}



