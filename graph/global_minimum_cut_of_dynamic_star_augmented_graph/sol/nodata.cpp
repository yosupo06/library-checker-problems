#include <algorithm>
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<P> vp;
typedef vector<vp> vvp;
const ll INF=1LL<<60;

vvi tr;
void EVS(vvp g){
	int n=g.size();
	tr=vvi(2*n-1);
	vl used(2*n-1,1);
	for(int i=0;i<n-1;i++){
		g.push_back(vp());
		vi ord(n-i),vis(n+i);
		vl cost(n+i);
		priority_queue<pll> que;
		for(int j=0;j<n+i;j++) if(used[j]){
			for(auto p:g[j]) cost[j]+=p.second;
			que.push({-cost[j],j});
		}
		for(int j=0;j<n-i;j++) while(1){
			auto pr=que.top();que.pop();
			int v=pr.second;
			if(vis[v]) continue;
			vis[v]=1;
			ord[j]=v;
			for(auto p:g[v]){
				int u=p.first;
				if(!vis[u]){
					cost[u]-=p.second;
					que.push({-cost[u],u});
				}
			}
			break;
		}
		int v0=ord[n-i-1],v1=ord[n-i-2];
		g[v0].clear(),g[v1].clear();
		used[v0]=used[v1]=0;
		for(int j=0;j<n+i;j++) if(used[j]) for(auto &p:g[j]){
			int u=p.first;
			if(u==v0||u==v1){
				p.first=n+i;
				g[n+i].push_back({j,p.second});
			}
		}
		tr[n+i].push_back(v0);
		tr[n+i].push_back(v1);
	}
}

vi par,dep,inds;
vl b;
ll ans=INF,id=-1;

void dfs(int v){
	for(auto u:tr[v]){
		par[u]=v;
		dep[u]=dep[v]+1;
		dfs(u);
	}
}
void Query(int v,ll x){
	if(x==0) return;
	bool flag=0;
	while(v>=0){
		if(v==id&&x>0) flag=1;
		b[v]+=x;
		if(b[v]<ans) ans=b[v],id=v;
		v=par[v];
	}
	if(flag){
		ans=INF;
		for(auto i:inds) if(ans>b[i]) ans=b[i],id=i;
	}
}
void HL(){
	int n=tr.size();
	dep=vi(n);
	par=vi(n,-1);
	dfs(n-1);
}

int n,m,q;
vi a;
vvp g;

vi tmp;
vvi tr_;
ll DFS(int v){
	ll x=INF;
	for(auto u:tr[v]){
		x=min(x,DFS(u));
	}
	if(x<=b[v]) tmp[v]=0;
	else x=b[v];
	return x;
}
void dfs1(int v,int p){
	if(tmp[v]) inds.push_back(v);
	for(auto u:tr[v]){
		if(tmp[u]){
			tr_[p].push_back(u);
			par[u]=p;
			dfs1(u,u);
		}
		else dfs1(u,p);
	}
}

int main(){
	scanf("%d%d%d",&n,&m,&q);
	a=vi(n);
	g=vvp(n);
	b=vl(2*n-1);
	for(int i=0;i<n;i++) scanf("%d",&a[i]);
	for(int i=0;i<m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		g[u].push_back({v,w});
		g[v].push_back({u,w});
	}
	EVS(g);HL();
	for(int i=0;i<n;i++) for(auto p:g[i]){
		int u=i,v=p.first;
		if(u>v) continue;
		while(u!=v){
			if(dep[u]<dep[v]) swap(u,v);
			b[u]+=p.second;
			u=par[u];
		}
	}
	tmp=vi(2*n-1,1);
	tr_=vvi(2*n-1);
	for(auto i:tr[2*n-2]) DFS(i);
	dfs1(2*n-2,2*n-2);
	tr=tr_;
	for(int i=0;i<n;i++){
		int v=i;
		while(v>=0){
			b[v]+=a[i];
			v=par[v];
		}
	}
	for(auto i:inds) if(b[i]<ans) ans=b[i],id=i;
	for(int i=0;i<q;i++){
		int v,w;
		scanf("%d%d",&v,&w);
		Query(v,w-a[v]);
		printf("%lld\n",ans);
		a[v]=w;
	}
}