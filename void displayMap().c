void displayMap(struct mineboard(*m)[MAX], int gamelevel) {
	gotoxy(0, 0);
	for (int i = 0; i < gamelevel; i++) {
		for (int j = 0; j < gamelevel; j++) {
			if (m[i][j].wall == 1)printf("��");
			else {
				if (m[i][j].block == 0) {
					if (m[i][j].flag == 0) printf("��");
					else printf("��");
				}
				else if (m[i][j].block == 1) {
					if (m[i][j].mine == 1) printf("��");
					else {
						if (m[i][j].minecount == 0) printf("��");
						else if (m[i][j].minecount == 1) printf("��");
						else if (m[i][j].minecount == 2) printf("��");
						else if (m[i][j].minecount == 3) printf("��");
						else if (m[i][j].minecount == 4) printf("��");
						else if (m[i][j].minecount == 5) printf("��");
						else if (m[i][j].minecount == 6) printf("��");
						else if (m[i][j].minecount == 7) printf("��");
						else if (m[i][j].minecount == 8) printf("��");
					}
				}
			}
		}
		printf("\n");
	}
}