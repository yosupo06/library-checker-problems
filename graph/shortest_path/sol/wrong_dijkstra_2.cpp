#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
#include <stdint.h>
#include <inttypes.h>
#include <algorithm>

int ri() {
	int n;
	scanf("%d", &n);
	return n;
}

template<typename T> using pqueue_inv = std::priority_queue<T, std::vector<T>, std::greater<T> >;

int main() {
	int n = ri();
	int m = ri();
	int s = ri();
	int t = ri();
	std::vector<std::vector<std::pair<int, int> > > hen(n);
	std::vector<std::vector<std::pair<int, int> > > rev(n);
	for (int i = 0; i < m; i++) {
		int a = ri();
		int b = ri();
		int c = ri();
		hen[a].push_back({b, c});
		rev[b].push_back({a, c});
	}
	std::vector<int64_t> dist(n, -1);
	pqueue_inv<std::pair<int64_t, int> > que;
	que.push({0, s});
	while (que.size()) {
		auto i = que.top();
		que.pop();
		if (dist[i.second] == -1) {
			dist[i.second] = i.first;
			for (auto j : hen[i.second])
				que.push({i.first + j.second, j.first});
		}
	}
	if (dist[t] == -1) puts("-1");
	else {
		std::vector<int> path;
		std::vector<bool> used(n);
		int u = t;
		path.emplace_back(u);
		while (s != u) {
			for (auto [from, cost] : rev[u]) {
				if (!used[from] && dist[u] - dist[from] == cost) {
					path.emplace_back(from);
					used[u] = true;
					u = from;
					break;
				}
			}
		}
		std::reverse(path.begin(), path.end());
		printf("%lld %d\n", (long long) dist[t], (int) path.size() - 1);
		for (int i = 0; i + 1 < (int) path.size(); i++) printf("%d %d\n", path[i], path[i + 1]);
	}
	return 0;
}
