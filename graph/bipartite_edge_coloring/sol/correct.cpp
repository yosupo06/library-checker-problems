#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <deque>
#include <assert.h>
#include <random>
#include <utility>
#include <time.h>

struct djset {
  std::vector<int> upper;
  std::vector<int> id;
  int n;
  djset(int n_) {
    n=n_;
    upper.resize(n);
    id.resize(n);
    for (int i=0;i<n;++i) upper[i]=-1;
  }
  int root(int x) {
    return upper[x]<0?x:(upper[x]=root(upper[x]));
  }
  bool equiv(int x,int y) {
    return root(x)==root(y);
  }
  void unite(int x,int y) {
    x=root(x);y=root(y);
    if (x==y) return;
    if (upper[x]<upper[y]) std::swap(x,y);
    upper[y]+=upper[x];
    upper[x]=y;
  }
  void build_id() {
    for (int i=0,p=0;i<n;++i) if (i==root(i)) id[i]=p++;
  }
  int components() {
    int e=0;
    for (int i=0;i<n;++i) if (i==root(i)) ++e;
    return e;
  }
};

struct edge {
  int dst=-1;
  int rev=-1;
  int cnt=1;
  int col=-1;
  int id=-1;// -1 ならば bad edge
};

struct vertex {
  int next_edge=0;
  int id;
  std::vector<edge> edges;
};

void add_edge(vertex &a,vertex &b,int col,int cnt,int id) {
  if (cnt==0) return;
  edge ab;
  edge ba;
  ab.dst=b.id;
  ba.dst=a.id;
  ab.rev=b.edges.size();
  ba.rev=a.edges.size();
  ab.col=col;
  ba.col=col;
  ab.cnt=cnt;
  ba.cnt=cnt;
  ab.id=id;
  ba.id=id;
  a.edges.push_back(ab);
  b.edges.push_back(ba);
}

int max_deg(std::vector<vertex> &vs){
  int deg=0;
  for (vertex &v:vs) {
    int sum=0;
    for (edge &e:v.edges) sum+=e.cnt;
    deg=std::max(deg,sum);
  }
  return deg;
}

int bad_edge(std::vector<vertex> &vs) {
  int ret=0;
  for (vertex &v:vs) for (edge &e:v.edges) if (e.id==-1) ++ret;
  return ret;
}

void divide_edge(std::vector<vertex> &v0,std::vector<vertex> &v1,int a,int b,edge &e) {
  add_edge(v0[a],v0[b],e.col,(e.cnt+1)/2,e.id);
  add_edge(v1[a],v1[b],e.col,e.cnt/2,e.id);
}

void divide(std::vector<vertex> &vs,std::vector<vertex> &v0,std::vector<vertex> &v1) {
  assert(max_deg(vs)%2==0);
  std::vector<std::vector<bool>> vis;
  for (int i=0;i<(int)vs.size();++i) {
    vis.push_back(std::vector<bool>(vs[i].edges.size(),false));
  }
  for (int i=0;i<(int)vs.size();++i) {
    int cur=i;
    int parity=0;
    while (vs[i].next_edge!=(int)vs[i].edges.size()) {
      edge e=vs[cur].edges[vs[cur].next_edge];
      if (vis[cur][vs[cur].next_edge]) {
        ++vs[cur].next_edge;
        continue;
      }
      if (e.cnt%2==0) {
        divide_edge(v0,v1,cur,e.dst,e);
        vis[e.dst][e.rev]=true;
        ++vs[cur].next_edge;
      } else {
        if (parity==0) divide_edge(v0,v1,cur,e.dst,e);
        else divide_edge(v1,v0,cur,e.dst,e);
        vis[e.dst][e.rev]=true;
        ++vs[cur].next_edge;
        cur=e.dst;
        parity^=1;
      }
    }
  }
}

std::vector<int> find_matching(std::vector<vertex> vs) {
  int n=(int)vs.size(),m=0,M=1;
  for (vertex v:vs) m+=v.edges.size();
  while (M<m) M*=2;
  for (int i=0;i<n/2;++i) {
    int k=vs[i].edges.size();
    for (edge &e:vs[i].edges) {
      e.cnt=M/k;
      vs[e.dst].edges[e.rev].cnt=e.cnt;
    }
    add_edge(vs[i],vs[i+n/2],-1,M%k,-1);
  }

  while (max_deg(vs)>1) {
    std::vector<vertex> v0(n);
    std::vector<vertex> v1(n);
    for (int i=0;i<n;++i) {
      v0[i].id=i;
      v1[i].id=i;
    }
    divide(vs,v0,v1);
    if (bad_edge(v0) <= bad_edge(v1)) {
      vs=v0;
    } else {
      vs=v1;
    }
  }
  std::vector<int> matching;
  for (vertex &v:vs) for (edge &e:v.edges) {
      if (v.id<e.dst) matching.push_back(e.id);
    }
  return matching;
}

void delete_edges(std::vector<vertex> &vs,std::vector<int> delete_edges) {
  std::vector<vertex> ret(vs.size());
  for (int i=0;i<(int)ret.size();++i) ret[i].id=i;
  std::set<int> s;
  for (int &id:delete_edges) s.insert(id);
  for (vertex &v:vs) for (edge &e:v.edges) {
      if (v.id>e.dst) continue;
      if (s.count(e.id)!=0) {
        --e.cnt;
        s.erase(e.id);
      }
      add_edge(ret[v.id],ret[e.dst],e.col,e.cnt,e.id);
    }
  vs=ret;
}

std::vector<std::pair<int,int>> colorize2(std::vector<vertex> &vs,int offset=0) {
  int D=max_deg(vs);
  if (D==1) {
    std::vector<std::pair<int,int>> ret;
    for (vertex &v:vs) for (edge &e:v.edges) {
        if (v.id>e.dst) continue;
        ret.push_back(std::make_pair(e.id,offset));
      }
    return ret;
  }
  std::vector<vertex> v0(vs.size());
  std::vector<vertex> v1(vs.size());
  for (int i=0;i<(int)vs.size();++i) {
    v0[i].id=i;
    v1[i].id=i;
  }
  divide(vs,v0,v1);
  std::vector<std::pair<int,int>> ans0=colorize2(v0,offset);
  std::vector<std::pair<int,int>> ans1=colorize2(v1,offset+D/2);
  for (std::pair<int,int> &p:ans0) {
    ans1.push_back(p);
  }
  return ans1;
}

std::vector<std::pair<int,int>> colorize(std::vector<vertex> vs,int offset=0) {
  int D=max_deg(vs);
  if (D==0) return std::vector<std::pair<int,int>>();
  else if (D%2==0) {
    int D2=1;
    while (D2<D/2) D2*=2;
    std::vector<vertex> v0(vs.size());
    std::vector<vertex> v1(vs.size());
    for (int i=0;i<(int)vs.size();++i) {
      v0[i].id=i;
      v1[i].id=i;
    }
    divide(vs,v0,v1);
    std::vector<std::pair<int,int>> ans0=colorize(v0,offset);
    std::set<int> invalid;
    for (auto &p:ans0) {
      assert(p.second<offset+D/2);
      if (p.second-offset>=(int)(D/2-(D2-D/2))) {
        invalid.insert(p.first);
      }
    }
    for (vertex &v:v0) {
      for (edge &e:v.edges) {
        if (v.id>e.dst) continue;
        if (invalid.count(e.id)) {
          add_edge(v1[v.id],v1[e.dst],-1,1,e.id);
        }
      }
    }
    std::vector<std::pair<int,int>> ans1=colorize2(v1,offset+(D/2-(D2-D/2)));
    for (std::pair<int,int> &p:ans0) {
      if (invalid.count(p.first)==0) ans1.push_back(p);
    }
    return ans1;
  } else {
    std::vector<int> matching=find_matching(vs);
    std::vector<std::pair<int,int>> ans0;
    std::vector<std::pair<int,int>> ans1;
    for (int &id:matching) {
      ans0.push_back(std::make_pair(id,offset));
    }
    delete_edges(vs,matching);
    ans1=colorize(vs,offset+1);
    for (std::pair<int,int> &p:ans1) {
      ans0.push_back(p);
    }
    return ans0;
  }
}

void contract(std::vector<int> &deg,djset &ds,int D) {
  std::priority_queue<std::pair<int,int>> pq;
  for (int i=0;i<(int)deg.size();++i) {
    pq.push(std::make_pair(-deg[i],i));
  }
  while (pq.size()>1) {
    std::pair<int,int> a=pq.top();pq.pop();
    std::pair<int,int> b=pq.top();pq.pop();
    if (-(a.first+b.first)>D) break;
    a.first+=b.first;
    ds.unite(a.second,b.second);
    pq.push(a);
  }
  ds.build_id();
}

std::vector<int> solve(int L,int R,int M,int a[],int b[]) {
  int D=0;
  std::vector<int> deg[2];
  deg[0]=std::vector<int>(L);
  deg[1]=std::vector<int>(R);
  for (int i=0;i<M;++i) {
    ++deg[0][a[i]];
    ++deg[1][b[i]];
    D=std::max(D,std::max(deg[0][a[i]],deg[1][b[i]]));
  }
  djset ds[2]={L,R};
  contract(deg[0],ds[0],D);
  contract(deg[1],ds[1],D);
  int sz=std::max(ds[0].components(),ds[1].components());
  std::vector<vertex> vs(2*sz);
  for (int i=0;i<(int)vs.size();++i) vs[i].id=i;
  for (int i=0;i<M;++i) {
    int u=ds[0].id[ds[0].root(a[i])];
    int v=ds[1].id[ds[1].root(b[i])];
    add_edge(vs[u],vs[v+sz],-1,1,i);
  }
  int p=0,q=sz,extra=0;
  while (p<(int)vs.size()&&q<(int)vs.size()) {
    if ((int)vs[p].edges.size()==D) ++p;
    else if ((int)vs[q].edges.size()==D) ++q;
    else add_edge(vs[p],vs[q],-1,1,M+(extra++));
  }
  std::vector<std::pair<int,int>> ps=colorize(vs);
  std::vector<int> ans(M);
  for (auto &pair:ps) {
    if (pair.first<M) ans[pair.first]=pair.second;
  }
  return ans;
}

std::mt19937 mt;

void gen() {
  int L=100000;
  int R=100000;
  int M=100000;
  int a[M];
  int b[M];
  for (int i=0;i<M;++i) {
    a[i]=mt()%L;
    b[i]=mt()%R;
  }
  std::vector<int> ans=solve(L,R,M,a,b);
  std::vector<vertex> g(L+R);
  for (int i=0;i<(int)g.size();++i) g[i].id=i;
  for (int i=0;i<M;++i) {
    add_edge(g[a[i]],g[b[i]+L],ans[i],1,i);
  }
  for (vertex &v:g) {
    std::set<int> cols;
    for (edge &e:v.edges) {
      cols.insert(e.col);
    }
  }
  std::cout<<"ok"<<std::endl;
}

void verify() {
  for (int i=0;i<10;++i) {
    clock_t start=clock();
    verify();
    clock_t end=clock();
    const double time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000.0;
    printf("time %lf[ms]\n", time);
  }
}

void solve() {
  int L,R,M;
  scanf("%d%d%d",&L,&R,&M);
  int a[M];
  int b[M];
  for (int i=0;i<M;++i) {
    scanf("%d%d\n",&a[i],&b[i]);
  }
  std::vector<int> ans=solve(L,R,M,a,b);
  int D=0;
  for (int &c:ans) D=std::max(D,c+1);
  printf("%d\n",D);
  for (int &c:ans) {
    printf("%d\n",c);
  }
}


int main() {
  solve();
}
