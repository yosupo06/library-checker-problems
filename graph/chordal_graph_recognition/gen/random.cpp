#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;



int main(int, char* argv[]) {

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  vector<pair<int,int>> edges;
  set<pair<int,int>> eset;
  auto add_edge=[&](int u,int v){
    if(gen.uniform(0,1)){
      edges.push_back({u,v});
    }else{
      edges.push_back({v,u});
    }
    eset.insert({u,v});
    eset.insert({v,u});
  };
  while(edges.size()<M_MAX){
    int u=gen.uniform(0,n-1);
    int v=gen.uniform(0,n-1);
    if(u!=v&&!eset.count({u,v})){
      add_edge(u,v);
    }
  }
  gen.shuffle(edges.begin(), edges.end());
  
  vector<int> labels;
  for (int i = 0; i < n; i++) {
    labels.push_back(i);
  }
  gen.shuffle(labels.begin(), labels.end());
  int m=edges.size();
  printf("%d %d\n", n, m);
  for (auto edge: edges) {
    printf("%d %d\n", labels[edge.first], labels[edge.second]);
  }
  return 0;
}
