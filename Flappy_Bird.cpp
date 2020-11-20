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
	//解释：设置地图幅度，鸟的坐标，水管（障碍）的坐标
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
//解释：由于最终的界面是和一个二维数组完全对应。所以初始化数组就显得非常重要。这里将围墙，水管，小鸟对应的二维数组上的位置都设定了不同的值，便于对应画图。
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
	printf("您当前的分数是%d", Score);
}
//解释：gotoxy找到起始位置，然后对应数组上的值来画图。并有一行文字显示得分
bool Update() {
	char input;
	if (_kbhit()) {
		//解释：_kbhit()只要有键盘敲击，就为真，然后同时为_getch输入
			input = _getch();
		if (input == ' ');
		bird_x = bird_x - 1;
		return true;
	}
	return false;
}
//解释：与输入值有关的更新
bool Isdie() {
	if (bird_x >= Map_height || Map[bird_x][bird_y] == 2)
		return true;
	else return false;
}
//解释：判断鸟的死亡条件，也是二维数组的坐标关系
void Update1() {
	bird_x++;//小鸟下落一个格子
	tube_x--;//水管向前一个格子
	Sleep(150);
}
//解释：与输入无关的更新，就是无论如何都会进行的更新
void GameRunner() {
	while (1) {
		InitMap();
		//解释：每次根据更新后数组上值的变化来更新地图
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
			Score = 0;
		}

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
