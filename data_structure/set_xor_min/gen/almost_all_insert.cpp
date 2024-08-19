#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int Q = MAX_Q;
	printf("%d\n", Q);
	for (int i = 0; i < Q; i++) {
		if (i + 1 < Q) printf("0 %d\n", gen.uniform(0, (1 << 30) - 1));
		else printf("2 %d\n", gen.uniform(0, (1 << 30) - 1));
	}
	
	return 0;
}
