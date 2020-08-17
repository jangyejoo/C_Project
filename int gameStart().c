int gameStart(struct mineboard (*m) [MAX],int gamelevel) {
	int mineCnt;
	if (gamelevel == 15) mineCnt = 20;
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
	displayMap(m, gamelevel, &mineCnt);
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

			if ((ch == 'f' || ch == 'F')&&(m[player.y][player.x/2].block==0)) {
				if (m[player.y][player.x/2].flag == 0) {
					m[player.y][player.x/2].flag = 1;
					--mineCnt;
					displayMap(m, gamelevel, &mineCnt);
				}
				else {
					m[player.y][player.x/2].flag = 0;
					++mineCnt;
					displayMap(m, gamelevel, &mineCnt);
				}
			}

			else if (ch == SPACEBAR) {

				if (m[player.y][player.x/2].mine == 1) {
					for (i = 0; i < gamelevel; i++) {
						for (j = 0; j < gamelevel; j++) {
							if (m[i][j].wall != 1) m[i][j].block = 1;
						}
					}
					displayMap(m, gamelevel, &mineCnt);
					gotoxy(gamelevel * 2 + 5, 6);
					printf("게임 실패");
					gotoxy(0, gamelevel + 3);
					system("pause");
					return 999;
				}

				else {
					mineRecursive(m, player.y, player.x / 2, &mineCnt);
					displayMap(m, gamelevel, &mineCnt);
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
			else if ((m[player.y][player.x/2].block==1)&&(ch == 'd'||ch=='D')) {			
				if (speedBreaker(m, player.y, player.x / 2)==1) {
					
					for (int i = player.y - 1; i < player.y + 2; i++) {
						for (int j = player.x / 2 - 1; j < player.x / 2 + 2; j++) {
							if (m[i][j].mine==0&&m[i][j].block == 0) {
								mineRecursive(m, i, j, &mineCnt);
								displayMap(m, gamelevel, &mineCnt);
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
		}
	}
}