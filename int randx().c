#include <stdlib.h>
#include <time.h>

int randx(int gamelevel) {
	srand(time(NULL));
	return (rand() % (gamelevel - 2) + 1);
}