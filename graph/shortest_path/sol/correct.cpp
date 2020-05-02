#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>
#include <stdint.h>
#include <inttypes.h>
#include <algorithm>

#define INF 1000000000000000000

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
	for (int i = 0; i < m; i++) {
		int a = ri();
		int b = ri();
		int c = ri();
		hen[a].push_back({b, c});
	}
	std::vector<int64_t> dist(n, INF);
	std::vector<int> from(n, -1);
	pqueue_inv<std::pair<int64_t, int> > que;
	que.push({dist[s] = 0, s});
	while (que.size()) {
		auto i = que.top();
		que.pop();
		if (i.first != dist[i.second]) continue;
		for (auto j : hen[i.second]) if (dist[j.first] > i.first + j.second) 
			que.push({dist[j.first] = i.first + j.second, j.first}), from[j.first] = i.second;
	}
	if (dist[t] == INF) puts("-1");
	else {
		std::vector<int> path;
		for (int cur = t; cur != -1; cur = from[cur]) path.push_back(cur);
		std::reverse(path.begin(), path.end());
		printf("%lld %d\n", (long long) dist[t], (int) path.size() - 1);
		for (int i = 0; i + 1 < (int) path.size(); i++) printf("%d %d\n", path[i], path[i + 1]);
	}
	return 0;
}
