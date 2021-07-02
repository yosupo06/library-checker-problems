#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

struct LowLink{
  vector<int> ord,low,par;
  vector<vector<pair<int, int>>> G;

  stack<int> cand;
  vector<vector<int>> E;

  LowLink(int n):ord(n,-1),low(n),par(n,-1),G(n){}

  void add_edge(int u,int v,int idx){
    G[u].emplace_back(v,idx);
    G[v].emplace_back(u,idx);
  }

  bool is_bridge(int u,int v){
    if(ord[u]>ord[v]) swap(u,v);
    return ord[u]<low[v];
  }

  void dfs(int v,int &pos){
    ord[v]=low[v]=pos++;
    for(auto edge:G[v]){
      int u=edge.first;
      if(u==par[v]) continue;

      if(ord[u]<ord[v])
        cand.emplace(edge.second);

      if(~ord[u]){
        low[v]=min(low[v],ord[u]);
        continue;
      }

      par[u]=v;
      dfs(u,pos);
      low[v]=min(low[v],low[u]);

      if(low[u]>=ord[v]){
        E.emplace_back();
        while(1){
          auto e=cand.top();cand.pop();
          E.back().emplace_back(e);
          if(e==edge.second) break;
        }
      }
    }
  }

  int build(){
    int n=G.size(),pos=0;
    for(int i=0;i<n;i++)
      if(ord[i]<0) dfs(i,pos);
    return E.size();
  }
};

signed main(){
  int n,m;
  (void)scanf("%d %d",&n,&m);

  LowLink G(n);
  for(int i=0;i<m;i++){
    int a,b;
    (void)scanf("%d %d",&a,&b);
    G.add_edge(a,b,i);
  }

  int k=G.build();
  printf("%d\n",k);
  for(int i=0;i<k;i++){
    printf("%d",(int)G.E[i].size());
    for(int v:G.E[i]) printf(" %d",v);
    puts("");
  }
  return 0;
}
