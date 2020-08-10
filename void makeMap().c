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
	randMine(m,gamelevel);
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