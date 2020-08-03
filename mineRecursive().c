void mineRecursive(struct mineboard(*m)[MAX_Y], int tmpX, int tmpY){
	int i, j;
	if (m[tmpX][tmpY].block == 1) return;
	else if (m[tmpX][tmpY].wall == 1) return;
	else if (m[tmpX][tmpY].minecount != 0) {
		m[tmpX][tmpY].block = 1;
		return;
	}
	else if (m[tmpX][tmpY].minecount == 0) {
		for (i = tmpX-2; i < tmpX + 4; i++) {
			for (j = tmpY - 1; j < tmpY + 2; j++) {
				mineRecursive(m, i, j);
			}
		}
	}
}