#include <stdio.h>
#include "../params.h"
#include "random.h"

int main() {
	int n = N_MAX;
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", !i);
	}
	puts("");
	return 0;
}
