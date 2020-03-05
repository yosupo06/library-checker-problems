#include<iostream>
#include<vector>
#include<tuple>
#include<unordered_map>
#include<unordered_set>
#include<functional>
#include<assert.h>
using namespace::std;
using lint=long long;
#define rep(i,n) for(lint (i)=0;(i)<lint(n);(i)++)
template<typename T>
class dynamic_connectivity{
	class euler_tour_tree{
		public:
		struct node;
		using np=node*;
		using lint=long long;
		struct node{
			np ch[2]={nullptr,nullptr};
			np p=nullptr;
			int l,r,sz,sz2;
			T val=et,sum=et;
			bool exact=1;
			bool child_exact;
			bool edge_connected=0;
			node(){}
			node(int l,int r):l(l),r(r),sz(l==r),sz2(0),child_exact(l<r){}
			bool is_root() {
				return !p;
			}
		};
		vector<unordered_map<int,np>>ptr;
		np get_node(int l,int r){
			if(ptr[l].find(r)==ptr[l].end())ptr[l][r]=new node(l,r);
			return ptr[l][r];
		}
		np root(np t){
			if(!t)return t;
			while(t->p)t=t->p;
			return t;
		}
		bool same(np s,np t){
			if(s)splay(s);
			if(t)splay(t);
			return root(s)==root(t);
		}
		np reroot(np t){
			auto s=split(t);
			return merge(s.second,s.first);
		}
		pair<np,np> split(np s){
			splay(s);
			np t=s->ch[0];
			if(t)t->p=nullptr;
			s->ch[0]=nullptr;
			return {t,update(s)};
		}
		pair<np,np> split2(np s){
			splay(s);
			np t=s->ch[0];
			np u=s->ch[1];
			if(t)t->p=nullptr;
			s->ch[0]=nullptr;
			if(u)u->p=nullptr;
			s->ch[1]=nullptr;
			return {t,u};
		}
		tuple<np,np,np> split(np s,np t){
			auto u=split2(s);
			if(same(u.first,t)){
				auto r=split2(t);
				return make_tuple(r.first,r.second,u.second);
			}else{
				auto r=split2(t);
				return make_tuple(u.first,r.first,r.second);
			}
		}
		template<typename First, typename... Rest>
		np merge(First s,Rest... t){
			return merge(s,merge(t...));
		}
		np merge(np s,np t){
			if(!s)return t;
			if(!t)return s;
			while(s->ch[1])s=s->ch[1];
			splay(s);
			s->ch[1]=t;
			if(t)t->p=s;
			return update(s);
		}
		int size(np t){return t?t->sz:0;}
		int size2(np t){return t?t->sz2:0;}
		np update(np t){
			t->sum=et;
			if(t->ch[0])t->sum=fn(t->sum,t->ch[0]->sum);
			if(t->l==t->r)t->sum=fn(t->sum,t->val);
			if(t->ch[1])t->sum=fn(t->sum,t->ch[1]->sum);
			t->sz=size(t->ch[0])+(t->l==t->r)+size(t->ch[1]);
			t->sz2=size2(t->ch[0])+(t->edge_connected)+size2(t->ch[1]);
			t->child_exact=(t->ch[0]?t->ch[0]->child_exact:0)|(t->l<t->r&&t->exact)|(t->ch[1]?t->ch[1]->child_exact:0);
			return t;
		}
		// void push(np t){
		// 	//遅延評価予定
		// }
		void rot(np t,bool b){
			np x=t->p,y=x->p;
			if((x->ch[1-b]=t->ch[b]))t->ch[b]->p=x;
			t->ch[b]=x,x->p=t;
			update(x);update(t);
			if((t->p=y)){
				if(y->ch[0]==x)y->ch[0]=t;
				if(y->ch[1]==x)y->ch[1]=t;
				update(y);
			}
		}
		void splay(np t){
			//push(t);
			while(!t->is_root()){
				np q=t->p;
				if(q->is_root()){
					//push(q), push(t);
					rot(t,q->ch[0]==t);
				}else{
					np r=q->p;
					//push(r), push(q), push(t);
					bool b=r->ch[0]==q;
					if(q->ch[1-b]==t)rot(q,b),rot(t,b);
					else rot(t,1-b),rot(t,b);
				}
			}
		}
		void debug(np t){
			if(!t)return;
			debug(t->ch[0]);
			cerr<<t->l<<"-"<<t->r<<" ";
			debug(t->ch[1]);
		}
		constexpr static T et=T();
		constexpr static T fn(T s,T t){
			return s+t;
		}
		public:
		euler_tour_tree(){}
		euler_tour_tree(int sz){
			ptr.resize(sz);
			for(int i=0;i<sz;i++)ptr[i][i]=new node(i,i);
		}
		int size(int s){
			np t=get_node(s,s);
			splay(t);
			return t->sz;
		}
		bool same(int s,int t){
			return same(get_node(s,s),get_node(t,t));
		}
		void set_size(int sz){
			ptr.resize(sz);
			for(int i=0;i<sz;i++)ptr[i][i]=new node(i,i);
		}
		void update(int s,T x){
			np t=get_node(s,s);
			splay(t);
			t->val=fn(t->val,x);
			update(t);
		}
		void edge_update(int s,function<void(int,int)> g){
			np t=get_node(s,s);
			splay(t);
			function<void(np)>dfs=[&](np t){
				assert(t);
				if(t->l<t->r&&t->exact){
					splay(t);
					t->exact=0;
					update(t);
					g(t->l,t->r);
					return;
				}
				if(t->ch[0]&&t->ch[0]->child_exact)dfs(t->ch[0]);
				else dfs(t->ch[1]);
			};
			while(t&&t->child_exact){
				dfs(t);
				splay(t);
			}
		}
		bool try_reconnect(int s,function<bool(int)> f){
			np t=get_node(s,s);
			splay(t);
			function<bool(np,int)>dfs=[&](np t,int idx)->bool{
				assert(t);
				if(t->edge_connected&&(size2(t->ch[0])==idx)){
					splay(t);
					return f(t->l);
				}
				if(idx<size2(t->ch[0]))return dfs(t->ch[0],idx);
				else return dfs(t->ch[1],idx-size2(t->ch[0])-(t->edge_connected));
			};
			while(size2(t)){
				if(dfs(t,0))return 1;
				splay(t);
			}
			return 0;
		}
		void edge_connected_update(int s,bool b){
			np t=get_node(s,s);
			splay(t);
			t->edge_connected=b;
			update(t);
		}
		bool link(int l,int r){
			if(same(l,r))return 0;
			merge(reroot(get_node(l,l)),get_node(l,r),reroot(get_node(r,r)),get_node(r,l));
			return 1;
		}
		bool cut(int l,int r){
			if(ptr[l].find(r)==ptr[l].end())return 0;
			np s,t,u;
			tie(s,t,u)=split(get_node(l,r),get_node(r,l));
			merge(s,u);
			np p=ptr[l][r];
			np q=ptr[r][l];
			ptr[l].erase(r);
			ptr[r].erase(l);
			delete p;delete q;
			return 1;
		}
		T get_sum(int p,int v){
			cut(p,v);
			np t=get_node(v,v);
			splay(t);
			T res=t->sum;
			link(p,v);
			return res;
		}
		T get_sum(int s){
			np t=get_node(s,s);
			splay(t);
			return t->sum;
		}
	};
	int dep=1;
	vector<euler_tour_tree> ett;
	vector<vector<unordered_set<int>>>edges;
	int sz;
	public:
	dynamic_connectivity(int sz):sz(sz){
		ett.emplace_back(sz);
		edges.emplace_back(sz);
	}
	bool link(int s,int t){
		if(s==t)return 0;
		if(ett[0].link(s,t))return 1;
		edges[0][s].insert(t);
		edges[0][t].insert(s);
		if(edges[0][s].size()==1)ett[0].edge_connected_update(s,1);
		if(edges[0][t].size()==1)ett[0].edge_connected_update(t,1);
		return 0;
	}
	bool same(int s,int t){
		return ett[0].same(s,t);
	}
	int size(int s){
		return ett[0].size(s);
	}
	vector<int>get_vertex(int s){
		return ett[0].vertex_list(s);
	}
	void update(int s,T x){
		ett[0].update(s,x);
	}
	T get_sum(int s){
		return ett[0].get_sum(s);
	}
	bool cut(int s,int t){
		if(s==t)return 0;
		for(int i=0;i<dep;i++){
			edges[i][s].erase(t);
			edges[i][t].erase(s);
			if(edges[i][s].size()==0)ett[i].edge_connected_update(s,0);
			if(edges[i][t].size()==0)ett[i].edge_connected_update(t,0);
		}
		for(int i=dep-1;i>=0;i--){
			if(ett[i].cut(s,t)){
				if(dep-1==i){
					dep++;
					ett.emplace_back(sz);
					edges.emplace_back(sz);
				}
				return !try_reconnect(s,t,i);
			}
		}
		return 0;
	}
	bool try_reconnect(int s,int t,int k){
		for(int i=0;i<k;i++){
			ett[i].cut(s,t);
		}
		for(int i=k;i>=0;i--){
			if(ett[i].size(s)>ett[i].size(t))swap(s,t);
			function<void(int,int)> g=[&](int s,int t){ett[i+1].link(s,t);};
			ett[i].edge_update(s,g);
			function<bool(int)> f=[&](int x)->bool{
				for(auto itr=edges[i][x].begin();itr!=edges[i][x].end();){
					auto y=*itr;
					itr=edges[i][x].erase(itr);
					edges[i][y].erase(x);
					if(edges[i][x].size()==0)ett[i].edge_connected_update(x,0);
					if(edges[i][y].size()==0)ett[i].edge_connected_update(y,0);
					if(ett[i].same(x,y)){
						edges[i+1][x].insert(y);
						edges[i+1][y].insert(x);
						if(edges[i+1][x].size()==1)ett[i+1].edge_connected_update(x,1);
						if(edges[i+1][y].size()==1)ett[i+1].edge_connected_update(y,1);
					}else{
						for(int j=0;j<=i;j++){
							ett[j].link(x,y);
						}
						return 1;
					}
				}
				return 0;
			};
			if(ett[i].try_reconnect(s,f))return 1;
		}
		return 0;
	}
};

int main(){
	lint n,k;
	scanf("%lld %lld",&n,&k);
	dynamic_connectivity<lint>dc(n);
	rep(i,n){
		lint x;
		scanf("%lld",&x);
		dc.update(i,x);
	}
	rep(i,k){
		lint x;
		scanf("%lld",&x);
		if(x==0){
			lint u,v;
			scanf("%lld %lld",&u,&v);
			dc.link(u,v);
		}
		if(x==1){
			lint u,v;
			scanf("%lld %lld",&u,&v);
			dc.cut(u,v);
		}
		if(x==2){
			lint v,x;
			scanf("%lld %lld",&v,&x);
			dc.update(v,x);
		}
		if(x==3){
			lint v;
			scanf("%lld",&v);
			printf("%lld\n",dc.get_sum(v));
		}
	}
}
