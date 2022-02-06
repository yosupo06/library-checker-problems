#include <iostream>
#include <set>

#include "../../../common/random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	int l = gen.uniform(0, L_MAX - 1);
	int r = l;
	int m = M_MAX;

	using P = pair<int, int>;
	set<P> edges;

	int k = l / 8 * 2;
	for(int i = 0; i < k; i++) {
		edges.insert({i, i});
	}
	for(int i = 0; i < k-1; i++) {
		edges.insert({i+1, i});
	}
	for(int i = 0; i < k/2; i++) {
		edges.insert({i, k+2*i});
		edges.insert({2*k+2*i, k+2*i});
		edges.insert({2*k+2*i, 3*k+2*i});
		edges.insert({k+2*i, i});
		edges.insert({k+2*i, 2*k+2*i});
		edges.insert({3*k+2*i, 2*k+2*i});
	}
	for(int j = 0; j < k/2; j++) {
		int i = k/2-1-j;
		edges.insert({k/2+j, k+2*i+1});
		edges.insert({2*k+2*i+1, k+2*i+1});
		edges.insert({2*k+2*i+1, 3*k+2*i+1});
		edges.insert({k+2*i+1, k/2+j});
		edges.insert({k+2*i+1, 2*k+2*i+1});
		edges.insert({3*k+2*i+1, 2*k+2*i+1});
	}

	m = int(edges.size());

	printf("%d %d %d\n", l, r, m);
	for (auto edge: edges) {
		printf("%d %d\n", edge.first, edge.second);
	}
	return 0;
}
