void sort_zero(int Lv[], int elapsedTime) {
	char c1;
	while (1) {
		printf("기록을 저장하시겠습니까? y / n\n");
		c1 = _getch();
		if (c1 == 121) {
			if (Lv[0] == '\0' && Lv[1] == '\0') Lv[0] = elapsedTime; //맨처음 플레이
			else if (Lv[0] != '\0' && Lv[1] == '\0') { //두번째 플레이
				if (elapsedTime < Lv[0]) {
					Lv[1] = Lv[0];
					Lv[0] = elapsedTime;
				}
				else Lv[1] = elapsedTime;
			}
			else if (Lv[0] != '\0' && Lv[1] != '\0') { //세번째 플레이
				if (elapsedTime > Lv[1]) Lv[2] = elapsedTime;
				else if (elapsedTime < Lv[0]) {
					Lv[2] = Lv[1];
					Lv[1] = Lv[0];
					Lv[0] = elapsedTime;
				}
				else {
					Lv[2] = Lv[1];
					Lv[1] = elapsedTime;
				}
			}
			printf("\n게임 종료를 누를 시 기록이 저장되며 종료됩니다.\n");
			system("pause");
			break;
		}
		else if (c1 == 'n') {
			printf("\n기록을 저장하지 않습니다.\n");
			system("pause");
			break;
		}
		else continue;
	}
}