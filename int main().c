#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
int Lv1[3], Lv2[3], Lv3[3]; //기록변수 배열

int main() {
	int i, select, elapsedTime;
	int gamelevel = 1;

	FILE* fp_r1 = fopen("easy.txt", "r");
	FILE* fp_r2 = fopen("mid.txt", "r");
	FILE* fp_r3 = fopen("hard.txt", "r");

	if (fp_r1 == NULL) {
		for (i = 0; i < 3; i++) Lv1[i] = '\0';
	}
	else {
		for (i = 0; i < 3; i++) fscanf(fp_r1, "%d", &Lv1[i]);
		fclose(fp_r1);
	}

	if (fp_r2 == NULL) {
		for (i = 0; i < 3; i++) Lv2[i] = '\0';
	}
	else {
		for (i = 0; i < 3; i++) fscanf(fp_r2, "%d", &Lv2[i]);
		fclose(fp_r2);
	}

	if (fp_r3 == NULL) {
		for (i = 0; i < 3; i++) Lv3[i] = '\0';
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
				elapsedTime = gameStart(m, gamelevel);
				if (elapsedTime != -1) {
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
				elapsedTime = gameStart(m, gamelevel);
				if (elapsedTime != -1) {
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
				elapsedTime = gameStart(m, gamelevel);
				if (elapsedTime != -1) {
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