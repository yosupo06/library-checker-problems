#include <iostream>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = 1;
	while ((n << 1) <= N_MAX) n <<= 1;
	n -= seed;
	
	printf("%s\n", gen.lower_string(n).c_str());
	return 0;
}
