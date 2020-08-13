#include <set>
#include <cassert>
#include <algorithm>
#include "testlib.h"
#include "params.h"

typedef std::pair<int,int> P;

int main(){
	registerValidation();
	
	int n=inf.readInt(N_MIN,N_MAX);
	inf.readSpace();
	int m=inf.readInt(M_MIN,std::min((long long)n*(n-1)/2,M_MAX));
	inf.readSpace();
	int q=inf.readInt(Q_MIN,Q_MAX);
	inf.readChar('\n');
	
	for(int i=0;i<n;i++){
		if(i) inf.readSpace();
		inf.readInt(0,W_MAX);
	}
	inf.readChar('\n');
	std::set<P> st;
	for(int i=0;i<m;i++){
		int u=inf.readInt(0,n-1);
		inf.readSpace();
		int v=inf.readInt(0,n-1);
		inf.readSpace();
		inf.readInt(1,W_MAX);
		assert(u!=v);
		if(u>v) std::swap(u,v);
		assert(st.find({u,v})==st.end());
		st.insert({u,v});
		inf.readChar('\n');
	}
	for(int i=0;i<q;i++){
		inf.readInt(0,n-1);
		inf.readSpace();
		inf.readInt(0,W_MAX);
		inf.readChar('\n');
	}
	
	inf.readEof();
}
