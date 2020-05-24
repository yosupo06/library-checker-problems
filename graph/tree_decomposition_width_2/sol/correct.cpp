#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int main() {
	char buf[10];
	int n, m;
	scanf("%s %s %d %d", buf, buf, &n, &m);

	V<set<int>> g(n);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		g[a].insert(b);
		g[b].insert(a);
	}


	
	V<int> deg(n);
	V<bool> alive(n, true);
	queue<int> que;
	for (int i = 0; i < n; i++) {
		deg[i] = int(g[i].size());
		que.push(i);
	}

	struct Event {
		int deg;
		int a, b, c;
	};
	V<Event> events;

	auto remove = [&](int p) {
		assert(alive[p]);
		alive[p] = false;
		for (int i: g[p]) {
			assert(alive[i]);
			g[i].erase(p);
			deg[i]--;
			que.push(i);
		}
	};
	while (que.size()) {
		int p = que.front(); que.pop();
		int d = deg[p];
		if (!alive[p] || d >= 3) continue;
		if (d == 0) {
			events.push_back({0, p, -1, -1});
		}
		if (d == 1) {
			events.push_back({1, p, *g[p].begin(), -1});
		}
		if (d == 2) {
			int u = *g[p].begin();
			int v = *g[p].rbegin();
			events.push_back({2, p, u, v});
			g[u].insert(v);
			g[v].insert(u);
			deg[u] = int(g[u].size());
			deg[v] = int(g[v].size());
		}
		remove(p);
	}

	for (int i = 0; i < n; i++) {
		if (alive[i]) {
			printf("-1\n");
			return 0;
		}
	}
	
	VV<int> bag;
	V<int> par;
	V<int> node_pos(n, -1);
	map<pair<int, int>, int> edge_pos;
	reverse(events.begin(), events.end());
	for (auto event: events) {
		int id = int(bag.size());
		if (event.deg == 0) {
			bag.push_back({event.a});
			par.push_back(id - 1);
		}
		if (event.deg == 1) {
			bag.push_back({event.a, event.b});
			par.push_back(node_pos[event.b]);
		}
		if (event.deg == 2) {
			bag.push_back({event.a, event.b, event.c});
			par.push_back(edge_pos[minmax(event.b, event.c)]);
		}
		for (int x: bag.back()) {
			node_pos[x] = id;
		}
		for (int x: bag.back()) {
			for (int y: bag.back()) {
				if (x < y) edge_pos[{x, y}] = id;
			}
		}
	}
	int K = int(bag.size());
	printf("s td %d 2 %d\n", K, n);
	for (int i = 0; i < K; i++) {
		printf("b %d", i + 1);
		for (int x: bag[i]) {
			printf(" %d", x + 1);
		}
		printf("\n");
	}
	for (int i = 1; i < K; i++) {
		printf("%d %d\n", par[i] + 1, i + 1);
	}
    return 0;
}

