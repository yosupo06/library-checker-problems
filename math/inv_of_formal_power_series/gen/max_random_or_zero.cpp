#include <stdio.h>
#include "random.h"

int main(int argc, char **argv) {
	(void) argc;
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = 500000;
	
	printf("%d\n", n);
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", i > 10 || !i ? gen.uniform(1, 998244352) : 0);
	}
	puts("");
	return 0;
}
