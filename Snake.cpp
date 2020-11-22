#include "head.h"
#include "Snake.h"
#define MaxSnakeLength 225
#define Snake_Map_Width 15
#define Snake_Map_Height 15

int b[2];
int temp_x, temp_y;
int look[4];//0
int xy[2];//起始位置
int bk[16][16];//地图大小
int pp, qq;//果实位置
int snakeBody[800], front, rear;
int flag;

bool enqueue(int t) {
	if (front == (rear + 1) % MaxSnakeLength)return 0;
	snakeBody[rear] = t;
	rear = (rear + 1) % (MaxSnakeLength * 2);
	return 1;
}

bool dequeue( int *t) {
	if (front == rear) return 0;
	*t = snakeBody[front];
	front = (front + 1) % (MaxSnakeLength * 2);
	return 1;
}

void Snake_InitMap() {
	for (int i = 1; i <= Snake_Map_Height; i++){
		bk[1][i] = 1;
	}
	for (int i = 2; i <= Snake_Map_Height - 1; i++) {
		bk[i][1] = 1;
		for (int j = 2; j <= Snake_Map_Width - 1; j++)
			bk[i][j] = 0;
		bk[i][Snake_Map_Width] = 1;
	}
	for (int i = 1; i <= Snake_Map_Height; i++) {
		bk[15][i] = 1;
	}
	srand(time(NULL));
	do  {
		pp = rand() % 15 + 1;
		qq = rand() % 15 + 1;
	} while (bk[pp][qq] != 0);
	bk[pp][qq] = 2;
	look[0] = rand() % 4 + 1;
	look[1] = 1;//蛇身长度
	look[2] = look[3] = 0;
	xy[0] = xy[1] = 7;//起始位置
	front = rear = 0;
	enqueue(xy[1]);
	enqueue(xy[0]);
}

void snake_draw() {
	system("cls");
	for (int i = 1; i <= Snake_Map_Height; i++) {
		for (int j = 1; j <= Snake_Map_Width; j++) {
			switch (bk[i][j]) {
			case 0:
				printf(" ");
				break;
			case 1:
				printf("*");
				break;
			case 2:
				printf("@");
				break;
			case 3:
				printf("0");
				break;
			}
		}
		printf("\n");
	}
	//gotoxy(60, 0);
	//BackGround(7, 0); //背景颜色的代码： 0=黑色  1蓝色 2 绿色 3湖蓝色 4红色 5紫色 6黄色 7白色 8灰色 9淡蓝色
	printf("现在得分是:%d,请再接再厉!^_^", look[2]);
	Sleep(150);
}

void snake() {
	Snake_InitMap();
	while (1) {
		snake_draw();
//---------------------读取键盘并移动------------------------------//
		if (_kbhit()) {//记录按下的是哪个方向键
			b[0] = _getch();//用b来记录
			if (b[0] == 224)  b[0] = _getch();//如果为224表示为方向键，但是要再一次获取才行
			if (b[0] == 72 && look[0] != 2)
				//如果输入的为上并且朝向不为下
				look[0] = 1;
			if (b[0] == 80 && look[0] != 1)
				look[0] = 2;
			if (b[0] == 75 && look[0] != 4)
				look[0] = 3;
			if (b[0] == 77 && look[0] != 3)
				look[0] = 4;
		}
		switch (look[0]) {
		case 1:
			//往上走
			xy[1]--;
			break;
		case 2:
			//往下走
			xy[1]++;
			break;
		case 3:
			//往左走
			xy[0]--;
			break;
		case 4:
			//往右走
			xy[0]++;
			break;
		}

//-------------------如果吃了果实-----------------------------//
		if (bk[xy[1]][xy[0]] == 2) {
			look[2]++;//分数加一
			look[1]++;//长度加一
			flag = 1;
			
			//更新分数
			while (bk[pp][qq] != 0) {
				pp = rand() % 15 + 1;
				qq = rand() % 15 + 1;
			}
			bk[pp][qq] = 2;//将这个地方变为果实
			gotoxy(pp * 2, qq);
			//BackGround(0, 2);
			printf("  ");
		}

//--------------------如果撞墙或者吃到自己----------------------//
			//如果撞了墙或者自己//
		if (bk[xy[1]][xy[0]] == 1 || bk[xy[1]][xy[0]] == 3) {
			look[3] = 1;//表示已经输了
			gotoxy(6, 6);
			//BackGround(7, 0);
			system("cls");
			break;
		}
//--------------------刷新蛇的位置-----------------------------//
		//gotoxy(i * 2, j);
		//BackGround(0, 0);
		//printf("  ");
		bk[xy[1]][xy[0]] = 3;//使这个位置变成蛇
		enqueue(xy[1]); enqueue(xy[0]);
		if (flag == 0) {
			dequeue(&temp_y); dequeue(&temp_x);
			bk[temp_y][temp_x] = 0;
		}
		else
			flag = 0;
	}
	printf("你输了，最后得分:%d", look[2]);
	enDgame();
}