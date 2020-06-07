#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	int n = gen.uniform<int>(N_AND_M_MIN,N_AND_M_MAX);
	int m = gen.uniform<int>(N_AND_M_MIN,N_AND_M_MAX);
	int k = gen.uniform<int>(K_MIN,K_MAX);
	printf("%d %d %d\n",n,m,k);
	int s,t;
	s=gen.uniform(0,n-1);
	t=gen.uniform(0,n-1);
	printf("%d %d\n",s,t);
	vector<int> v(n);
	for (int i = 0; i < n; i++)v[i]=i;
	gen.shuffle(v.begin(),v.end());
	for (int i = 0; i < m; i++) {
		if(i<n-1){
			int c;
			c=gen.uniform(C_MIN,C_MAX);
			printf("%d %d %d\n",v[i],v[i+1],c);
		}else{
			int u,v,c;
			u=gen.uniform(0,n-1);
			v=gen.uniform(0,n-1);
			c=gen.uniform(C_MIN,C_MAX);
			printf("%d %d %d\n",u,v,c);
		}
	}
	return 0;
}