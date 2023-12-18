#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    // https://github.com/yosupo06/library-checker-problems/pull/1069#discussion_r1429047154

    // Consume the same number of random numbers as in the original case
    gen.uniform<int>(0, 2);

    // Correspondence between seeds and d in the original test cases:
    //                       seed     d                              
    //                      ==============                           
    //                        0     65535                            
    //                        1     65536                            
    //                        2     65537                            
    //                      --------------                           
    int a[3]{ 0, 1, 2 };

    long long d = 65535 + a[seed % 3];
    long long k = gen.uniform<long long>(0, K_MAX);

    printf("%lld %lld\n", d, k);

    for(int _ = 0; _ < 2; _++) {
        for (int i = 0; i < d; i++) {
            printf("%d", gen.uniform<int>(0, MOD - 1));
            printf(i == d - 1 ? "\n" : " ");
        }
    }
    return 0;
}
