void displayMap(struct mineboard(*m)[MAX], int gamelevel, int* retMine) {
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
	gotoxy(gamelevel * 2 + 5, 3);
	printf("남은 지뢰 개수 : %2d", *retMine);
}