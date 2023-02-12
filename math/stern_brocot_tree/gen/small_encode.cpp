
#include "../params.h"
#include "../lib/lib.hpp"

int main(int, char*[]) {
    std::vector<int> A;
    std::vector<int> B;

    int max_ab = 1;
    while(max_ab * max_ab <= T_MAX) max_ab++;
    max_ab--;

    for(int a=1; a<=max_ab; a++){
        int b = 1;
        for(int bi=1; bi<=max_ab; bi++){
            while(Gcd(a, b) != 1) b++;
            A.push_back(a);
            B.push_back(b);
            b++;
        }
    }

    int z = A.size();
    
    // output T
    printf("%d\n", z);

    for(int i=0; i<z; i++){
        printf("ENCODE_PATH %d %d\n", A[i], B[i]);
    }

    return 0;
}
