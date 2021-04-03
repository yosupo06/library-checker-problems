#include <vector>
#include <set>
#include <utility>
#include <tuple>

#include "random.h"
#include "gen_common.hpp"
#include "../params.h"

using namespace std;

struct G {
	int n;
	vector<pair<int, int>> edges;
	void uniq_edges() {
		for (auto& p: edges) {
			if (p.first > p.second) swap(p.first, p.second);
		}
		sort(edges.begin(), edges.end());
		edges.erase(unique(edges.begin(), edges.end()), edges.end());
	}
};
G construct(Random& gen, int m) {
	if (m == 1) {
		return {2, {{0, 1}}};
	}
	if (gen.uniform_bool()) {
		// series
		int lm = gen.uniform(1, m - 1);
		auto lg = construct(gen, lm);
		auto rg = construct(gen, m - lm);
		for (auto e: rg.edges) {
			lg.edges.push_back({e.first + lg.n - 1, e.second + lg.n - 1});
		}
		lg.n += rg.n - 1;
		return lg;
	} else {
		// parallel
		int lm = gen.uniform(1, m - 1);
		auto lg = construct(gen, lm);
		auto rg = construct(gen, m - lm);
		for (auto& e: lg.edges) {
			int u = e.first, v = e.second;
			if (u == lg.n - 1) u += rg.n - 2;
			if (v == lg.n - 1) v += rg.n - 2;
			e = {u, v};
		}
		for (auto e: rg.edges) {
			int u = e.first, v = e.second;
			if (u != 0) u += lg.n - 2;
			if (v != 0) v += lg.n - 2;
			lg.edges.push_back({u, v});
		}
		lg.n += rg.n - 2;
		return lg;
	}
}

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	auto g = construct(gen, M_MAX);
	g.uniq_edges();
	print_graph(gen, g.n, g.edges);
	return 0;
}
