#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACEBAR 32
#define ESC 27
//(0,0)~(79,24)
struct APoint {
	int x;
	int y;
};
void gotoxy(int x, int y)
{
	COORD cd;
	cd.X = x;
	cd.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}
int main() {
	struct APoint player;
	printf("¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¡á¢Ã\n");
	printf("¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã¢Ã\n");
	char ch;
	player.x = 2;
	player.y = 1;
	gotoxy(player.x, player.y);
	while (1) {
		if (_kbhit()) {
			ch = _getch();
			if (ch == -32) {
				ch = _getch();
				switch (ch) {
				case LEFT:
					if (player.x > 2)gotoxy(player.x -= 2, player.y);
					break;

				case RIGHT:
					if (player.x <= 28)gotoxy(player.x += 2, player.y);
					break;
				case UP:
					if (player.y > 1)gotoxy(player.x, player.y-=1);
					break;
				case DOWN:
					if (player.y <= 14)gotoxy(player.x, player.y+=1);
					break;
				default:
					break;
				}
			}
			
		}
	}

}
