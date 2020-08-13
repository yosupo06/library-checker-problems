#include <cstdio>
#include "random.h"
#include "../params.h"
#include "./base.h"

int main(int, char* argv[]) {
	long long seed=atoll(argv[1]);
	auto gen=Random(seed);
	int n=1,m=0,q=Q_MAX;
	while(2*n<=N_MAX) n*=2;
	vvp g(n);
	vi a;
	vp b;
	int id=0;
	for(int i=20;i>=0;i--) if(n&1<<i){
		m+=(1<<i)-1;
		for(int j=1;j<1<<i;j++){
			for(int k=0;k<i;k++) if(j&1<<k){
				g[id+j-1].push_back({id+j,1<<(i-k-1)});
				g[id+j].push_back({id+j-1,1<<(i-k-1)});
				break;
			}
		}
		id+=1<<i;
	}
	Random_Query(n,q,W_MAX,g,a,b,gen);
	Output(n,m,q,a,g,b,gen);
}