#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = N_MAX;
	
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", i > 10 || !i ? gen.uniform<int>(1, MOD - 1) : 0);
	}
	puts("");
	return 0;
}
