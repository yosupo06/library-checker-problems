#include <stdio.h>
#include "../params.h"
#include "random.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	int n = N_MAX;
	printf("%d\n", n);
	printf("0 1");
	for (int i = 2; i < n; i++) {
		printf(" %d", gen.uniform(0, int(MOD - 1)));
	}
	puts("");
	return 0;
}
