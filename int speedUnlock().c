int speedUnlock(struct mineboard(*m)[MAX], int tmpX, int tmpY) {
	int i, j;
	int result = 1;
	int count = 0;

	for (i = tmpX - 1; i < tmpX + 2; i++) {
		for (j = tmpY - 1; j < tmpY + 2; j++) {
			if (m[i][j].flag == 1) count++;
		}
	}
	if ((m[tmpX][tmpY].minecount != count)||(count==0)){
		result *= 0;
	}

	return result;
}