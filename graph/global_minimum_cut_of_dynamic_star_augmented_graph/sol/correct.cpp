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

class Lazy_Segment_Tree{
	private:
	int n;
	vl lst,lazy;
	void Set_Lazy(int k,ll x){lst[k]+=x,lazy[k]+=x;}
	void Fix(int k){lst[k]=min(lst[k*2+1],lst[k*2+2]);}
	void Push(int k){
		Set_Lazy(k*2+1,lazy[k]);
		Set_Lazy(k*2+2,lazy[k]);
		lazy[k]=0;
	}
	void Rec(int a,int b,int k,int l,int r,ll x){
		if(r<=a||b<=l) return;
		if(a<=l&&r<=b){
			Set_Lazy(k,x);
			return;
		}
		Push(k);
		int m=(l+r)/2;
		Rec(a,b,k*2+1,l,m,x);
		Rec(a,b,k*2+2,m,r,x);
		Fix(k);
	}
	public:
	void Init(int n_){
		n=1;
		while(n<n_) n*=2;
		lst=vl(2*n-1,INF);
		lazy=vl(2*n-1);
	}
	ll Open(int k){
		k+=n-1;
		ll res=lst[k];
		while(k>0){
			k=(k-1)/2;
			res+=lazy[k];
		}
		return res;
	}
	void Add(int a,int b,ll x){Rec(a,b,0,0,n,x);}
	void Update(int k,ll x){Add(k,k+1,x-Open(k));}
	ll Min(){return lst[0];}
};

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

vi vid,head,hvy,par,dep;
Lazy_Segment_Tree lst;

int dfs(int v){
	int mx=0,t=1;
	for(auto u:tr[v]){
		par[u]=v;
		dep[u]=dep[v]+1;
		int s=dfs(u);
		t+=s;
		if(s>mx) mx=s,hvy[v]=u;
	}
	return t;
}
void bfs(int rt){
	int id=0;
	queue<int> q;
	q.push(rt);
	while(!q.empty()){
		int v=q.front();q.pop();
		for(int u=v;u!=-1;u=hvy[u]){
			vid[u]=id++;
			head[u]=v;
			for(auto w:tr[u]) if(w!=hvy[u]) q.push(w);
		}
	}
}
ll Query(int v,ll x){
	while(v>=0){
		lst.Add(vid[head[v]],vid[v]+1,x);
		v=par[head[v]];
	}
	return lst.Min();
}
void HL(){
	int n=tr.size();
	head=dep=vi(n);
	vid=hvy=par=vi(n,-1);
	lst.Init(n);
	dfs(n-1);bfs(n-1);
}

int n,m,q;
vi a;
vvp g;
vl b;

vi tmp;
ll DFS(int v){
	ll x=INF;
	for(auto u:tr[v]){
		x=min(x,DFS(u));
	}
	if(x<=b[v]) tmp[v]=0;
	else x=b[v];
	return x;
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
		if(!w) continue;
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
	for(int i=0;i<2*n-1;i++) lst.Update(vid[i],b[i]);
	for(int i=0;i<n;i++) Query(i,a[i]);
	for(int i=0;i<q;i++){
		int v,w;
		scanf("%d%d",&v,&w);
		printf("%lld\n",Query(v,w-a[v]));
		a[v]=w;
	}
}