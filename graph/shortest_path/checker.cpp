#include <vector>
#include <utility>
#include <stdint.h>
#include <inttypes.h>
#include "testlib.h"

struct Result {
	long long dist;
	std::vector<std::pair<int, int> > path;
};

Result read_ans(int n, InStream& stream) {
	int64_t dist = stream.readLong(-1, 1000000000000000000);
	if (dist == -1) return {-1, {}};
	int x = stream.readInt(1, n - 1);
	std::vector<std::pair<int, int> > path;
	for (int i = 0; i < x; i++) {
		int a = stream.readInt(0, n - 1);
		int b = stream.readInt(0, n - 1);
		path.push_back({a, b});
	}
	return {dist, path};
}

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	
	int n = inf.readInt();
	int m = inf.readInt();
	int s = inf.readInt();
	int t = inf.readInt();
	std::map<std::pair<int, int>, int> costs;
	for (int i = 0; i < m; i++) {
		int a = inf.readInt();
		int b = inf.readInt();
		int c = inf.readInt();
		costs[{a, b}] = c;
	}
	
	auto res_correct = read_ans(n, ans);
	auto res_submitted = read_ans(n, ouf);
	if (!res_submitted.path.size() != !res_correct.path.size()) {
		quitf(_wa, "path existence differ - expected: %s, found: %s",
			res_correct.path.size() ? "Yes" : "No",
			res_submitted.path.size() ? "Yes" : "No");
	}
	auto path_submitted = res_submitted.path;
	if (path_submitted.size()) {
		if (path_submitted.front().first != s)
			quitf(_wa, "start of the path invalid : %d", path_submitted.front().first);
		if (path_submitted.back().second != t)
			quitf(_wa, "end of the path invalid : %d", path_submitted.back().second);
		long long total_cost_submitted = 0;
		std::vector<bool> used(n);
		used[s] = true;
		for (int i = 0; i < (int) path_submitted.size(); i++) {
			if (i + 1 < (int) path_submitted.size() && path_submitted[i].second != path_submitted[i + 1].first)
				quitf(_wa, "teleporting between %i-th edge and %i-th edge from vertex %d to vertex %d",
					i, i + 1, path_submitted[i].second, path_submitted[i + 1].first);
			if (!costs.count(path_submitted[i]))
				quitf(_wa, "using an edge that doesn't exist : (%d, %d)",
					path_submitted[i].first, path_submitted[i].second);
			if (used[path_submitted[i].second]) 
				quitf(_wa, "visited the same vertex #%d twice", path_submitted[i].second);
			used[path_submitted[i].second] = true;
			total_cost_submitted += costs[path_submitted[i]];
		}
		if (total_cost_submitted != res_submitted.dist)
			quitf(_wa, "total weight differ between X(" I64 ") and submitted path's(" I64 ")",
				res_submitted.dist, total_cost_submitted);
		if (total_cost_submitted > res_correct.dist)
			quitf(_wa, "not the shortest - shortest : " I64 ", your path : " I64,
				res_correct.dist, total_cost_submitted);
		if (total_cost_submitted < res_correct.dist) // should never happen...
			quitf(_fail, "submitted solution got shorter path than judge's - submitted : " I64 ", judge : " I64,
				total_cost_submitted, res_correct.dist);
	}
	quitf(_ok, "OK");
}
