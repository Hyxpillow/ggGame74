#ifndef Flappy_Bird
#define Flappy_Bird

typedef struct {
	int x;
	int y;
	int color;
	int step;
}Star;

void InitData();
void InitMap();
void draw();
bool Update();
bool Isdie();
void Update1();
void GameRunner();
void bird();
void InitStar(int);
void MoveStar(int);
void enDgame();
#endif // !Flappy_Bird



