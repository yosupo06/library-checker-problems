#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;



int main(int, char* argv[]) {

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = std::min(N_MAX,(M_MAX+3)/2);
  
  vector<pair<int,int>> edges;
  auto add_edge=[&](int u,int v){
    if(gen.uniform(0,1)){
      edges.push_back({u,v});
    }else{
      edges.push_back({v,u});
    }
  };
  add_edge(0,1);
  for (int i = 2; i < n; i++) {
    auto e=edges[gen.uniform(0,(int)edges.size()-1)];
    add_edge(i,e.first);
    add_edge(i,e.second);
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
