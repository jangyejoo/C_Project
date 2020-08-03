int levelSelect() {
	int select;
	while (1) {
		system("cls");
		levelSelectMenu();
		scanf("%d", &select);
		if (select == 1) return 15;
		else if (select == 2) return 20;
		else if (select == 3) return 25;
		else continue;
	}
}