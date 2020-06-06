#include <iostream>
#include "random.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = 1;
	while ((n << 1) <= 500000) n <<= 1;
	n -= seed;
	
	printf("%s\n", gen.lower_string(n).c_str());
	return 0;
}
