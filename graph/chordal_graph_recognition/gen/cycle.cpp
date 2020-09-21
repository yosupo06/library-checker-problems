#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;



int main(int, char* argv[]) {

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = std::min(N_MAX,M_MAX);
  
  vector<pair<int,int>> edges;
  auto add_edge=[&](int u,int v){
    if(gen.uniform(0,1)){
      edges.push_back({u,v});
    }else{
      edges.push_back({v,u});
    }
  };
  for (int i = 0; i < n-1; i++) {
    add_edge(i,i+1);
  }
  add_edge(0,n-1);
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
