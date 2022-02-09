#include <iostream>
#include <vector>

#include "../params.h"

using namespace std;

int main() {

	int l = L_MAX;
	int r = R_MAX;
	int m = M_MAX;

	using P = pair<int, int>;
	vector<P> edges;

	int k = l / 8 * 2;
	for(int i = 0; i < k; i++) {
		edges.push_back({i, i});
	}
	for(int i = 0; i < k-1; i++) {
		edges.push_back({i+1, i});
	}
	for(int i = 0; i < k/2; i++) {
		edges.push_back({i, k+2*i});
		edges.push_back({2*k+2*i, k+2*i});
		edges.push_back({2*k+2*i, 3*k+2*i});
		edges.push_back({k+2*i, i});
		edges.push_back({k+2*i, 2*k+2*i});
		edges.push_back({3*k+2*i, 2*k+2*i});
	}
	for(int j = 0; j < k/2; j++) {
		int i = k/2-1-j;
		edges.push_back({k/2+j, k+2*i+1});
		edges.push_back({2*k+2*i+1, k+2*i+1});
		edges.push_back({2*k+2*i+1, 3*k+2*i+1});
		edges.push_back({k+2*i+1, k/2+j});
		edges.push_back({k+2*i+1, 2*k+2*i+1});
		edges.push_back({3*k+2*i+1, 2*k+2*i+1});
	}

	m = int(edges.size());

	printf("%d %d %d\n", l, r, m);
	for (auto edge: edges) {
		printf("%d %d\n", edge.first, edge.second);
	}
	return 0;
}
