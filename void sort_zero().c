void sort_zero(int Lv[], int elapsedTime) {
	char c1;
	while (1) {
		printf("����� �����Ͻðڽ��ϱ�? y / n\n");
		c1 = _getch();
		if (c1 == 121) {
			if (Lv[0] == '\0' && Lv[1] == '\0') Lv[0] = elapsedTime; //��ó�� �÷���
			else if (Lv[0] != '\0' && Lv[1] == '\0') { //�ι�° �÷���
				if (elapsedTime < Lv[0]) {
					Lv[1] = Lv[0];
					Lv[0] = elapsedTime;
				}
				else Lv[1] = elapsedTime;
			}
			else if (Lv[0] != '\0' && Lv[1] != '\0') { //����° �÷���
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
			printf("\n���� ���Ḧ ���� �� ����� ����Ǹ� ����˴ϴ�.\n");
			system("pause");
			break;
		}
		else if (c1 == 'n') {
			printf("\n����� �������� �ʽ��ϴ�.\n");
			system("pause");
			break;
		}
		else continue;
	}
}