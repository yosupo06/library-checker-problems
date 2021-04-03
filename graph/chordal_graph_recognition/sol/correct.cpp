#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <cassert>

int main(){
  int N,M;
  scanf("%d %d",&N,&M);
  std::vector<std::set<int> > adj(N);
  for(int i=0;i<M;i++){
    int A,B;
    scanf("%d %d",&A,&B);
    adj[A].insert(B);
    adj[B].insert(A);
  }
  std::vector<int> in(N);
  std::set<std::pair<int,int> > pq;
  for(int i=0;i<N;i++){
    pq.insert({0,i});
  }
  std::vector<int> index(N);
  std::vector<int> ord;
  while(!pq.empty()){
    int x=pq.rbegin()->second;
    index[x]=ord.size();
    ord.push_back(x);
    pq.erase(*pq.rbegin());
    in[x]=-1;
    for(int y:adj[x]){
      if(in[y]==-1) continue;
      pq.erase({in[y],y});
      in[y]++;
      pq.insert({in[y],y});
    }
  }
  for(int x:ord){
    int prev=-1;
    for(int y:adj[x]){
      if(index[y]<index[x]&&index[y]>prev){
	prev=index[y];
      }
    }
    if(prev==-1) continue;
    int z=ord[prev];
    for(int y:adj[x]){
      if(index[y]<index[z]&&!adj[z].count(y)){
	//y--x--z
	//find shortest path from y to z without using x or its neighbors
	std::vector<int> dist(N,-1);
	std::vector<int> from(N,-1);
	std::queue<int> q;
	dist[y]=0;
	q.push(y);
	while(!q.empty()){
	  int u=q.front();
	  q.pop();
	  for(int v:adj[u]){
	    if(v==x||((v!=z)&&adj[x].count(v))) continue;
	    if(dist[v]==-1){
	      dist[v]=dist[u]+1;
	      from[v]=u;
	      q.push(v);
	    }
	  }
	}
	assert(dist[z]!=-1);
	printf("NO\n");
	printf("%d\n",dist[z]+2);
	for(int u=z;u!=y;u=from[u]){
	  printf("%d ",u);
	}
	printf("%d %d\n",y,x);
	return 0;
      }
    }
  }
  printf("YES\n");
  for(int i=0;i<N;i++){
    if(i) printf(" ");
    printf("%d",ord[N-1-i]);
  }
  printf("\n");
}
