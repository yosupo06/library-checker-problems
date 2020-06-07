#include<iostream>
#include<vector>
#include<tuple>
#include<queue>
using namespace::std;
using lint=long long;
constexpr lint INF=1LL<<60;
 
template<typename T>
struct heap{
	struct node{
		node* ch[2]={0,0};
		int s;
		T val;
		int from,to;
		node(T val,int from,int to):s(1),val(val),from(from),to(to){}
	};
	using np=node*;
	np root=0;
	heap(np t=0):root(t){}
	np meld(np a,np b){
		if(!b)return a?new node(*a):0;
		if(!a)return b?new node(*b):0;
		a=new node(*a);b=new node(*b);
		if(a->val>b->val)swap(a,b);
		a->ch[1]=meld(a->ch[1],b);
		if(!a->ch[0]||a->ch[0]->s<a->ch[1]->s)swap(a->ch[0],a->ch[1]);
		a->s=(a->ch[1]?a->ch[1]->s:0)+1;
		return a;
	}
	heap meld(heap b){
		return heap(meld(root,b.root));
	}
	heap insert(T x,int from,int to){
		return heap(meld(root,new node(x,from,to)));
	}
	heap pop(){
		return heap(meld(root->ch[0],root->ch[1]));
	}
	T top(){
		return root?root->val:T(-1);
	}
	bool empty(){
		return !root;
	}
};
 
int main(){
	lint n,m,k;
	scanf("%lld%lld%lld",&n,&m,&k);
	lint x,y;
	scanf("%lld%lld",&x,&y);
	vector<vector<tuple<lint,lint,lint>>>g(n);
	vector<vector<tuple<lint,lint,lint>>>g2(n);
	for(lint i=0;i<m;++i){
		lint s,t,c;
		scanf("%lld%lld%lld",&s,&t,&c);
		g[t].emplace_back(s,c,i);
		g2[s].emplace_back(t,c,i);
	}
	vector<lint>p(n,INF);
	vector<lint>par(n,-1);
	vector<lint>idx(n,-1);
	vector<vector<lint>>ch(n);
	priority_queue<pair<lint,lint>,vector<pair<lint,lint>>,greater<pair<lint,lint>>>que;
	que.emplace(0,y);
	p[y]=0;
	while(!que.empty()){
		lint t,n;
		tie(t,n)=que.top();
		que.pop();
		for(auto d:g[n]){
			lint e,c,id;
			tie(e,c,id)=d;
			if(p[e]>t+c){
				p[e]=t+c;
				par[e]=n;
				idx[e]=id;
				que.emplace(p[e],e);
			}
		}
	}
	for(lint i=0;i<n;++i){
		if(par[i]!=-1)ch[par[i]].push_back(i);
	}
	vector<heap<lint>>h(n);
	for(lint i=0;i<n;++i)h[i]=heap<lint>();
	queue<lint>qq;
	qq.emplace(y);
	while(!qq.empty()){
		auto n=qq.front();
		qq.pop();
		if(par[n]!=-1)h[n]=h[n].meld(h[par[n]]);
		for(auto d:g2[n]){
			lint e,c,id;
			tie(e,c,id)=d;
			if(id!=idx[n])h[n]=h[n].insert(c-p[n]+p[e],n,e);
		}
		for(auto e:ch[n]){
			qq.emplace(e);
		}
	}
	auto comp=[](auto s,auto t){return get<0>(s)>get<0>(t);};
	priority_queue<tuple<lint,heap<lint>::np>,vector<tuple<lint,heap<lint>::np>>,decltype(comp)>qqq(comp);
	heap<lint>s;
	s=s.insert(p[x],-1,x);
	qqq.emplace(p[x],s.root);
	vector<lint>ans;
	while(!qqq.empty()){
		lint t;
		heap<lint>::np now;
		tie(t,now)=qqq.top();
		qqq.pop();
		if(t==INF)break;
		ans.push_back(t);
		if(int(ans.size())==k)break;
		if(now->ch[0]){
			qqq.emplace(t+now->ch[0]->val-now->val,now->ch[0]);
		}
		if(now->ch[1]){
			qqq.emplace(t+now->ch[1]->val-now->val,now->ch[1]);
		}
		if(h[now->to].root){
			qqq.emplace(t+h[now->to].root->val,h[now->to].root);
		}
	}
	for(lint i=0;i<k;++i){
		if(i<(int)ans.size())cout<<ans[i]<<endl;
		else cout<<-1<<endl;
	}
}