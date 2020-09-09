#include <cstdio>
#include "random.h"
#include "../params.h"
#include "./base.h"

int main(int, char* argv[]) {
	long long seed=atoll(argv[1]);
	auto gen=Random(seed);
	int n=N_MED,m=M_MAX,q=Q_MAX;
	vvp g;
	vi a;
	vp b;
	Random_Graph(n,m,W_MED,g,gen);
	Random_Query(n,q,W_MAX,g,a,b,gen);
	Output(n,m,q,a,g,b,gen);
}