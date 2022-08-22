#include <iostream>
#include <vector>
#include <set>
#include "random.h"
#include "./myset.hpp"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	int n = N_AND_Q_MAX;
	int q = N_AND_Q_MAX;
	printf("%d %d\n",n,q);
	for (int i = 0; i < n; i++) {
		int x=gen.uniform(A_AND_X_MIN,A_AND_X_MAX);
		printf("%d", x);
		if (i != n - 1) printf(" ");
	}
	printf("\n");
	myset<pair<int,int>>s;
	for (int i = 0; i < q; i++) {
		int t;
		if(s.size())t = gen.uniform(0,3);
		else {
			t=gen.uniform(1,3);
			if(t==1)t=0;
		}
		if(t==0){
			auto v = gen.uniform_pair(0,n-1);
			bool swap_flag=gen.uniform_bool();
			if(!s.count(v)){
				s.insert(v);
				if(swap_flag){
					swap(v.first,v.second);
				}
				printf("%d %d %d\n",0,v.first,v.second);
			}else{
				s.erase(v);
				if(swap_flag){
					swap(v.first,v.second);
				}
				printf("%d %d %d\n",1,v.first,v.second);
			}
		}
		if(t==1){
			int v = gen.uniform(0,s.size()-1);
			printf("%d %d %d\n",t,s[v].first,s[v].second);
			s.erase(s[v]);
		}
		if(t==2){
			int v = gen.uniform(0,n-1);
			int x = gen.uniform(A_AND_X_MIN,A_AND_X_MAX);
			printf("%d %d %d\n",t,v,x);
		}
		if(t==3){
			int v = gen.uniform(0,n-1);
			printf("%d %d\n",t,v);
		}
	}
	return 0;
}