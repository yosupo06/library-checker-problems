#pragma once

#include <vector>
#include <cstdio>

using namespace std;

void print_graph(Random& gen, vector<vector<int>> g) {
	int n = int(g.size());
	vector<int> idx = gen.perm<int>(n);
	int m = 0;
	for (int i = 0; i < n; i++) {
		for (int j: g[i]) {
			if (i < j) m++;
		}
	}
	printf("p tw %d %d\n", n, m);
	for (int i = 0; i < n; i++) {
		for (int j: g[i]) {
			if (i < j) {
				printf("%d %d\n", idx[i] + 1, idx[j] + 1);
			}
		}
	}
}

void print_graph(Random& gen, int n, vector<pair<int, int>> edges) {
	vector<vector<int>> g(n);
	for (auto p: edges) {
		assert(0 <= p.first && p.first < n);
		assert(0 <= p.second && p.second < n);
		g[p.first].push_back(p.second);
		g[p.second].push_back(p.first);
	}
	print_graph(gen, std::move(g));
}

void shuffle_vertices_and_print_graph(Random& gen, int n, vector<pair<int, int>> edges) {
	vector<int> idx = gen.perm<int>(n);

	int m = edges.size();
	printf("p tw %d %d\n", n, m);
	for (int i = 0; i < m; i++) {
		int u = edges[i].first;
		int v = edges[i].second;
		assert(0 <= u && u < n);
		assert(0 <= v && v < n);
		printf("%d %d\n", idx[u] + 1, idx[v] + 1);
	}
}
