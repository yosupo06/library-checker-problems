#include <vector>
#include <queue>
#include <algorithm>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define INF 1000000000000000000

int ri() {
	int n;
	scanf("%d", &n);
	return n;
}

// SPFA, Shortest Path Fast Algorithm
// O(NM)

int main() {
	int n = ri();
	int m = ri();
	int s = ri();
	int t = ri();
	struct Hen {
		int to;
		int cost;
		int id;
	};
	std::vector<std::vector<std::pair<int, int> > > hen(n);
	for (int i = 0; i < m; i++) {
		int a = ri();
		int b = ri();
		int c = ri();
		hen[a].push_back({b, c});
	}
	std::vector<int64_t> dist(n, INF);
	std::vector<int> from(n, -1);
	std::vector<bool> inqueue(n, false);
	std::queue<int> que;
	que.push(s);
	dist[s] = 0;
	inqueue[s] = true;
	while (que.size()) {
		auto i = que.front();
		que.pop();
		inqueue[i] = false;
		for (auto j : hen[i]) if (dist[j.first] > dist[i] + j.second) {
			dist[j.first] = dist[i] + j.second;
			from[j.first] = i;
			if (!inqueue[j.first]) inqueue[j.first] = true, que.push(j.first);
		}
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
