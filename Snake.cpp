#include "head.h"
#include "Snake.h"
#define MaxSnakeLength 225
#define Snake_Map_Width 15
#define Snake_Map_Height 15

int b[2];
int temp_x, temp_y;
int look[4];//0
int xy[2];//��ʼλ��
int bk[16][16];//��ͼ��С
int pp, qq;//��ʵλ��
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
	look[1] = 1;//������
	look[2] = look[3] = 0;
	xy[0] = xy[1] = 7;//��ʼλ��
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
	//BackGround(7, 0); //������ɫ�Ĵ��룺 0=��ɫ  1��ɫ 2 ��ɫ 3����ɫ 4��ɫ 5��ɫ 6��ɫ 7��ɫ 8��ɫ 9����ɫ
	printf("���ڵ÷���:%d,���ٽ�����!^_^", look[2]);
	Sleep(150);
}

void snake() {
	Snake_InitMap();
	while (1) {
		snake_draw();
//---------------------��ȡ���̲��ƶ�------------------------------//
		if (_kbhit()) {//��¼���µ����ĸ������
			b[0] = _getch();//��b����¼
			if (b[0] == 224)  b[0] = _getch();//���Ϊ224��ʾΪ�����������Ҫ��һ�λ�ȡ����
			if (b[0] == 72 && look[0] != 2)
				//��������Ϊ�ϲ��ҳ���Ϊ��
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
			//������
			xy[1]--;
			break;
		case 2:
			//������
			xy[1]++;
			break;
		case 3:
			//������
			xy[0]--;
			break;
		case 4:
			//������
			xy[0]++;
			break;
		}

//-------------------������˹�ʵ-----------------------------//
		if (bk[xy[1]][xy[0]] == 2) {
			look[2]++;//������һ
			look[1]++;//���ȼ�һ
			flag = 1;
			
			//���·���
			while (bk[pp][qq] != 0) {
				pp = rand() % 15 + 1;
				qq = rand() % 15 + 1;
			}
			bk[pp][qq] = 2;//������ط���Ϊ��ʵ
			gotoxy(pp * 2, qq);
			//BackGround(0, 2);
			printf("  ");
		}

//--------------------���ײǽ���߳Ե��Լ�----------------------//
			//���ײ��ǽ�����Լ�//
		if (bk[xy[1]][xy[0]] == 1 || bk[xy[1]][xy[0]] == 3) {
			look[3] = 1;//��ʾ�Ѿ�����
			gotoxy(6, 6);
			//BackGround(7, 0);
			system("cls");
			break;
		}
//--------------------ˢ���ߵ�λ��-----------------------------//
		//gotoxy(i * 2, j);
		//BackGround(0, 0);
		//printf("  ");
		bk[xy[1]][xy[0]] = 3;//ʹ���λ�ñ����
		enqueue(xy[1]); enqueue(xy[0]);
		if (flag == 0) {
			dequeue(&temp_y); dequeue(&temp_x);
			bk[temp_y][temp_x] = 0;
		}
		else
			flag = 0;
	}
	printf("�����ˣ����÷�:%d", look[2]);
	enDgame();
}