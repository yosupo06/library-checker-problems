#include <vector>
#include <queue>
#include <utility>
#include <stdint.h>
#include <algorithm>

#include "../fastio.h"

#define INF 1000000000000000000

// SPFA with LLL(Large Label Last)
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
	__int128_t inque_dist_sum = 0;
	std::vector<int64_t> dist(n, INF);
	std::vector<int> from(n, -1);
	std::vector<bool> inqueue(n, false);
	std::deque<int> que;
	que.push_back(s);
	dist[s] = 0;
	inqueue[s] = true;
	while (que.size()) {
		auto i = que.front();
		que.pop_front();
		inque_dist_sum -= dist[i];
		inqueue[i] = false;
		
		while (que.size() && (__int128_t) dist[que.front()] * que.size() > inque_dist_sum) que.push_back((int) que.front()), que.pop_front();
		for (auto j : hen[i]) if (dist[j.first] > dist[i] + j.second) {
			if (inqueue[j.first]) inque_dist_sum -= dist[j.first];
			dist[j.first] = dist[i] + j.second;
			from[j.first] = i;
			inque_dist_sum += dist[j.first];
			if (!inqueue[j.first]) {
				inqueue[j.first] = true;
				/*
				if (dist[j.first] <= que.front()) que.push_front(j.first);
				else que.push_back(j.first);*/
				if ((__int128_t) dist[j.first] * que.size() > inque_dist_sum) que.push_back(j.first);
				else que.push_front(j.first);
				// que.push_back(j.first);
				// while (que.size() && (__int128_t) dist[que.front()] * que.size() > inque_dist_sum) que.push_back((int) que.front()), que.pop_front();
			}
		}
	}
	if (dist[t] == INF) println("-1");
	else {
		std::vector<int> path;
		for (int cur = t; cur != -1; cur = from[cur]) path.push_back(cur);
		std::reverse(path.begin(), path.end());
		println(dist[t], ' ', path.size() - 1);
		for (int i = 0; i + 1 < (int) path.size(); i++) println(path[i], ' ', path[i + 1]);
	}
	return 0;
}
