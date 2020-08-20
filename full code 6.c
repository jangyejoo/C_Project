#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACEBAR 32
#define MAX 30
//(0,0)~(79,24)
struct Point {
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
struct mineboard {
	bool mine;
	bool block;
	bool flag;
	bool wall;
	int minecount;
};
struct mineboard m[MAX][MAX];

int Lv1[3], Lv2[3], Lv3[3];

int levelSelect();
void levelSelectMenu();
void makeMap(struct mineboard(*m)[MAX], int gamelevel);
void randMine(struct mineboard(*m)[MAX], int gamelevel);
int gameLog();
int gameStart(struct mineboard(*m)[MAX], int gamelevel); //수정
void mainMenu();
void mineRecursive(struct mineboard(*m)[MAX], int tmpX, int tmpY, int* retMine);
void rank();
void displayMap(struct mineboard(*m)[MAX], int gamelevel);
int resultFunc(struct mineboard(*m)[MAX], int gamelevel);
void howtoPlay();
int speedUnlock(struct mineboard(*m)[MAX], int tmpX, int tmpY); //이름 수정
void printRetMine(int gamelevel, int* retMine); 
void sort_zero(int Lv[], int elapsedTime); //추가
void sort(int Lv[], int elapsedTime); //추가

void printRetMine(int gamelevel, int* retMine) { 
	gotoxy(gamelevel * 2 + 5, 3);
	printf("남은 지뢰 개수 : %3d", *retMine); 
}

void mainMenu() {
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("▩                              ▩");
	puts("▩       § 지뢰 찾기 §        ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩        1. 게임 시작          ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩        2. 순위 보기          ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩        3. 게임 방법          ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩        4. 게임 종료          ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("");
	printf(">>>\n");
}

int levelSelect() {
	int select;
	while (1) {
		system("cls");
		levelSelectMenu();
		scanf("%d", &select);
		if (select == 1) return 15;
		else if (select == 2) return 20;
		else if (select == 3) return 25;
		else continue;
	}
}

void levelSelectMenu() {
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("▩                          ▩");
	puts("▩     ※난이도 선택※      ▩");
	puts("▩                          ▩");
	puts("▩        1. 초급           ▩");
	puts("▩                          ▩");
	puts("▩        2. 중급           ▩");
	puts("▩                          ▩");
	puts("▩        3. 고급           ▩");
	puts("▩                          ▩");
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("");
	printf(">>>");
}

void mineRecursive(struct mineboard(*m)[MAX], int tmpX, int tmpY, int* retMine) {
	int i, j;
	if (m[tmpX][tmpY].block == 1) return;
	else if (m[tmpX][tmpY].wall == 1) return;
	else if (m[tmpX][tmpY].minecount != 0) {
		m[tmpX][tmpY].block = 1;
		if (m[tmpX][tmpY].flag == 1) {
			m[tmpX][tmpY].flag = 0;
			++* retMine;
		}
		return;
	}
	else {
		m[tmpX][tmpY].block = 1;
		if (m[tmpX][tmpY].flag == 1) {
			m[tmpX][tmpY].flag = 0;
			++* retMine;
		}
		for (i = tmpX - 1; i < tmpX + 2; i++) {
			for (j = tmpY - 1; j < tmpY + 2; j++) {
				mineRecursive(m, i, j, retMine);
			}
		}
	}
}

void makeMap(struct mineboard(*m)[MAX], int gamelevel) {
	for (int i = 0; i < gamelevel; i++) {
		for (int j = 0; j < gamelevel; j++) {
			if (i == 0 || i == gamelevel - 1 || j == 0 || j == gamelevel - 1) {
				m[i][j].wall = 1;
				m[i][j].mine = 0;
				m[i][j].block = 0;
				m[i][j].flag = 0;
				m[i][j].minecount = 0;
			}
			else {
				m[i][j].wall = 0;
				m[i][j].mine = 0;
				m[i][j].block = 0;
				m[i][j].flag = 0;
				m[i][j].minecount = 0;
			}
		}
	}
	randMine(m, gamelevel);
	for (int i = 1; i < gamelevel - 1; i++) {
		for (int j = 1; j < gamelevel - 1; j++) {
			for (int k = i - 1; k < i + 2; k++) {
				for (int l = j - 1; l < j + 2; l++) {
					if (m[k][l].mine == 1) {
						m[i][j].minecount++;
					}
					else continue;
				}
			}
		}
	}
}

void randMine(struct mineboard(*m)[MAX], int gamelevel) {
	int mineCnt = 0;
	if (gamelevel == 15) mineCnt = 20;
	else if (gamelevel == 20) mineCnt = 50;
	else if (gamelevel == 25) mineCnt = 109;
	srand((unsigned int)time(NULL)); 
	do {
		int i, j;
		i = (rand() % (gamelevel - 2) + 1);
		j = (rand() % (gamelevel - 2) + 1);
		if (m[i][j].mine == 0) {
			m[i][j].mine = 1;
			mineCnt--;
		}
		else continue;
	} while (mineCnt > 0);
}

int gameLog() {
	int i;
	FILE* fp_w1 = fopen("easy.txt", "w");
	FILE* fp_w2 = fopen("mid.txt", "w");
	FILE* fp_w3 = fopen("hard.txt", "w");

	if (fp_w1 == NULL || fp_w2 == NULL || fp_w3 == NULL) return -1;

	for (i = 0; i < 3; i++) fprintf(fp_w1, "%d ", Lv1[i]);

	for (i = 0; i < 3; i++) fprintf(fp_w2, "%d ", Lv2[i]);

	for (i = 0; i < 3; i++) fprintf(fp_w3, "%d ", Lv3[i]);

	fclose(fp_w1); fclose(fp_w2); fclose(fp_w3);
	return 0;
}

void displayMap(struct mineboard(*m)[MAX], int gamelevel) { 
	gotoxy(0, 0);
	for (int i = 0; i < gamelevel; i++) {
		for (int j = 0; j < gamelevel; j++) {
			if (m[i][j].wall == 1)printf("▩");
			else {
				if (m[i][j].block == 0) {
					if (m[i][j].flag == 0) printf("■");
					else printf("¶");
				}
				else if (m[i][j].block == 1) {
					if (m[i][j].mine == 1) printf("※");
					else {
						if (m[i][j].minecount == 0) printf("□");
						else if (m[i][j].minecount == 1) printf("①");
						else if (m[i][j].minecount == 2) printf("②");
						else if (m[i][j].minecount == 3) printf("③");
						else if (m[i][j].minecount == 4) printf("④");
						else if (m[i][j].minecount == 5) printf("⑤");
						else if (m[i][j].minecount == 6) printf("⑥");
						else if (m[i][j].minecount == 7) printf("⑦");
						else if (m[i][j].minecount == 8) printf("⑧");
					}
				}
			}
		}
		printf("\n");
	}
}

int resultFunc(struct mineboard(*m)[MAX], int gamelevel) {
	int count = 0;
	int i, j;
	int allMine = 0;
	if (gamelevel == 15) allMine = 20;
	else if (gamelevel == 20) allMine = 50;
	else if (gamelevel == 25) allMine = 109;

	for (i = 0; i < gamelevel; i++) {
		for (j = 0; j < gamelevel; j++) {
			if (m[i][j].wall != 1 && m[i][j].block == 0)
				count++;
		}
	}
	if (allMine == count) {
		system("cls");
		displayMap(m, gamelevel);
		gotoxy(gamelevel * 2 + 5, 6);
		printf("게임 성공!");
		gotoxy(0, gamelevel + 5);
		return 1;
	}
	return 0;
}

int speedUnlock(struct mineboard(*m)[MAX], int tmpX, int tmpY) { //이름, 함수 내부 수정
	int i, j;
	int result = 1;
	int count = 0; 

	for (i = tmpX - 1; i < tmpX + 2; i++) {
		for (j = tmpY - 1; j < tmpY + 2; j++) {
			if (m[i][j].flag == 1) count++;
		}
	}
	if (m[tmpX][tmpY].minecount == count) return result;
	else if (count == 0) return result *= 0;

	return -1;
}

int gameStart(struct mineboard(*m)[MAX], int gamelevel) { //매개변수수정
	int mineCnt;
	if (gamelevel == 15) mineCnt = 20;
	else if (gamelevel == 20) mineCnt = 50;
	else if (gamelevel == 25) mineCnt = 109;
	double duration;
	struct Point player;
	char ch;
	int i, j;
	time_t start, end;

	time(&start);
	player.x = 2;
	player.y = 1;
	displayMap(m, gamelevel);
	printRetMine(gamelevel, &mineCnt);

	gotoxy(player.x, player.y);

	while (1) {
		if (_kbhit()) {
			ch = _getch();
			switch (ch) {
			case LEFT:
				if (player.x > 2) gotoxy(player.x -= 2, player.y);
				break;
			case RIGHT:
				if (player.x < (gamelevel - 2) * 2) gotoxy(player.x += 2, player.y);
				break;
			case UP:
				if (player.y > 1) gotoxy(player.x, player.y -= 1);
				break;
			case DOWN:
				if (player.y < gamelevel - 2) gotoxy(player.x, player.y += 1);
				break;
			}

			if ((ch == 'f' || ch == 'F') && (m[player.y][player.x / 2].block == 0)) {

				if (m[player.y][player.x / 2].flag == 0) {
					m[player.y][player.x / 2].flag = 1;
					--mineCnt;
					displayMap(m, gamelevel);
					printRetMine(gamelevel, &mineCnt);
				}
				else {
					m[player.y][player.x / 2].flag = 0;
					++mineCnt;
					displayMap(m, gamelevel);
					printRetMine(gamelevel, &mineCnt);
				}
			}

			else if (ch == SPACEBAR) {

				if (m[player.y][player.x / 2].mine == 1) {
					for (i = 0; i < gamelevel; i++) {
						for (j = 0; j < gamelevel; j++) {
							if (m[i][j].wall != 1) m[i][j].block = 1;
						}
					}
					system("cls");
					displayMap(m, gamelevel);
					gotoxy(gamelevel * 2 + 5, 6);
					printf("게임 실패");
					gotoxy(0, gamelevel + 3);
					system("pause");
					return -1; //수정
				}

				else {
					mineRecursive(m, player.y, player.x / 2, &mineCnt);
					displayMap(m, gamelevel);
					printRetMine(gamelevel, &mineCnt);
					if (resultFunc(m, gamelevel) == 1) {
						time(&end);
						duration = difftime(end, start);
						gotoxy(gamelevel * 2 + 5, 4);
						printf("게임 기록 : %d초", (int)duration);
						gotoxy(0, gamelevel + 3);
						system("pause");
						return (int)duration;
					}
				}
			}
			else if ((m[player.y][player.x / 2].block == 1) && (ch == 'd' || ch == 'D')) {
				if (speedUnlock(m, player.y, player.x / 2) == 1) {

					for (int i = player.y - 1; i < player.y + 2; i++) {
						for (int j = player.x / 2 - 1; j < player.x / 2 + 2; j++) {
							if (m[i][j].flag == 0 && m[i][j].block == 0) { //수정

								if (m[i][j].mine == 1) { //깃발 잘못 세운 경우
									for (i = 0; i < gamelevel; i++) {
										for (j = 0; j < gamelevel; j++) {
											if (m[i][j].wall != 1) m[i][j].block = 1;
										}
									}
									system("cls");
									displayMap(m, gamelevel);
									gotoxy(gamelevel * 2 + 5, 6);
									printf("게임 실패");
									gotoxy(0, gamelevel + 3);
									system("pause");
									return -1; //수정
								}
								else {
									mineRecursive(m, i, j, &mineCnt);
									displayMap(m, gamelevel);
									if (resultFunc(m, gamelevel) == 1) {
										time(&end);
										duration = difftime(end, start);
										gotoxy(gamelevel * 2 + 5, 4);
										printf("게임 기록 : %d초", (int)duration);
										gotoxy(0, gamelevel + 3);
										system("pause");
										return (int)duration;
									}
								}
							}
						}
					}
				}
				else if (speedUnlock(m, player.y, player.x / 2) == -1); //추가
				else {
					for (i = 0; i < gamelevel; i++) {
						for (j = 0; j < gamelevel; j++) {
							if (m[i][j].wall != 1) m[i][j].block = 1;
						}
					}
					system("cls");
					displayMap(m, gamelevel);
					gotoxy(gamelevel * 2 + 5, 6);
					printf("게임 실패");
					gotoxy(0, gamelevel + 3);
					system("pause");
					return -1; //수정
				}
			}
		}
	}
}

void rank() { //함수 내부 수정
	int i;
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("");
	puts("");
	puts("       ※ 랭킹 TOP3 ※       ");
	puts("");
	puts("");
	puts("");
	puts("         ▼ 초급 ▼         ");
	puts("");
	for (i = 0; i < 3; i++) {
		if (Lv1[i] == '\0') printf("          ");
		else printf("   %3d    ", Lv1[i]);
	}
	puts("");
	puts("");
	puts("");
	puts("         ▼ 중급 ▼         ");
	puts("");
	for (i = 0; i < 3; i++) {
		if (Lv2[i] == '\0') printf("          ");
		else printf("   %3d    ", Lv2[i]);
	}
	puts("");
	puts("");
	puts("");
	puts("         ▼ 고급 ▼          ");
	puts("");
	for (i = 0; i < 3; i++) {
		if (Lv3[i] == '\0') printf("          ");
		else printf("   %3d    ", Lv3[i]);
	}
	puts("");
	puts("");
	puts("");
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("");
}

void howtoPlay() {
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("▩                              ▩");
	puts("▩       § 게임 방법 §        ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩     ←↑↓→ : 커서 이동     ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩       f : 깃발 세우기        ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩     SPACEBAR : 블록 제거     ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩   d : 주변블록 한번에 제거   ▩");
	puts("▩                              ▩");
	puts("▩                              ▩");
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
}

void sort_zero(int Lv[], int elapsedTime) { //함수 추가
	char c1;
	printf("기록을 저장하시겠습니까? y / n\n");
	c1 = _getch();
	if (c1 == 121) {
		if (Lv[0] == '\0' && Lv[1] == '\0') Lv[0] = elapsedTime; //맨처음 플레이
		else if (Lv[0] != '\0' && Lv[1] == '\0') { //두번째 플레이
			if (elapsedTime < Lv[0]) {
				Lv[1] = Lv[0];
				Lv[0] = elapsedTime;
			}
			else Lv[1] = elapsedTime;
		}
		else if (Lv[0] != '\0' && Lv[1] != '\0') { //세번째 플레이
			if (elapsedTime > Lv[1]) Lv[2] = elapsedTime;
			else if (elapsedTime < Lv[0]) {
				Lv[2] = Lv[1];
				Lv[1] = Lv[0];
				Lv[0] = elapsedTime;
			}
			else {
				Lv[2] = Lv[1];
				Lv[1] = elapsedTime;
			}
		}
		printf("\n게임 종료를 누를 시 기록이 저장되며 종료됩니다.\n");
		system("pause");
	}
	else if (c1 == 'n') {
		printf("\n기록을 저장하지 않습니다.\n");
		system("pause");
	}
}

void sort(int Lv[], int elapsedTime) { //함수 추가
	char c1;
	printf("기록을 저장하시겠습니까? y / n\n");
	c1 = _getch();
	if (c1 == 121) {
		if (elapsedTime > Lv[1]) {
			Lv[2] = elapsedTime;
		} 
		else if (elapsedTime < Lv[0]) {
			Lv[2] = Lv[1];
			Lv[1] = Lv[0];
			Lv[0] = elapsedTime;
		}
		else {
			Lv[2] = Lv[1];
			Lv[1] = elapsedTime;
		}
		printf("\n게임 종료를 누를 시 기록이 저장되며 종료됩니다.\n");
		system("pause");
	}

	else if (c1 == 'n') {
		printf("\n기록을 저장하지 않습니다.\n");
		system("pause");
	}
}

int main() { //매개변수 수정
	int i, select, elapsedTime;
	int gamelevel = 1;
	
	FILE* fp_r1 = fopen("easy.txt", "r");
	FILE* fp_r2 = fopen("mid.txt", "r");
	FILE* fp_r3 = fopen("hard.txt", "r");

	if (fp_r1 == NULL) {
		for (i = 0; i < 3; i++) Lv1[i] = '\0';  //수정
	}
	else {
		for (i = 0; i < 3; i++) fscanf(fp_r1, "%d", &Lv1[i]);
		fclose(fp_r1);
	}

	if (fp_r2 == NULL) {
		for (i = 0; i < 3; i++) Lv2[i] = '\0'; //수정
	}
	else {
		for (i = 0; i < 3; i++) fscanf(fp_r2, "%d", &Lv2[i]);
		fclose(fp_r2);
	}

	if (fp_r3 == NULL) {
		for (i = 0; i < 3; i++) Lv3[i] = '\0'; //수정
	}
	else {
		for (i = 0; i < 3; i++) fscanf(fp_r3, "%d", &Lv3[i]);
		fclose(fp_r3);
	}

	while (1) {
		system("cls");
		mainMenu();
		fflush(stdin); scanf("%d", &select);
		system("cls");

		switch (select) {
		case 1:
			gamelevel = levelSelect();

			switch (gamelevel) {
			case 15:
				makeMap(m, gamelevel);
				system("cls");
				elapsedTime = gameStart(m, gamelevel); //수정
				if (elapsedTime != -1) { //수정
					if (Lv1[2] == '\0') {
						sort_zero(Lv1, elapsedTime);
						break;
					}
					else if (Lv1[2] != '\0' && elapsedTime < Lv1[2]) {
						sort(Lv1, elapsedTime);
						break;
					}
					else if (Lv1[2] != '\0' && elapsedTime > Lv1[2]) {
						break;
					}
				}
				break;

			case 20:
				makeMap(m, gamelevel);
				system("cls");
				elapsedTime = gameStart(m, gamelevel); //수정
				if (elapsedTime != -1) { //수정
					if (Lv2[2] == '\0') {
						sort_zero(Lv2, elapsedTime);
						break;
					}
					else if (Lv2[2] != '\0' && elapsedTime < Lv2[2]) {
						sort(Lv2, elapsedTime);
						break;
					}
					else if (Lv2[2] != '\0' && elapsedTime > Lv2[2]) {
						break;
					}
				}
				break;

			case 25:
				makeMap(m, gamelevel);
				system("cls");
				elapsedTime = gameStart(m, gamelevel); //수정
				if (elapsedTime != -1) { //수정
					if (Lv3[2] == '\0') {
						sort_zero(Lv3, elapsedTime);
						break;
					}
					else if (Lv3[2] != '\0' && elapsedTime < Lv3[2]) {
						sort(Lv3, elapsedTime);
						break;
					}
					else if (Lv3[2] != '\0' && elapsedTime > Lv3[2]) {
						break;
					}
				}
				break;
			}
			break;

		case 2:
			rank();
			system("pause");
			break;

		case 3:
			howtoPlay();
			system("pause");
			break;

		case 4:
			gameLog();
			return 0;

		default:
			break;
		}
	}
}