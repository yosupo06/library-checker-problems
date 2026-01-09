
#include <vector>
#include <queue>
#include <utility>
#include <optional>
#include <algorithm>
#include <cstdio>

struct ShortestPathProblemUndirected {
  using Weight = long long;
  struct Edge { int u, v, uv, id; Weight w; };
  int n;
  Weight inf;
  Weight zero;
  std::vector<Edge> edges;
  std::vector<std::vector<int>> inc;
  int s;
  int t;

  ShortestPathProblemUndirected(int _n, Weight _inf, Weight _zero, int _s, int _t)
    : n(_n), inf(_inf), zero(_zero), edges(), inc(_n), s(_s), t(_t) {}

  int addEdge(int u, int v, Weight w){
    int e = edges.size();
    edges.push_back({ u, v, u ^ v, e, w });
    inc[u].push_back(e);
    inc[v].push_back(e);
    return e;
  }

  struct ShortestPathTree {
    std::vector<int> parent;
    std::vector<Weight> dist;
    std::vector<int> root;
    void resize(int n, Weight inf){
      parent.resize(n, -1);
      dist.resize(n, inf);
      root.resize(n, -1);
    }
  };

  void updateTree(const std::vector<bool>& edgeMask, ShortestPathTree& tree){
    ShortestPathTree t; std::swap(t, tree);
    using Node = std::pair<Weight, int>;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> que;
    auto check = [&](int v, int p, int r, Weight d) -> void {
      if(!(d < t.dist[v])) return;
      t.dist[v] = d;
      t.parent[v] = p;
      t.root[v] = r;
      que.push({ d, v });
    };
    for(int v=0; v<n; v++) if(t.root[v] != -1) que.push({t.dist[v], v});
    while(que.size()){
      auto [d, v] = que.top(); que.pop();
      if(t.dist[v] < d) continue;
      for(int e : inc[v]) if(edgeMask[e]){
        check(v ^ edges[e].uv, e, t.root[v], d + edges[e].w);
      }
    }
    std::swap(t, tree);
  }

  std::vector<int> getPath(const ShortestPathTree& t, int start){
    std::vector<int> path;
    for(int v=start; t.root[v]!=v; v^=edges[path.back()].uv){
      if(t.parent[v] < 0) return {};
      path.push_back(t.parent[v]);
    }
    std::reverse(path.begin(), path.end());
    return path;
  }

  ShortestPathTree solve(const std::vector<bool>& edgeMask){
    ShortestPathTree tree; tree.resize(n, inf);
    tree.root[s] = s;
    tree.dist[s] = zero;
    updateTree(edgeMask, tree);
    return tree;
  }

  struct Instance {
    ShortestPathProblemUndirected* data;
    std::vector<bool> edgeMask;
    Weight wt;
    std::vector<int> path;
    std::vector<std::pair<int, Weight>> cand;
    int lim;

    struct SplitResult {
      std::vector<int> path;
      std::vector<Instance> newInstances;
    };

    // `edgeMask` : 使用できる辺に 1 、使用禁止する辺に 0 を設定する。
    // Instance は、 `edgeMask` の条件下における s-t 単純パスのうち最短パス以外を探索空間として管理する。
    Instance(ShortestPathProblemUndirected* _data, std::vector<bool> _edgeMask)
      : data(_data), edgeMask(_edgeMask) {}

    // 更新される変数 `path`
    //    `path` : 最短パスの辺列。このパスは探索空間から除かれる。
    bool solve(){
      auto tree = data->solve(edgeMask);
      path = data->getPath(tree, data->t);
      if(path.empty()) return false;
      lim = path.size();
      return true;
    }

    // 更新される変数 `cand`, `wt`
    //    `cand` : 分岐地点の候補と、それぞれの場合の最短パスの重み。
    //             分岐地点は、配列 `path` における位置で表す。
    //             各要素 (v,w) は、頂点 v で分岐した場合の最短パスの重みが w であり、
    //             v よりも前で分岐して重みがそれ以下のパスを得られないことを表す。
    //             最後の要素が、 `edgeMask` の条件下における全体の第二最短パスを表す。
    //    `wt` : 第二最短パス長の重み。
    //
    // 参考: https://noshi91.hatenablog.com/entry/2024/10/14/164225
    bool solve2nd(){
      ShortestPathTree treeS, treeT;
      treeS.resize(data->n, data->inf);
      treeT.resize(data->n, data->inf);
      int pathLen = path.size();
      std::vector<int> pathVtx(pathLen + 1);
      pathVtx[0] = data->s;
      for(int i=0; i<pathLen; i++) pathVtx[i+1] = pathVtx[i] ^ data->edges[path[i]].uv;

      for(int h : {data->s, data->t}){
        treeS.dist[h] = data->zero;
        treeS.root[h] = h;
        for(int i=0; i<pathLen; i++){
          auto e = data->edges[path[i]];
          treeS.root[pathVtx[i+1]] = pathVtx[i+1];
          treeS.dist[pathVtx[i+1]] = treeS.dist[pathVtx[i]] + e.w;
        }
        data->updateTree(edgeMask, treeS);
        std::swap(treeS, treeT);
        std::reverse(path.begin(), path.end());
        std::reverse(pathVtx.begin(), pathVtx.end());
      }
      std::vector<int> mainPath(data->edges.size(), -1);
      for(int i=0; i<pathLen; i++) mainPath[path[i]] = i;
      std::vector<int> mainPathVtx(data->n, -1);
      for(int i=0; i<=pathLen; i++) mainPathVtx[pathVtx[i]] = i;

      std::vector<Weight> nextWeight(pathLen, data->inf);
      for(int i=0; i<int(data->edges.size()); i++) if(edgeMask[i] && mainPath[i] == -1){
        auto e = data->edges[i];
        for(int t=0; t<2; t++){
          std::swap(e.u, e.v);
          if(treeS.root[e.u] < 0 || treeT.root[e.v] < 0) continue;
          if(mainPathVtx[treeS.root[e.u]] >= mainPathVtx[treeT.root[e.v]]) continue;
          Weight& dest = nextWeight[mainPathVtx[treeS.root[e.u]]];
          dest = std::min(dest, e.w + treeS.dist[e.u] + treeT.dist[e.v]);
        }
      }

      Weight minWeight = data->inf;
      for(int i=0; i<lim; i++) if(nextWeight[i] < minWeight){
        minWeight = nextWeight[i];
        cand.push_back({ i, minWeight });
      }
      wt = minWeight;
      return !cand.empty();
    }

    // src の探索空間中のパスのうち最短のパスを取得し、それ以外のパス全体をいくつかの Instance で表す。
    static SplitResult split(Instance src){
      SplitResult res;
      auto [rank, weight] = src.cand.back();
      src.cand.pop_back();

      // `rank` で分岐するパスのうち、今回取り出したもの以外 
      {
        auto nextEdgeMask = src.edgeMask;
        int p = src.data->s;
        // `rank` までは一直線
        for(int i=0; i<rank; i++){
          for(int e : src.data->inc[p]) nextEdgeMask[e] = false;
          p ^= src.data->edges[src.path[i]].uv;
        }
        for(int i=0; i<rank; i++) nextEdgeMask[src.path[i]] = true;
        // `rank` では、 `path` で使用した辺のみ禁止する
        nextEdgeMask[src.path[rank]] = false;
        Instance buf(src.data, std::move(nextEdgeMask));
        buf.solve();
        // この場合の最短パス (buf.path) が、 src の探索空間中の最短パスである
        res.path = buf.path;
        if(buf.solve2nd()) res.newInstances.push_back(std::move(buf));
      }

      // `rank` よりも後で分岐するパス
      {
        auto nextEdgeMask = src.edgeMask;
        int p = src.data->s;
        // `rank` を過ぎるまでは一直線
        for(int i=0; i<=rank; i++){
          for(int e : src.data->inc[p]) nextEdgeMask[e] = false;
          p ^= src.data->edges[src.path[i]].uv;
        }
        for(int i=0; i<=rank; i++) nextEdgeMask[src.path[i]] = true;
        // 最短パスとして src.path を指定することで、パスが重複しないようにする
        Instance buf(src.data, std::move(nextEdgeMask));
        buf.path = src.path;
        buf.lim = src.lim; // まだ分岐を決めていないので、分岐位置の制限は保存する
        if(buf.solve2nd()) res.newInstances.push_back(std::move(buf));
      }
      
      // `rank` よりも手間で分岐するパス
      if(src.cand.size()){
        src.wt = src.cand.back().second;
        // `rank` よりも手前で分岐するように制限する
        src.lim = rank;
        res.newInstances.push_back(std::move(src));
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

  std::optional<std::vector<int>> getNextSmallest(){
    if(!KthStarted){
      KthStarted = true;
      Instance inst(this, std::vector<bool>(edges.size(), true));
      if(!inst.solve()) return std::nullopt;
      auto res = inst.path;
      if(inst.solve2nd()) que.push(std::move(inst));
      return res;
    }
    if(que.empty()) return std::nullopt;
    auto h = Instance::split(que.top()); que.pop();
    for(auto& nx : h.newInstances) que.push(std::move(nx));
    return h.path;
  }
};


int main(){
  int N, M, s, t, K;
  scanf("%d%d%d%d%d", &N, &M, &s, &t, &K);

  ShortestPathProblemUndirected graph(N, (1ll << 60), 0, s, t);
  for(int i=0; i<M; i++){
    int u, v; long long c; scanf("%d%d%lld", &u, &v, &c);
    graph.addEdge(u, v, c);
  }

  for(int k=0; k<K; k++){
    auto path = graph.getNextSmallest();
    if(path.has_value()){
      long long wt = 0;
      for(int e : *path) wt += graph.edges[e].w;
      printf("%lld\n", wt);
    } else {
      printf("-1\n");
    }
  }
  return 0;
}
