#include <cstdio>
#include <tuple>
#include <utility>
#include <vector>
#include <set>
#include <algorithm>
#include <math.h>
#include <cassert>
using i64 = long long;
static constexpr i64 mod = 998244353;

i64 solve_naive(int n,std::vector<std::vector<int>> g,std::vector<i64> xs){
	i64 ans = 0;
	if(n > 30) return 0;
	for(int bit = 1; bit < (1 << n); bit++){
		std::set<int> now_ver;
		for(int i = 0; i < n; i++){
			if(1 & (bit >> i)){
				now_ver.insert(i);
			}
		}
		int flag = 1;
		for(auto i: now_ver){
			for(auto j: now_ver){
				if (i != j){
					if(std::find(g[i].begin(), g[i].end(), j) == g[i].end()){
						flag = 0;
					}
				}
			}
		}
		if(flag){
			i64 now = 1;
			for(auto i: now_ver){
				now *= xs[i];
				now %= mod;
			}
			ans += now;
			ans %= mod;
		}
	}
	return ans;
}
int main() {

	int n, m;
	std::scanf("%d %d", &n, &m);
	std::vector<i64> xs(n);
	for (auto &x : xs) {
    	scanf("%lld", &x);
  	}
  	std::vector<std::pair<int, int>> edges(m);
  	for (auto &e : edges) {
    	int &u = e.first;
    	int &v = e.second;
    	std::scanf("%d %d", &u, &v);
  	}


  	std::vector<std::vector<int>> g(n);
  	for (const auto &e : edges) {
    	int u = e.first;
    	int v = e.second;
    	g[u].push_back(v);
    	g[v].push_back(u);
  	}
  	std::vector<int> deg(n);
  	for (int i = 0; i < n; i++){
    	deg[i] = g[i].size();
  	}
  	std::set<int> S;
  	for (int i = 0; i < n; i++){
    	S.insert(i);
  	}
	
	i64 ans = solve_naive(n,g,xs);

	printf("%lld\n", ans);
    return 0;
}
