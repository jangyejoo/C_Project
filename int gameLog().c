//�ʱ� ��� �迭 int Lv1[3]={10,20,30}, �߱� ��� �迭 int Lv2[3], ��� ��� �迭 int Lv3[3]

int gameLog() { //size�� �迭 ũ��
	int i;
	FILE* fp_w1 = fopen("easy.txt", "w");
	FILE* fp_w2 = fopen("mid.txt", "w");
	FILE* fp_w3 = fopen("hard.txt", "w");

	if (fp_w1 == NULL || fp_w2 == NULL || fp_w3 == NULL) return -1;

	for (i = 0; i < size; i++) fprintf(fp_w1, "%d ", Lv1[i]);
	
	for (i = 0; i < size; i++) fprintf(fp_w2, "%d ", Lv2[i]);
	
	for (i = 0; i < size; i++) fprintf(fp_w3, "%d ", Lv3[i]);

	fclose(fp_w1); fclose(fp_w2); fclose(fp_w3);
	return 0;
}