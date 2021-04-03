#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
    int n = N_AND_M_MAX;
	int m = n;
	int k = K_MAX;
    vector<int> v(n);
	for (int i = 0; i < n; i++)v[i]=i;
	gen.shuffle(v.begin(),v.end());
	int s=v[0];
	int t=v.back();
	printf("%d %d %d %d %d\n",n,m,s,t,k);
	for (int i = 0; i < m; i++){
        int c=C_MAX;
        printf("%d %d %d\n",v[i],v[(i+1)%n],c);
	}
	return 0;
}