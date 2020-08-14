#include <cstdio>
#include "random.h"
#include "../params.h"
#include "./base.h"

int main(int, char* argv[]) {
	long long seed=atoll(argv[1]);
	auto gen=Random(seed);
	int n=0,m=M_MAX,q=Q_MAX;
	while(n*(n+1)/2<=m) n++;
	n++;
	vvp g;
	vi a;
	vp b;
	Random_Graph(n,m,W_MED,g,gen);
	Random_Query(n,q,W_MAX,g,a,b,gen);
	Output(n,m,q,a,g,b,gen);
}