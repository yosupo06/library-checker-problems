#include <cstdio>
#include "random.h"
#include "../params.h"
#include "./base.h"

int main(int, char* argv[]) {
	long long seed=atoll(argv[1]);
	auto gen=Random(seed);
	int n=N_MAX,m=n-1,q=Q_MAX;
	vvp g(n);
	vi a;
	vp b;
	for(int i=0;i<n/2-1;i++){
		g[i].push_back({i+1,(i+1)*2});
		g[i+1].push_back({i,(i+1)*2});
		g[i+n/2].push_back({i+n/2+1,(i+1)*2});
		g[i+n/2+1].push_back({i+n/2,(i+1)*2});
	}
	g[0].push_back({n/2,1});
	g[n/2].push_back({0,1});
	Random_Query(n,q,W_MAX,g,a,b,gen);
	Output(n,m,q,a,g,b,gen);
}