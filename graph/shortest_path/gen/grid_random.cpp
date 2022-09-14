#include <vector>
#include "random.h"
#include "../params.h"
#include "../fastio.h"

#define INDEX(i, j) ((i) * len + (j))
int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int len;
	for (len = 0; len * len * 4 <= M_MAX; len += 2);
	len -= 2;
	struct Hen {
		int from;
		int to;
		int cost;
	};
	std::vector<Hen> hens;
	
	auto rnd = [&] () { return gen.uniform((int) C_MIN, (int) C_MAX); };
	for (int i = 0; i < len; i++) {
		for (int j = 0; j < len; j++) {
			if (j + 1 < len) hens.push_back({INDEX(i, j), INDEX(i, j + 1), rnd()});
			if (i + 1 < len) hens.push_back({INDEX(i, j), INDEX(i + 1, j), rnd()});
			if (j) hens.push_back({INDEX(i, j), INDEX(i, j - 1), rnd()});
			if (i) hens.push_back({INDEX(i, j), INDEX(i - 1, j), rnd()});
		}
	}
	gen.shuffle(hens.begin(), hens.end());
	
	int s = gen.uniform(0, len * len - 1);
	int t;
	do t = gen.uniform(0, len * len - 1); while (s == t);
	
	println(len * len, ' ', (int) hens.size(), ' ', s, ' ', t);
	for (auto i : hens) println(i.from, ' ', i.to, ' ', i.cost);
	return 0;
}
