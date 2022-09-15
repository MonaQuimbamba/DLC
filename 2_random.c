#include <stdio.h>
#include <stdlib.h>

int main () {

        srand(time(NULL));
	int val;
	val = rand() %50;
	printf("%d\n",val);
	return 0;
}
