#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <cassert>
#include <algorithm>

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
	//incorrect recovery (not necessarily induced)
	std::vector<int> p1({y}),p2({z});
	while(!adj[p1.back()].count(p2.back())){
	  if(index[p1.back()]>index[p2.back()]){
	    p1.swap(p2);
	  }
	  int v=p2.back();
	  //there must exist w such that index[w]<index[v] and w is adjacent to v but not x
	  //otherwise MCS would've picked x instead of v
	  int ext=-1;
	  for(int w:adj[v]){
	    if(index[w]<index[v]&&adj[v].count(w)&&!adj[x].count(w)){
	      ext=w;
	      break;
	    }
	  }
	  assert(ext!=-1);
	  p2.push_back(ext);
	}
	printf("NO\n");
	printf("%d\n",(int)p1.size()+(int)p2.size()+1);
	for(int u:p2){
	  printf("%d ",u);
	}
	std::reverse(p1.begin(),p1.end());
	for(int u:p1){
	  printf("%d ",u);
	}
	printf("%d\n",x);
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
