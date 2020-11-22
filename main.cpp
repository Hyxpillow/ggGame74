#include "head.h"
#include "Flappy_Bird.h"
#include "Snake.h"

int main() {
	int sel = 0;
	while (1) {
		menu(sel);
		switch (sel)
		{
		case 1: bird(); break;
		case 3: snake(); break;
		case 5: return 0;
		default: break;
		}
		system("cls");
	}
	return 0;
}