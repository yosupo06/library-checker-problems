#include<iostream>
#include<vector>
#include<tuple>
#include<set>
#include<functional>
#include<assert.h>
using namespace::std;
using lint=long long;
#define rep(i,n) for(lint i=0;(i)<lint(n);(i)++)
vector<set<lint>>g;
vector<lint>a;
set<lint>visited;
lint dfs(lint now){
	lint ans=a[now];
	for(lint to:g[now]){
		if(visited.count(to))continue;
		visited.insert(to);
		ans+=dfs(to);
	}
	return ans;
}
int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	lint n,k;
	cin>>n>>k;
	g.resize(n);
	a.resize(n,0);
	rep(i,n){
		lint x;
		cin>>x;
		a[i]=x;
	}
	rep(i,k){
		lint x;
		cin>>x;
		if(x==0){
			lint u,v;
			cin>>u>>v;
			g[u].insert(v);
			g[v].insert(u);
		}
		if(x==1){
			lint u,v;
			cin>>u>>v;
			g[u].erase(v);
			g[v].erase(u);
		}
		if(x==2){
			lint v,x;
			cin>>v>>x;
			a[v]+=x;
		}
		if(x==3){
			lint v;
			cin>>v;
			visited.clear();
			visited.insert(v);
			cout<<dfs(v)<<endl;
		}
	}
}
