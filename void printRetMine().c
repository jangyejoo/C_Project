void printRetMine(int gamelevel,int *retMine) { 
	gotoxy(gamelevel * 2 + 5, 3);           
	printf("남은 지뢰 개수 : %3d", *retMine); 
}