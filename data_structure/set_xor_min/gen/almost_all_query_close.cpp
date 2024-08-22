#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int Q = MAX_Q;
	printf("%d\n", Q);
	int x = gen.uniform(0, (1 << 30) - 1);
	for (int i = 0; i < Q; i++) {
		if (i) printf("2 %d\n", x ^ gen.uniform(0, 7));
		else printf("0 %d\n", x);
	}
	
	return 0;
}
