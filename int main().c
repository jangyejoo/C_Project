#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
int Lv1[3], Lv2[3], Lv3[3]; //기록변수 배열

int main(int mineCnt) {
	struct mineboard m[MAX_X][MAX_Y];
	int i, select, elapsedTime;
	char c1;
	int gamelevel = 1;

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
		case 1: //겜시작
			gamelevel = levelSelect();
				
			switch (gamelevel) {  //기록 저장 묻기-레벨별로
			case 15:
				makeMap(m, gamelevel);
				system("cls");
				elapsedTime = gameStart(m, gamelevel,&mineCnt);
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
						break;
					}
					else if (c1 == 'n') break;
				}
				break;

			case 20:
				makeMap(m, gamelevel);
				system("cls");
				elapsedTime = gameStart(m, gamelevel, &mineCnt);
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
						break;
					}
					else if (c1 == 'n') break;
				}
				break;
			case 25:
				makeMap(m, gamelevel);
				system("cls");
				elapsedTime = gameStart(m, gamelevel, &mineCnt);
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
						break;
					}
					else if (c1 == 'n') break;
				}
				break;
			} //기록 저장 묻기 끝
			break;

		case 2: //순위 보기
			rank(); 
			system("pause");
			break;

		case 3:
			howtoPlay();
			system("pause");
			break;
		case 4: //겜종료, 기록 저장
			gameLog();
			return 0;
		default:
			break;
		}
	}
}