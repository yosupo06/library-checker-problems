#include <vector>
#include <iostream>
#include <algorithm>

#include "random.h"
#include "../params.h"

using namespace std;

/*
 3-regular bipartite graph,
 like a benzene

      ______   
     //    \\  
    //      \\ 
    \        / 
     \ ____ /  
      ------   

*/

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int h = min(M_MAX / 6, min(L_MAX, R_MAX)) * 2;
  // int m = h * 3;

  vector<pair<int,int>> edges;
  for(int i=0; i<h; i++){
    edges.push_back({ i, i });
    edges.push_back({ i, i });
    edges.push_back({ i, (i + 1) % h });
  }

  if (seed % 2 == 1) {
    // shuffle
    int l = h;
    int r = h;
    vector<int> new_idx_L(l), new_idx_R(r);
    for (int i = 0; i < l; ++i) new_idx_L[i] = i;
    for (int i = 0; i < r; ++i) new_idx_R[i] = i;
    gen.shuffle(edges.begin(), edges.end());
    gen.shuffle(new_idx_L.begin(), new_idx_L.end());
    gen.shuffle(new_idx_R.begin(), new_idx_R.end());
    for (auto& [a, b]: edges) a = new_idx_L[a], b = new_idx_R[b];
  }

  int m = int(edges.size());
  printf("%d %d %d\n", h, h, m);
  for (auto edge: edges) { printf("%d %d\n", edge.first, edge.second); }
  return 0;
}
