#include <cstdio>
#include "random.h"
#include "../params.h"
#include "./base.h"

int main(int, char* argv[]) {
	long long seed=atoll(argv[1]);
	auto gen=Random(seed);
	int n=0,m=M_MAX,q=Q_MAX;
	while(n*(n+1)/2<=m) n++;
	m=n*(n-1)/2;
	vvp g(n);
	vi a(n);
	vp b(q);
	for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
		g[i].push_back({j,W_MAX});
		g[j].push_back({i,W_MAX});
	}
	for(int i=0;i<n;i++) a[i]=W_MAX;
	for(int i=0;i<q;i+=2){
		int v=gen.uniform<int>(0,n-1);
		b[i]={v,W_MAX-1};
		b[i+1]={v,W_MAX};
	}
	Output(n,m,q,a,g,b,gen);
}