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
	//解释：设置地图幅度，鸟的坐标，水管（障碍）的坐标
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
//解释：由于最终的界面是和一个二维数组完全对应。所以初始化数组就显得非常重要。这里将围墙，水管，小鸟对应的二维数组上的位置都设定了不同的值，便于对应画图。
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
	printf("您当前的分数是%d", bird_Score);
}
//解释：gotoxy找到起始位置，然后对应数组上的值来画图。并有一行文字显示得分
bool Update() {
	char input;
	if (_kbhit()) {
		//解释：_kbhit()只要有键盘敲击，就为真，然后同时为_getch输入
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
//解释：与输入值有关的更新
bool Isdie() {
	if (bird_x >= bird_Map_height || bird_Map[bird_x][bird_y] == 2)
		return true;
	else return false;
}
//解释：判断鸟的死亡条件，也是二维数组的坐标关系
void Update1() {
	Sleep(150);
	gotoxy(bird_y, bird_x);
	putchar(' ');
	bird_Map[bird_x][bird_y] = 0;
	bird_x++;//小鸟下落一个格子
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
	tube_x--;//水管向前一个格子
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
//解释：与输入无关的更新，就是无论如何都会进行的更新
void GameRunner() {
	InitMap();
	//解释：每次根据更新后数组上值的变化来更新地图
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
	//解释：用户输入的字符缓冲区
	while (1) {
		InitData();
		GameRunner();
		InputBox((LPTSTR)buf, 20, TEXT("还玩吗？(Y/N)"));
		//解释：交互窗口，问用户还要不要继续玩，第一个参数是缓冲区的数组（根据定义强制类型转换），第二个参数是输入字符限制，第三个是窗口上的文字
		if (buf[0] != 'Y') {
			enDgame();
			break;
		}
		bird_Score = 0;
	}

}



