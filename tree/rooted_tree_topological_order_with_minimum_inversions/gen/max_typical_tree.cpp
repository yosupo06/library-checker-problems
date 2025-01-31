#include "../params.h"
#include "random.h"
#include "gen_fractions.hpp"
#include "gen_typical_trees.hpp"
#include "output.hpp"

#include <cstdlib>
#include <vector>
#include <algorithm>

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = N_MAX;
    std::vector<int> P;

    if(seed == 0){
        P = typical_tree_path(N);
    } else if(seed == 1){
        P = typical_tree_star0(N);
    } else if(seed == 2){
        P = typical_tree_star1(N);
    } else if(seed == 3){
        P = typical_tree_binary(N);
    }

    auto CD = distinct_fractions(N, C_SUM_MAX, D_SUM_MAX);
    
    gen.shuffle(CD.begin(), CD.end());

    case_output(N, P, CD);

    return 0;
}
