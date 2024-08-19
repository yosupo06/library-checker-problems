#include <stdio.h>
#include "random.h"
#include "toptree.h"
#include "../params.h"

std::vector<std::pair<int, int> > random_tree(int n, Random &rnd) {
	std::vector<std::pair<int, int> > res;
	for (int i = 1; i < n; i++) res.push_back({rnd.uniform(0, i - 1), i});
	std::vector<int> perm(n);
	std::iota(perm.begin(), perm.end(), 0);
	rnd.shuffle(perm.begin(), perm.end());
	for (auto &i : res) {
		if (rnd.uniform_bool()) std::swap(i.first, i.second);
		i.first = perm[i.first];
		i.second = perm[i.second];
	}
	rnd.shuffle(res.begin(), res.end());
	return res;
}

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = gen.uniform<int>(2, N_MAX);
	int q = gen.uniform<int>(1, Q_MAX);
	printf("%d %d\n", n, q);
	
	for (int i = 0; i < n; i++) {
		if (i) printf(" ");
		printf("%d", gen.uniform<int>(0, VAL_MAX));
	}
	puts("");
	
	auto hens = random_tree(n, gen);
	for (auto i : hens) printf("%d %d\n", i.first, i.second);
	
	std::vector<TopTree::Node> nodes(n);
	for (auto &i : nodes) i.fetch();
	for (auto i : hens) {
		nodes[i.first].evert();
		nodes[i.first].link(&nodes[i.second]);
	}
	
	auto link_cut = [&] () {
		int remove_index = gen.uniform(0, n - 2);
		int x = hens[remove_index].first;
		int y = hens[remove_index].second;
		std::swap(hens[remove_index], hens.back());
		printf("%d %d ", x, y);
		nodes[x].evert();
		nodes[y].cut();
		hens.pop_back();
		
		nodes[x].evert();
		x = nodes[x].kth_heavy(gen.uniform(0, nodes[x].size() - 1)) - &nodes[0];
		nodes[y].evert();
		y = nodes[y].kth_heavy(gen.uniform(0, nodes[y].size() - 1)) - &nodes[0];
		printf("%d %d", x, y);
		nodes[x].evert();
		nodes[x].link(&nodes[y]);
		hens.push_back({x, y});
	};
	for (int i = 0; i < q; i++) {
		int t = gen.uniform(0, 2);
		printf("%d ", t);
		if (t == 0) link_cut();
		else {
			auto edge = hens[gen.uniform(0, n - 2)];
			if (gen.uniform_bool()) std::swap(edge.first, edge.second);
			printf("%d %d", edge.first, edge.second);
			if (t == 1) printf(" %d", gen.uniform<int>(0, VAL_MAX));
		}
		puts("");
	}
	
	return 0;
}
