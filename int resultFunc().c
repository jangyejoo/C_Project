int resultFunc(struct mineboard(*m)[MAX_Y], int gamelevel, int * retMine){
	int count = 0;
	int i, j;
	int allMine;
	if (gamelevel == 15) allMine = 20;
	else if (gamelevel == 20) allMine = 50;
	else if (gamelevel == 25) allMine = 80;

	for (i = 0; i < gamelevel; i++) {
		for (j = 0; j < gamelevel; j++) {
			if (m[i][j].wall != 1 && m[i][j].block == 0)
				count++;
		}
	}
	if (allMine == count) {
		displayMap(m, gamelevel, &retlMine);
		gotoxy(gamelevel * 2 + 5, 6);
		printf("���� ����!");
		gotoxy(0, gamelevel + 5);
		return 1;
	}
	return 0;
}