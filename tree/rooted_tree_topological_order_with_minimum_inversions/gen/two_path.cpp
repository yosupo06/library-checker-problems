#include "../params.h"
#include "random.h"
#include "gen_fractions.hpp"
#include "output.hpp"

#include <cstdlib>
#include <vector>
#include <algorithm>

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = N_MAX;
    std::vector<int> P(N, -1);

    int n0 = (N-1) / 2;
    int n1 = N / 2;
    for(int i=1; i<N; i++) P[i] = i-1;
    P[1+n0] = 0;

    auto CD = distinct_fractions(N, C_SUM_MAX, D_SUM_MAX);
    sort_fractions(CD);

    if(seed == 1){
        std::reverse(CD.begin(), CD.end());
    } else if(seed == 2){
        gen.shuffle(CD.begin(), CD.end());
    } else if(seed == 3){
        auto newCD = CD;
        for(int i=0; i<n0+1; i++) newCD[i] = CD[i*2];
        for(int i=0; i<n1; i++) newCD[n0+1+i] = CD[i*2+1];
        std::swap(newCD, CD);
    } else if(seed == 4){
        std::reverse(CD.begin(), CD.end());
        auto newCD = CD;
        for(int i=0; i<n0+1; i++) newCD[i] = CD[i*2];
        for(int i=0; i<n1; i++) newCD[n0+1+i] = CD[i*2+1];
        std::swap(newCD, CD);
    }

    case_output(N, P, CD);

    return 0;
}
