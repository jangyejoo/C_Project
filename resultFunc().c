int resultFunc(struct mineboard(*m)[MAX_Y], int gamelevel, int allMine){
	int count = 0;
	int i, j;
	if (gamelevel == 15) allMine = 10;
	else if (gamelevel == 20) allMine = 50;
	else if (gamelevel == 25) allMine = 80;
	for (i = 0; i < gamelevel; i++) {
		for (j = 0; j < gamelevel; j++) {
			if (m[i][j].wall != 1 && m[i][j].block == 0)
				count++;
		}
	}
	if (allMine == count) {
		displayMap(m, gamelevel);
		gotoxy(gamelevel * 2, 6);
		printf("게임 성공!");
		gotoxy(gamelevel * 2, gamelevel + 1);
		return 1;
	}
	return 0;
}