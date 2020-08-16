void mineRecursive(struct mineboard(*m)[MAX_Y], int tmpX, int tmpY, int* retMine){
	int i, j;
	if (m[tmpX][tmpY].block == 1) return;
	else if (m[tmpX][tmpY].wall == 1) return;
	else if (m[tmpX][tmpY].minecount != 0) {
		m[tmpX][tmpY].block = 1;
		if (m[tmpX][tmpY].flag == 1) {
			m[tmpX][tmpY].flag = 0;
			++*retMine;
		}
		return;
	}
	else {
		m[tmpX][tmpY].block = 1;
		if (m[tmpX][tmpY].flag == 1) {
			m[tmpX][tmpY].flag = 0;
			++*retMine;
		}
		for (i = tmpX - 1; i < tmpX + 2; i++) {
			for (j = tmpY - 1; j < tmpY + 2; j++) {
				mineRecursive(m, i, j, retMine);
			}
		}
	}
}