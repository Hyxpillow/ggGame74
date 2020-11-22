#ifndef others
#define others
typedef struct {
	int x;
	int y;
	int color;
	int step;
}Star;

void gotoxy(int x, int y);
void HideCursor();
void menu(int& sel);
void enDgame();

#endif // !others


