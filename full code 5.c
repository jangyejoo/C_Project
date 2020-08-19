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
void randMine(struct mineboard(*m)[MAX], int gamelevel); //수정
int gameLog();
int gameStart(struct mineboard(*m)[MAX], int gamelevel,int *retMine); //수정
void mainMenu();
void mineRecursive(struct mineboard(*m)[MAX], int tmpX, int tmpY, int* retMine);
void rank();
void displayMap(struct mineboard(*m)[MAX], int gamelevel); //수정
int resultFunc(struct mineboard(*m)[MAX], int gamelevel); //수정
void howtoPlay();
int speedBreaker(struct mineboard(*m)[MAX], int tmpX, int tmpY);
void printRetMine(int gamelevel, int* retMine); //추가, 수정

void printRetMine(int gamelevel,int *retMine) { //남은 지뢰 개수를 출력
	gotoxy(gamelevel * 2 + 5, 3);           
	printf("남은 지뢰 개수 : %3d", *retMine); //수정
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

void randMine(struct mineboard(*m)[MAX], int gamelevel) { //지뢰 개수 수정
	int mineCnt = 0;
	if (gamelevel == 15) mineCnt = 20;
	else if (gamelevel == 20) mineCnt = 50;
	else if (gamelevel == 25) mineCnt = 109;
	srand((unsigned int)time(NULL)); //오류 수정
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

void displayMap(struct mineboard(*m)[MAX], int gamelevel) { // 남은 지뢰 개수 표시 부분 삭제
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
	int allMine=0;
	if (gamelevel == 15) allMine = 20;
	else if (gamelevel == 20) allMine = 50;
	else if (gamelevel == 25) allMine = 109; //지뢰 개수 수정
	 
	for (i = 0; i < gamelevel; i++) {
		for (j = 0; j < gamelevel; j++) {
			if (m[i][j].wall != 1 && m[i][j].block == 0)
				count++;
		}
	}
	if (allMine == count) {
		system("cls"); //남은 지뢰 개수를 보이지 않기 위해 콘솔창 초기화
		displayMap(m, gamelevel); 
		gotoxy(gamelevel * 2 + 5, 6);
		printf("게임 성공!");
		gotoxy(0, gamelevel + 5);
		return 1;
	}
	return 0;
}

int speedBreaker(struct mineboard(*m)[MAX], int tmpX, int tmpY) {  
	int i, j;
	int result = 1;
	bool exitOuterLoop = false;

	for (i = tmpX - 1; i < tmpX + 2; i++) {
		for (j = tmpY - 1; j < tmpY + 2; j++) {
			if (m[i][j].mine == 1 && m[i][j].block == 0) {
				if (m[i][j].flag == 0)
					result *= 0;
			}
			else if (m[i][j].mine == 0) {
				if (m[i][j].flag == 1)
					result *= 0;
			}
			else continue;
		}
	}

	return result;

}

int gameStart(struct mineboard(*m)[MAX], int gamelevel,int *retMine) { //매개변수수정
	int mineCnt;
	if (gamelevel == 15) mineCnt = 20;
	else if (gamelevel == 20) mineCnt = 50;
	else if (gamelevel == 25) mineCnt = 109; //지뢰 개수 수정
	double duration;
	struct Point player;
	char ch;
	int i, j;
	time_t start, end;

	time(&start);
	player.x = 2;
	player.y = 1;
	displayMap(m, gamelevel);
	printRetMine(gamelevel, &mineCnt); //수정

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

			if ((ch == 'f' || ch == 'F')&&(m[player.y][player.x/2].block==0)){
		
				if (m[player.y][player.x / 2].flag == 0) {
					m[player.y][player.x / 2].flag = 1;
					--mineCnt;                                
					displayMap(m, gamelevel);
					printRetMine(gamelevel, &mineCnt);//수정
				}
				else {
					m[player.y][player.x / 2].flag = 0;
					++mineCnt;                                
					displayMap(m, gamelevel);
					printRetMine(gamelevel, &mineCnt);//수정
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
					displayMap(m, gamelevel);  //매개변수 수정
					gotoxy(gamelevel * 2 + 5, 6);
					printf("게임 실패");
					gotoxy(0, gamelevel + 3);
					system("pause");
					return 999;
				}

				else {
					mineRecursive(m, player.y, player.x / 2, &mineCnt);  
					displayMap(m, gamelevel);
					printRetMine(gamelevel, &mineCnt);//수정
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
				if (speedBreaker(m, player.y, player.x / 2) == 1) {

					for (int i = player.y - 1; i < player.y + 2; i++) {
						for (int j = player.x / 2 - 1; j < player.x / 2 + 2; j++) {
							if (m[i][j].mine == 0 && m[i][j].block == 0) {
								mineRecursive(m, i, j, &mineCnt);   
								displayMap(m, gamelevel);
								printRetMine(gamelevel, &mineCnt);//수정
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
		}
	}
}

void rank() {
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("▩                          ▩");
	puts("▩     ※ 랭킹 TOP3 ※      ▩");
	puts("▩                          ▩");
	puts("▩                          ▩");
	puts("▩          *초급*          ▩");
	puts("▩                          ▩");
	printf("▩   %3d     %3d     %3d    ▩\n", Lv1[0], Lv1[1], Lv1[2]);
	puts("▩                          ▩");
	puts("▩          *중급*          ▩");
	puts("▩                          ▩");
	printf("▩   %3d     %3d     %3d    ▩\n", Lv2[0], Lv2[1], Lv2[2]);
	puts("▩                          ▩");
	puts("▩          *고급*          ▩");
	puts("▩                          ▩");
	printf("▩   %3d     %3d     %3d    ▩\n", Lv3[0], Lv3[1], Lv3[2]);
	puts("▩                          ▩");
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

int main(int mineCnt) { //매개변수 추가
	int i, select, elapsedTime;
	int gamelevel = 1;
	char c1;
	FILE* fp_r1 = fopen("easy.txt", "r");
	FILE* fp_r2 = fopen("mid.txt", "r");
	FILE* fp_r3 = fopen("hard.txt", "r");

	if (fp_r1 == NULL) {
		for (i = 0; i < 3; i++) Lv1[i] = 999;
	}
	else {
		for (i = 0; i < 3; i++) fscanf(fp_r1, "%d", &Lv1[i]);
		fclose(fp_r1);
	}

	if (fp_r2 == NULL) {
		for (i = 0; i < 3; i++) Lv2[i] = 999;
	}
	else {
		for (i = 0; i < 3; i++) fscanf(fp_r2, "%d", &Lv2[i]);
		fclose(fp_r2);
	}

	if (fp_r3 == NULL) {
		for (i = 0; i < 3; i++) Lv3[i] = 999;
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
				elapsedTime = gameStart(m, gamelevel,&mineCnt); //수정
				if (elapsedTime < Lv1[2]) {
					printf("기록을 저장하시겠습니까? y / n\n");
					c1 = _getch();
					if (c1 == 121) {
						if (elapsedTime > Lv1[1]) {
							Lv1[2] = elapsedTime;
						}
						else if (elapsedTime < Lv1[0]) {
							Lv1[2] = Lv1[1];
							Lv1[1] = Lv1[0];
							Lv1[0] = elapsedTime;
						}
						else {
							Lv1[2] = Lv1[1];
							Lv1[1] = elapsedTime;
						}
						printf("\n게임 종료를 누를 시 기록이 저장되며 종료됩니다.\n");
						system("pause");
						break;
					}
					else if (c1 == 'n') {
						printf("\n");
						printf("기록을 저장하지 않습니다.\n");
						system("pause");
						break;
					}
				}
				break;

			case 20:
				makeMap(m, gamelevel);
				system("cls");
				elapsedTime = gameStart(m, gamelevel, &mineCnt); //수정
				if (elapsedTime < Lv2[2]) {
					printf("기록을 저장하시겠습니까? y / n\n");
					c1 = _getch();
					if (c1 == 121) {
						if (elapsedTime > Lv2[1]) {
							Lv2[2] = elapsedTime;
						}
						else if (elapsedTime < Lv2[0]) {
							Lv2[2] = Lv2[1];
							Lv2[1] = Lv2[0];
							Lv2[0] = elapsedTime;
						}
						else {
							Lv2[2] = Lv2[1];
							Lv2[1] = elapsedTime;
						}
						printf("\n게임 종료를 누를 시 기록이 저장되며 종료됩니다.\n");
						system("pause");
						break;
					}
					else if (c1 == 'n') {
						printf("\n");
						printf("기록을 저장하지 않습니다.\n");
						system("pause");
						break;
					}
				}
				break;

			case 25:
				makeMap(m, gamelevel);
				system("cls");
				elapsedTime = gameStart(m, gamelevel , &mineCnt); //수정
				if (elapsedTime < Lv3[2]) {
					printf("기록을 저장하시겠습니까? y / n\n");
					c1 = _getch();
					if (c1 == 121) {
						if (elapsedTime > Lv3[1]) {
							Lv3[2] = elapsedTime;
						}
						else if (elapsedTime < Lv3[0]) {
							Lv3[2] = Lv3[1];
							Lv3[1] = Lv3[0];
							Lv3[0] = elapsedTime;
						}
						else {
							Lv3[2] = Lv3[1];
							Lv3[1] = elapsedTime;
						}
						printf("\n게임 종료를 누를 시 기록이 저장되며 종료됩니다.\n");
						system("pause");
						break;
					}
					else if (c1 == 'n') {
						printf("\n");
						printf("기록을 저장하지 않습니다.\n");
						system("pause");
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