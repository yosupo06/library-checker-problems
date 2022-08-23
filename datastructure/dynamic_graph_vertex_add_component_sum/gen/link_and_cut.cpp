#include <cstdio>
#include <vector>
#include <set>
#include <algorithm>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	const int BUCKET = 100;
	int n = N_AND_Q_MAX;
	int qt = N_AND_Q_MAX / BUCKET;
	int qt1 = qt/2+1;
	int q = qt * 100;
	printf("%d %d\n",n,q);
	for (int i = 0; i < n; i++) {
		int x=gen.uniform(A_AND_X_MIN,A_AND_X_MAX);
		printf("%d", x);
		if (i != n - 1) printf(" ");
	}
	printf("\n");

	vector<pair<int,int>> edges;
	{
		set<pair<int,int>> s;
		int cntq0 = qt1*(BUCKET-1);

		int turn1 = cntq0/2;
		for(int i=0; i<turn1; i++) s.insert(make_pair(i, i+1));
		for(int i=turn1; i<cntq0; i++) while(true){
			auto e = gen.uniform_pair(0, turn1);
			if(s.count(e) == 0){ s.insert(e); break; }
		}
		edges = vector<pair<int,int>>(s.begin(), s.end());
		gen.shuffle(edges.begin(), edges.end());
	}

	vector<int> perm(n);
	for(int i = 0; i < n; i++) perm[i] = i;
	gen.shuffle(perm.begin(), perm.end());
	for(auto& e : edges){
		if(gen.uniform_bool()) swap(e.first, e.second);
		e.first = perm[e.first];
		e.second = perm[e.second];
	}

	int q0iter = 0;
	int q1iter = 0;

	for (int it = 0; it < qt; it++) for (int i = 0; i < BUCKET; i++) {
		int t;
		if(i == BUCKET-1) t = 3;
		else if(it < qt1) t = 0;
		else t = 1;
		if(t == 0){
			auto e = edges[q0iter++];
			printf("%d %d %d\n", t, e.first, e.second);
		}
		if(t == 1){
			auto e = edges[q1iter++];
			printf("%d %d %d\n", t, e.first, e.second);
		}
		if(t == 3){
			auto v = edges[gen.uniform(0, (int)edges.size() - 1)].first;
			printf("%d %d\n", t, v);
		}
	}
	return 0;
}