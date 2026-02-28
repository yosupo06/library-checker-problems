
#include <vector>
#include <queue>
#include <utility>
#include <optional>
#include <algorithm>
#include <cstdio>

struct ShortestPathProblemDirected {
  //using Weight = long long;
  using Weight = double;
  struct Edge { int from, to, id; Weight w; };
  int n;
  Weight inf;
  Weight zero;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> inc;
  int s;
  int t;

  ShortestPathProblemDirected(int _n, Weight _inf, Weight _zero, int _s, int _t)
    : n(_n), inf(_inf), zero(_zero), edges(), inc(_n), s(_s), t(_t) {}

  int addEdge(int from, int to, Weight w){
    int e = edges.size();
    edges.push_back({ from, to, e, w });
    inc[from].push_back(e);
    return e;
  }

  std::vector<int> solve(const std::vector<bool>& edgeMask){
    if(s == t) return {};
    std::vector<Weight> dist(n, inf);
    std::vector<int> parent(n, -1);
    using Node = std::pair<Weight, int>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> que;
    auto check = [&](int v, int p, Weight d) -> void {
      if(!(d < dist[v])) return;
      dist[v] = d;
      parent[v] = p;
      que.push({ d, v });
    };
    check(s, -1, zero);
    while(que.size()){
      auto [d, v] = que.top(); que.pop();
      if(dist[v] < d) continue;
      for(int e : inc[v]) if(edgeMask[e]){
        check(edges[e].to, e, d + edges[e].w);
      }
    }
    if(parent[t] == -1) return {};
    std::vector<int> path;
    for(int v=t; v!=s; v=edges[path.back()].from){
      path.push_back(parent[v]);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }

  struct Instance {
    ShortestPathProblemDirected* data;
    std::vector<bool> edgeMask;
    int rank;
    Weight wt;
    std::vector<int> path;

    Instance(ShortestPathProblemDirected* _data, std::vector<bool> _edgeMask, int _rank)
      : data(_data), edgeMask(_edgeMask), rank(_rank) {}

    bool solve(){
      path = data->solve(edgeMask);
      if(path.empty()) return false;
      wt = data->zero;
      for(int e : path) wt += data->edges[e].w;
      return true;
    }

    std::vector<Instance> split() const {
      std::vector<Instance> res;
      std::vector<bool> nextEdgeMask = edgeMask;
      for(int s=rank; s<(int)path.size(); s++){
        nextEdgeMask[path[s]] = false;
        Instance inst(data, nextEdgeMask, s);
        if(inst.solve()) res.push_back(std::move(inst));
        for(int e : data->inc[data->edges[path[s]].from]) nextEdgeMask[e] = false;
        nextEdgeMask[path[s]] = true;
      }
      return res;
    }
  };

  struct CmpWt {
    bool operator()(const Instance& l, const Instance& r){
      return r.wt < l.wt;
    }
  };

  std::priority_queue<Instance, std::vector<Instance>, CmpWt> que;
  bool KthStarted = false;

  std::optional<Weight> getNextSmallest(){
    if(!KthStarted){
      KthStarted = true;
      Instance inst(this, std::vector<bool>(edges.size(), true), 0);
      if(inst.solve()) que.push(std::move(inst));
    }
    else {
      if(que.empty()) return std::nullopt;
      auto h = que.top().split(); que.pop();
      for(auto& nx : h) que.push(std::move(nx));
    }

    if(que.empty()) return std::nullopt;
    return que.top().wt;
  }
};


int main(){
  int N, M, s, t, K;
  scanf("%d%d%d%d%d", &N, &M, &s, &t, &K);

  ShortestPathProblemDirected graph(N, (1ll << 60), 0, s, t);
  for(int i=0; i<M; i++){
    int u, v; long long c; scanf("%d%d%lld", &u, &v, &c);
    graph.addEdge(u, v, c);
  }

  for(int k=0; k<K; k++){
    auto path = graph.getNextSmallest();
    if(path.has_value()){
      long long wt = *path;
      printf("%lld\n", wt);
    } else {
      printf("-1\n");
    }
  }
  return 0;
}
