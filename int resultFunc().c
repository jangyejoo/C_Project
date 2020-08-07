int resultFunc(struct mineboard(*m)[MAX_Y], int gamelevel, int allMine){
	int count = 0;
	int i, j;
	
	for (i = 0; i < gamelevel; i++) {
		for (j = 0; j < gamelevel; j++) {
			if (m[i][j].wall != 1 && m[i][j].block == 0)
				count++;
		}
	}
	if (allMine == count) {
		displayMap(m, gamelevel);
		gotoxy(gamelevel * 2 + 5, 6);
		printf("게임 성공!");
		gotoxy(0, gamelevel + 5);
		return 1;
	}
	return 0;
}