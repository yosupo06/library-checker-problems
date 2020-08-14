#include <cstdio>
#include "random.h"
#include "../params.h"
#include "./base.h"

int main(int, char* argv[]) {
	long long seed=atoll(argv[1]);
	auto gen=Random(seed);
	int n=1,m=0,q=Q_MAX;
	vvp g(n);
	vi a(n);
	vp b(q);
	for(int i=0;i<n;i++) a[i]=0;
	for(int i=0;i<q;i++) b[i]={0,gen.uniform<int>(0,W_MAX)};
	Output(n,m,q,a,g,b,gen);
}