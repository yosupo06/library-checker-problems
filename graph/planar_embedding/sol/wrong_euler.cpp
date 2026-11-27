// Wrong: answers Yes iff every connected component with n >= 3 vertices has
// m <= 3n - 6, and prints the neighbors in input order as the "embedding".
#include <cstdint>
#include <iostream>
#include <vector>
#include <numeric>

namespace {

std::vector<int> par;
int find(int x) { while (par[x] != x) x = par[x] = par[par[x]]; return x; }

} // namespace

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int T;
	std::cin >> T;
	while (T--) {
		int N, M;
		std::cin >> N >> M;
		par.resize(N);
		std::iota(par.begin(), par.end(), 0);
		std::vector<std::vector<int>> adj(N);
		for (int i = 0; i < M; i++) {
			int a, b;
			std::cin >> a >> b;
			adj[a].push_back(b);
			adj[b].push_back(a);
			par[find(a)] = find(b);
		}
		std::vector<int64_t> n_c(N, 0), m_c(N, 0);
		for (int v = 0; v < N; v++) {
			n_c[find(v)]++;
			m_c[find(v)] += int(adj[v].size());
		}
		bool ok = true;
		for (int v = 0; v < N; v++) {
			if (find(v) == v && n_c[v] >= 3 && m_c[v] / 2 > 3 * n_c[v] - 6) ok = false;
		}
		if (!ok) {
			std::cout << "No\n";
			continue;
		}
		std::cout << "Yes\n";
		for (int v = 0; v < N; v++) {
			for (size_t i = 0; i < adj[v].size(); i++) {
				if (i) std::cout << ' ';
				std::cout << adj[v][i];
			}
			std::cout << '\n';
		}
	}
	return 0;
}
