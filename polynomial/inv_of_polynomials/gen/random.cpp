#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <random>
#include <algorithm>
#include <deque>
#include <cstring>
#include <time.h>
#include <tuple>
#include "random.h"
#include "../params.h"


int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    
    int n = gen.uniform(1, int(N_MAX));
    int m = gen.uniform(1, int(N_MAX));
    
    std::vector<int> a(n),b(m);
    
    for (int i = 0; i < n; i++) {
      a[i]=gen.uniform((i == n-1) ? 1 : 0, int(MOD - 1));
    }
    for (int i = 0; i < m; i++) {
      b[i]=gen.uniform((i == m-1) ? 1 : 0, int(MOD - 1));
    }
   
    
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("%d", gen.uniform((i == n-1) ? 1 : 0, int(MOD - 1)));
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    
    for (int i = 0; i < m; i++) {
      printf("%d", gen.uniform((i == m-1) ? 1 : 0, int(MOD - 1)));
      if (i != m - 1) printf(" ");
    }
    printf("\n");
    
    
    return 0;
}
