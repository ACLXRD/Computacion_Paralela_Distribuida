#include <stdio.h>

main(){
	int x = 0, y = 0;
	for (x = 6; x > 0; x -= 2)
		for (y = 0; y < 2; y++)
			printf("%d ", x-y);
}
