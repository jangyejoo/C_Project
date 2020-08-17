int speedBreaker(struct mineboard(*m)[MAX], int tmpX, int tmpY) {
	int i, j;
	int result=1;
	bool exitOuterLoop = false;

	for (i = tmpX - 1; i < tmpX + 2; i++) {
		for (j = tmpY - 1; j < tmpY + 2; j++) {
			if (m[i][j].mine == 1 && m[i][j].block == 0) {
				if(m[i][j].flag==0)
					result*= 0;
			}
			else if (m[i][j].mine==0) {
				if (m[i][j].flag==1)
					result*=0;
			}
			else continue;
		}
	}

	return result;
	
}