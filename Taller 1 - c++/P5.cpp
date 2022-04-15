#include <stdio.h>

void fnx(int x){
	if (x) printf("%d ", x);
}

main() {
	int i, a = 1234;
	for (i = 0; i < 4; i++)
		fnx(a = a/10);
}
