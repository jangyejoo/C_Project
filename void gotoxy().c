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