#include <vector>
#include <utility>
#include <set>
#include <cstdint>
#include <iostream>
#include <cassert>

#include "testlib.h"

using namespace std;

struct UnionFind {
    int n;
    vector<int> p, r;
    int gn;
    UnionFind(int _n = 0) : n(_n), p(n, -1), r(n, 1), gn(n) {}
    void merge(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        int x = group(a), y = group(b);
        if (x == y) return;  // same
        gn--;
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
            if (r[x] == r[y]) r[x]++;
        }
    }
    int group(int a) {
        assert(0 <= a && a < n);
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        return group(a) == group(b);
    }
};

bool read_ans(int n, int m, vector<vector<int>> g, InStream& stream) {
	string s;
	
	s = stream.readToken();

	if (s == "-1") return false;

	if (s != "s") {
		stream.quit(_pe, "first token must be s");
	}
	s = stream.readToken();
	if (s != "td") {
		stream.quit(_pe, "first token must be td");
	}

	int K = stream.readInt(0, 2 * n + m + 10);

	int tw = stream.readInt(0, 2);

	stream.readInt(n, n);
	stream.readEoln();

	vector<vector<int>> bag(K);
	for (int i = 0; i < K; i++) {
		string line = stream.readString();
		vector<string> tokens = split(line, ' ');

		if (!(2 <= int(tokens.size()) && int(tokens.size()) <= 2 + tw + 1)) {
			stream.quit(_pe, "tokens is too many");
		}
		if (tokens[0] != "b") {
			stream.quit(_pe, "expect b");
		}

		if (tokens[1] != to_string(i + 1)) {
			stream.quit(_pe, "expect i + 1");
		}

		for (int j = 2; j < int(tokens.size()); j++) {
			long long v = stringToLongLong(stream, tokens[j].c_str());
			if (v <= 0 || n < v) {
				stream.quitf(_pe, "out of range");
			}
			bag[i].push_back(int(v) - 1);
		}
	}
	vector<vector<int>> tree(K);
	UnionFind uf(K);
	for (int i = 0; i < K - 1; i++) {
		int u = stream.readInt(1, K) - 1;
		int v = stream.readInt(1, K) - 1;
		if (u == v) {
			stream.quitf(_pe, "not tree");
		}
		tree[u].push_back(v);
		tree[v].push_back(u);
		if (uf.same(u, v)) {
			stream.quitf(_pe, "not tree");
		}
		uf.merge(u, v);
	}

	set<pair<int, int>> ok_edges;
	vector<int> count(n);
	for (int i = 0; i < K; i++) {
		int l = int(bag[i].size());
		for (int a = 0; a < l; a++) {
			count[bag[i][a]]++;
			for (int b = a + 1; b < l; b++) {
				ok_edges.insert(minmax(bag[i][a], bag[i][b]));
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j: g[i]) {
			if (!ok_edges.count(minmax(i, j))) {
				stream.quitf(_wa, "no bag corresponded to (%d, %d)", i + 1, j + 1);
			}
		}
	}

	vector<int> visited(n);

	auto dfs = [&](auto self, int target, int node, int pre_node) -> int {
		int sum = 1;
		for (int near: tree[node]) {
			if (near == pre_node) continue;
			if (find(bag[near].begin(), bag[near].end(), target) == bag[near].end()) continue;			
			sum += self(self, target, near, node);
		}
		return sum;
	};
	for (int i = 0; i < K; i++) {
		for (int v: bag[i]) {
			if (visited[v]) continue;
			// check v
			if (count[v] != dfs(dfs, v, i, -1)) {
				stream.quitf(_wa, "%d is not tree on decomp, %d %d", v + 1, count[v], dfs(dfs, v, i, -1));
			}
			visited[v] = true;
		}
	}

	return true;
}

int main(int argc, char *argv[]) {
	registerTestlibCmd(argc, argv);
	inf.readToken();
	inf.readToken();
	int n = inf.readInt();
	int m = inf.readInt();
	vector<vector<int>> g(n);
	for (int i = 0; i < m; i++) {
		int a = inf.readInt() - 1;
		int b = inf.readInt() - 1;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	bool expect = read_ans(n, m, g, ans);
	bool actual = read_ans(n, m, g, ouf);

	if (expect && !actual) {
		quitf(_wa, "can not construct tree decomposition");
	}
	if (!expect && actual) {
		quitf(_fail, "judge can not construct...");
	}
	quitf(_ok, "OK %s", (expect ? "found" : "not found"));
}
