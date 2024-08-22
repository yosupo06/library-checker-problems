#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int Q = gen.uniform(1, (int) MAX_Q);
	printf("%d\n", Q);
	std::vector<int> in;
	std::set<int> inset;
	for (int i = 0; i < Q; i++) {
		int t = gen.uniform(0, in.size() ? 2 : 1);
		int x;
		if (t == 0) {
			if (!gen.uniform(0, 5) && in.size()) { // rare, try to insert existing element
				x = in[gen.uniform(0, (int) in.size() - 1)];
			} else { // probably inserting a new one
				x = gen.uniform(0, (1 << 30) - 1);
				if (inset.insert(x).second) in.push_back(x);
			}
		} else if (t == 1) {
			if (gen.uniform_bool() && in.size()) { // remove existing element
				int index = gen.uniform(0, (int) in.size() - 1);
				std::swap(in[index], in.back());
				x = in.back();
				in.pop_back();
				inset.erase(x);
			} else do x = gen.uniform(0, (1 << 30) - 1); while (inset.count(x)); // remove nothing
		} else x = gen.uniform(0, (1 << 30) - 1); // t == 2, query
		printf("%d %d\n", t, x);
	}
	
	return 0;
}
