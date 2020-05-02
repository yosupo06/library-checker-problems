#include <stdio.h>
#include "../params.h"
#include "random.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	int n = 500000;
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", i < 2 ? 0 : gen.uniform(0, 998244352));
	}
	puts("");
	return 0;
}
