
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>
#include "random.h"
#include "../params.h"

std::vector<int> randomTree(int minN, int maxN, Random& rng){
    int N = rng.uniform(minN, maxN);
    std::vector<int> P(N-1);
    for(int i=1; i<N; i++) P[i-1] = rng.uniform(0, i-1);
    return P;
}

std::vector<int> shuffleTree(const std::vector<int>& tree, Random& rng){

    int N = tree.size() + 1;
    std::vector<int> adjI(N+1, 0);
    std::vector<int> adj(N-1);
    for(int i=0; i<N-1; i++) adjI[tree[i]]++;
    for(int i=0; i<N; i++) adjI[i+1] += adjI[i];
    for(int i=0; i<N-1; i++) adj[--adjI[tree[i]]] = i+1;

    std::vector<int> Q = {0};
    std::vector<int> IQ(N, -1);
    for(int l=0; l<N; l++){
        int qi = rng.uniform(l, (int)Q.size()-1);
        std::swap(Q[l], Q[qi]);
        int p = Q[l];
        IQ[p] = l;
        for(int ei=adjI[p]; ei<adjI[p+1]; ei++){
            int c = adj[ei];
            Q.push_back(c);
        }
    }

    std::vector<int> res(N-1);
    for(int i=1; i<N; i++) res[i-1] = IQ[tree[Q[i]-1]];
    return res;
}

std::vector<int> mergeTree(const std::vector<int>& A, const std::vector<int>& B){
    int nA = A.size() + 1;
    int nB = B.size() + 1;
    std::vector<int> res(nA + nB);
    res[0] = res[nA] = 0;
    for(int i=1; i<nA; i++) res[i] = A[i-1] + 1;
    for(int i=1; i<nB; i++) res[nA+i] = B[i-1] + 1 + nA;
    return res;
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = (N_MAX - 1) / 2;
    int N = n * 2 + 1;

    auto T = randomTree(n, n, gen);
    auto TT = mergeTree(T, T);
    TT = shuffleTree(TT, gen);

    assert((int)TT.size() + 1 == N);

    printf("%d\n", N);
    for(int i=1; i<N; i++){
        if(i != 1) printf(" ");
        printf("%d", TT[i-1]);
    }
    printf("\n");
    return 0;
}
