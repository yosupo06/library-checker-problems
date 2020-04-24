#include <stdio.h>
#include "../params.h"
#include "random.h"

int main(int argc, char **argv) {
	(void) argc;
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	int n = gen.uniform(1, 10000);
	int m = gen.uniform(1, 10000);
	printf("%d %d\n", n, m);
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("0");
	}
	puts("");
	for (int i = 0; i < m; i++) {
		if (i) printf(" ");
		printf("0");
	}
	puts("");
	return 0;
}
