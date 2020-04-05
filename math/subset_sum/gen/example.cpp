#include "random.h"
#include <iostream>
#include <vector>
#include <cassert>
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N=5,T=5;
    printf("%d %d\n", N,T);
    for(int i=0;i<N;i++){
        printf("%d",gen.uniform(1,T));
        if(i!=N-1)printf(" ");
    } printf("\n");
    return 0;
}