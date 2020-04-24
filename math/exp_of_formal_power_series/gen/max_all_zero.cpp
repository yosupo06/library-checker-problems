#include <stdio.h>
#include "../params.h"
#include "random.h"

int main() {
	int n = 500000;
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("0");
	}
	puts("");
	return 0;
}
