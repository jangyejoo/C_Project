void randMine(struct mineboard(*m)[MAX], int gamelevel) {
	int mineCnt=0;
	if (gamelevel == 15) mineCnt = 10;
	else if (gamelevel == 20) mineCnt = 50;
	else if (gamelevel == 25) mineCnt = 80;
	do {
		int i, j;
		i = randx(gamelevel);
		j = randx(gamelevel);
		if (m[i][j].mine == 0) {
			m[i][j].mine = 1;
			mineCnt--;
		}
		else continue;
	} while (mineCnt>0);
}