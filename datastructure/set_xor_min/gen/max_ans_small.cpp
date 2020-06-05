#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int Q = MAX_Q;
	printf("%d\n", Q);
	std::vector<int> all;
	for (int i = 0; i < Q; i++) {
		if (i < Q / 2) {
			int x = gen.uniform(0, (1 << 30) - 1);
			all.push_back(x);
			printf("0 %d\n", x);
		} else printf("2 %d\n", all[gen.uniform(0, (int) all.size() - 1)] ^ gen.uniform(0, 7));
	}
	
	return 0;
}
