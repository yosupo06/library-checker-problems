#include "random.h"
#include <functional>
#include <algorithm>
#include <iostream>
#include <utility>
#include <cassert>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef pair<ll,ll> pll;
typedef pair<P,int> pip;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<P> vp;
typedef vector<vp> vvp;
typedef vector<pip> vip;
const ll INF=1LL<<60;

void Output(int n,int m,int q,vi a,vvp g,vp b,Random &gen){
	assert(n==(int)a.size()&&q==(int)b.size());
	{
		int t=0;
		for(int i=0;i<n;i++) for(auto p:g[i]) if(i<p.first) t++;
		assert(t==m);
	}
	vi perm(n),inv(n);
	for(int i=0;i<n;i++) perm[i]=i;
	gen.shuffle(perm.begin(),perm.end());
	for(int i=0;i<n;i++) inv[perm[i]]=i;
	printf("%d %d %d\n",n,m,q);
	for(int i=0;i<n;i++){
		if(i) printf(" ");
		printf("%d",a[inv[i]]);
	}
	printf("\n");
	vip edge;
	for(int i=0;i<n;i++) for(auto p:g[i]){
		int u=perm[i],v=perm[p.first];
		if(u>v) continue;
		if(gen.uniform_bool()) swap(u,v);
		edge.push_back({{u,v},p.second});
	}
	gen.shuffle(edge.begin(),edge.end());
	assert((int)edge.size()==m);
	for(auto p:edge) printf("%d %d %d\n",p.first.first,p.first.second,p.second);
	for(int i=0;i<q;i++) printf("%d %d\n",perm[b[i].first],b[i].second);
}

ll DFS(int v,vvi &tr,vi &used,vl &c){
	ll x=INF;
	for(auto u:tr[v]) x=min(x,DFS(u,tr,used,c));
	if(x<=c[v]) used[v]=0;
	else x=c[v];
	return x;
}
void dfs(int v,int p,vvi &tr,vvi &tr_,vi &par_,vi &vid){
	for(auto u:tr[v]){
		if(vid[u]>=0){
			tr_[vid[p]].push_back(vid[u]);
			par_[vid[u]]=vid[p];
			dfs(u,u,tr,tr_,par_,vid);
		}
		else dfs(u,p,tr,tr_,par_,vid);
	}
}
void EVS(vvp g,vvi &tr,vl &c,vi &par,bool debug=false){
	if(debug){printf("DEBUG\n");}
	int n=g.size();
	tr=vvi(2*n-1);
	c=vl(2*n-1);
	vi used(2*n-1,1);
	vvp g_=g;
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
	par=vi(2*n-1,-1);
	vi dep(2*n-1);
	fill(used.begin(),used.end(),1);
	for(auto i:tr[2*n-2]){
		queue<int> q;
		q.push(i);
		par[i]=2*n-2;
		dep[i]=1;
		while(!q.empty()){
			int v=q.front();q.pop();
			for(auto u:tr[v]){
				par[u]=v;
				dep[u]=dep[v]+1;
				q.push(u);
			}
		}
	}
	for(int i=0;i<n;i++) for(auto p:g_[i]){
		int u=i,v=p.first;
		if(u>v) continue;
		while(u!=v){
			if(dep[u]<dep[v]) swap(u,v);
			c[u]+=p.second;
			u=par[u];
		}
	}
	for(auto i:tr[2*n-2]) DFS(i,tr,used,c);
	int N=0;
	vi vid(2*n-1,-1);
	vl c_;
	for(int i=0;i<2*n-1;i++) if(used[i]){
		c_.push_back(c[i]);
		vid[i]=N++;
	}
	vvi tr_(N);
	vi par_(N,-1);
	dfs(2*n-2,2*n-2,tr,tr_,par_,vid);
	tr=tr_,c=c_,par=par_;
}

void Random_Graph(int n,int m,int M,vvp &g,Random &gen){
	g=vvp(n);
	int I=0;
	for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
		I++;
		int x=gen.uniform<int>(0,n*(n-1)/2-I);
		if(x<m){
			int t=gen.uniform<int>(1,M);
			g[i].push_back({j,t});
			g[j].push_back({i,t});
			m--;
		}
	}
	assert(m==0);
}

void Random_Query(int n,int q,int M,vvp g,vi &a,vp &b,Random &gen,bool debug=false){
	a=vi(n,-1);
	b=vp(q,{-1,-1});
	vvi tr;
	vi par;
	vl c;
	ll ans=INF,id=-1,mx=0;
	EVS(g,tr,c,par,debug);
	int N=tr.size();
	for(int i=0;i<n;i++) mx=max(mx,c[i]);
	for(int i=0;i<n;i++){
		a[i]=gen.uniform<int>(0,mx/n+10);
		int v=i;
		while(v>=0){
			c[v]+=a[i];
			v=par[v];
		}
	}
	for(int i=0;i<N;i++) if(c[i]<ans) ans=c[i],id=i;
	vi a_=a;
	function<void(int,ll,int)> Set=[&a,&b,&par,&c,&ans,&id,M](int v,ll x,int i){
		if(x<0) x=0;
		if(x>M) x=M;
		ll d=x-a[v];
		if(d){
			bool flag=0;
			int u=v;
			while(u>=0){
				if(u==id&&d>0) flag=1;
				c[u]+=d;
				if(c[u]<ans) ans=c[u],id=u;
				u=par[u];
			}
			if(flag){
				ans=INF;
				for(int i=0;i<(int)c.size();i++) if(ans>c[i]) ans=c[i],id=i;
			}
		}
		a[v]=x;
		b[i]={v,a[v]};
	};
	if(debug){
		for(int i=0;i<N;i++) printf("%d ",par[i]);
		printf("\n");
		for(int i=0;i<N;i++) printf("%d ",(int)tr[i].size());
		printf("\n");
		printf("%d %d\n",n,N);
	}
	for(int i=0;i<q;i++){
		int v=id,type=gen.uniform<int>(1,10000);
		while(v>=n){v=tr[v][gen.uniform<int>(0,(int)tr[v].size()-1)];}
		if(type<500){
			int d=gen.uniform<int>(0,a[v]);
			Set(v,a[v]-d,i);
			continue;
		}
		if(type==500&&i+n<q){
			int v=-1,cnt=0;
			do{
				v=gen.uniform<int>(n,N-1);
				cnt++;
			}while(par[v]>=0&&tr[par[v]].size()==1&&cnt<100);
			if(cnt==100) v=gen.uniform<int>(0,n-1);
			if(debug){
				printf("%d %d %d\n",v,N,i);
			}
			vi tmp;
			queue<int> q;
			q.push(v);
			while(!q.empty()){
				int u=q.front();q.pop();
				if(u<n) tmp.push_back(u);
				else for(auto w:tr[u]) q.push(w);
			}
			gen.shuffle(tmp.begin(),tmp.end());
			for(auto j:tmp) Set(j,0,i++);
			if(v==N-1){
				i--;
				continue;
			}
			while(1){
				tmp.clear();
				for(int j=0;j<N;j++) if(j!=v&&c[j]<=c[v]) tmp.push_back(j);
				if(tmp.empty()) break;
				gen.shuffle(tmp.begin(),tmp.end());
				int u=tmp[0],w=u;
				while(w>=n){
					w=tr[w][gen.uniform<int>(0,(int)tr[w].size()-1)];
					if(w==v) w=u;
				}
				if(debug) printf("%lld %lld\n",c[u],c[v]);
				Set(w,a[w]+c[v]-c[u]+gen.uniform<int>(1,30),i++);
				if(debug) printf("%lld %lld\n",c[u],c[v]);
			}
			i--;
			continue;
		}
		vi used(N,1);
		int u=v;
		while(u>=0) used[u]=0,u=par[u];
		ll mn=INF;
		for(int j=0;j<N;j++) if(used[j]) mn=min(mn,c[j]);
		ll d=mn-ans+1;
		if(a[v]+d<=M) d+=gen.uniform<int>(0,9);
		else d=-gen.uniform<int>(0,a[v]);
		Set(v,a[v]+d,i);
	}
	a=a_;
}