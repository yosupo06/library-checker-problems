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
    for(int i=1; i<N/2; i++) P.push_back(i-1);
    for(int i=N/2; i<N; i++) P.push_back(gen.uniform(0,i-1));

    std::vector<int> C = gen.choice<int>(N, 0, C_SUM_MAX + N);
    for(int i=N-1; i>=1; i--) C[i] -= C[i-1] + 1;
    std::vector<int> D = gen.choice<int>(N, 0, D_SUM_MAX + N);
    for(int i=N-1; i>=1; i--) D[i] -= D[i-1] + 1;

    case_output_split(N, P, C, D);

    return 0;
}
