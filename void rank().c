void rank() {
	int i;
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("");
	puts("");
	puts("       ※ 랭킹 TOP3 ※       ");
	puts("");
	puts("");
	puts("");
	puts("         ▼ 초급 ▼         ");
	puts("");
	for (i = 0; i < 3; i++) {
		if (Lv1[i] == '\0') printf("          ");
		else printf("   %3d    ", Lv1[i]);
	}
	puts("");
	puts("");
	puts("");
	puts("         ▼ 중급 ▼         ");
	puts("");
	for (i = 0; i < 3; i++) {
		if (Lv2[i] == '\0') printf("          ");
		else printf("   %3d    ", Lv2[i]);
	}
	puts("");
	puts("");
	puts("");
	puts("         ▼ 고급 ▼          ");
	puts("");
	for (i = 0; i < 3; i++) {
		if (Lv3[i] == '\0') printf("          ");
		else printf("   %3d    ", Lv3[i]);
	}
	puts("");
	puts("");
	puts("");
	puts("▩▩▩▩▩▩▩▩▩▩▩▩▩▩▩");
	puts("");
}