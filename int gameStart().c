int gameStart(struct mineboard (*m) [MAX_Y],int gamelevel) {
	int mineCnt;
	if (gamelevel == 15) mineCnt = 10;
	else if (gamelevel == 20) mineCnt = 50;
	else if (gamelevel == 25) mineCnt = 80;
	double duration;
	Point player;
	char ch;
	int i, j;
	time_t start, end;

	time(&start);
	player.x = 2;
	player.y = 1;
	displayMap(m,gamelevel);
	gotoxy(player.x, player.y);

	while (1) {
		if (_kbhit()) {
			ch = _getch();
			switch (ch) {
			case LEFT:
				if (player.x > 2) gotoxy(player.x -= 2, player.y);
				break;
			case RIGHT:
				if (player.x < (gamelevel-2) * 2) gotoxy(player.x += 2, player.y);
				break;
			case UP:
				if (player.y > 1) gotoxy(player.x, player.y -= 1);
				break;
			case DOWN:
				if (player.y < gamelevel - 2) gotoxy(player.x, player.y += 1);
				break;
			}

			if (ch == 'f' || ch == 'F') {
				if (m[player.y][player.x/2].flag == 0) {
					m[player.y][player.x/2].flag = 1;
					displayMap(m,gamelevel);
				}
				else {
					m[player.y][player.x/2].flag = 0;
					displayMap(m,gamelevel);
				}
			}

			else if (ch == SPACEBAR) {

				if (m[player.y][player.x/2].mine == 1) {
					for (i = 0; i < gamelevel; i++) {
						for (j = 0; j < gamelevel; j++) {
							if (m[i][j].wall != 1) m[i][j].block = 1;
						}
					}
					displayMap(m, gamelevel);
					gotoxy(gamelevel * 2 + 5, 6);
					printf("게임 실패");
					gotoxy(0, gamelevel + 3);
					system("pause");
					return 999;
				}

				else {
					mineRecursive(m, player.y, player.x/2);
					displayMap(m, gamelevel);
					if (resultFunc(m, gamelevel, mineCnt) == 1) {
						time(&end);
						duration = difftime(end, start);
						gotoxy(gamelevel * 2 + 5, 4);
						printf("게임 기록 : %d초", (int)duration);
						gotoxy(0, gamelevel + 3);
						system("pause");
						return (int)duration;
					}
				}
			}
		}
	}
}