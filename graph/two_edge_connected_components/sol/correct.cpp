#include <cstdio>
#include <vector>
using namespace std;

struct LowLink{
  int n,pos;
  vector<int> ord,low,par,blg;
  vector<vector<int>> G,C;

  LowLink(int n):n(n),pos(0),ord(n,-1),low(n),
                 par(n,-1),blg(n,-1),G(n){}

  void add_edge(int u,int v){
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  bool is_bridge(int u,int v){
    if(ord[u]>ord[v]) swap(u,v);
    return ord[u]<low[v];
  }

  void dfs(int v){
    ord[v]=low[v]=pos++;
    int cnt=0;
    for(int u:G[v]){
      if(u==par[v]&&cnt==0){
        cnt++;
        continue;
      }
      if(~ord[u]){
        low[v]=min(low[v],ord[u]);
        continue;
      }
      par[u]=v;
      dfs(u);
      low[v]=min(low[v],low[u]);
    }
  }

  void fill_component(int v){
    C[blg[v]].emplace_back(v);
    for(int u:G[v]){
      if(~blg[u]||is_bridge(u,v)) continue;
      blg[u]=blg[v];
      fill_component(u);
    }
  }

  void add_component(int v,int &k){
    if(~blg[v]) return;
    blg[v]=k++;
    C.emplace_back();
    fill_component(v);
  }

  int build(){
    for(int i=0;i<n;i++)
      if(ord[i]<0) dfs(i);

    int k=0;
    for(int i=0;i<n;i++) add_component(i,k);
    return k;
  }
};

signed main(){
  int n,m;
  (void)scanf("%d %d",&n,&m);

  LowLink G(n);
  for(int i=0;i<m;i++){
    int a,b;
    (void)scanf("%d %d",&a,&b);
    G.add_edge(a,b);
  }

  int k=G.build();
  printf("%d\n",k);
  for(int i=0;i<k;i++){
    printf(" %d",(int)G.C[i].size());
    for(int v:G.C[i]) printf(" %d",v);
    puts("");
  }
  return 0;
}
