void sort(int Lv[], int elapsedTime) { //�Լ� �߰�
	char c1;
	printf("����� �����Ͻðڽ��ϱ�? y / n\n");
	c1 = _getch();
	if (c1 == 121) {
		if (elapsedTime > Lv[1]) {
			Lv[2] = elapsedTime;
		}
		else if (elapsedTime < Lv[0]) {
			Lv[2] = Lv[1];
			Lv[1] = Lv[0];
			Lv[0] = elapsedTime;
		}
		else {
			Lv[2] = Lv[1];
			Lv[1] = elapsedTime;
		}
		printf("\n���� ���Ḧ ���� �� ����� ����Ǹ� ����˴ϴ�.\n");
		system("pause");
	}
	else if (c1 == 'n') {
		printf("\n����� �������� �ʽ��ϴ�.\n");
		system("pause");
	}
}