#include "../params.h"
#include "random.h"
#include "output.hpp"

#include <cstdlib>
#include <vector>
#include <algorithm>

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = N_MAX;
    std::vector<int> P;
    P.push_back(-1);
    
    for(int i=1; i<N; i++){
        int p = gen.uniform(0, i-1);
        P.push_back(p);
    }
    
    std::vector<int> C(N, 0);
    std::vector<int> D(N, 0);

    case_output_split(N, P, C, D);

    return 0;
}
