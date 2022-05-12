#include <iostream>
#include <vector>
using namespace std;

int main(int, char* argv[]) {


    int Q = 1000000;

    printf("%d\n", Q);

    int query0 = Q - 1000;
    int query1 = 1000;
    long long int mask = (1 << 17) - 1;
    int length = (int)((1<<15)*1.3+1);

    printf("%d %lld\n", 0, mask + 2);
    printf("%d %lld\n", 0, mask + 2);
    long long int x = 6;
    for(int i = 1; i < length; i++){
        printf("%d %lld\n", 0, x);
        printf("%d %lld\n", 0, x);
        x = x * 5 + 1;
        x &= mask;
    }

    for(int i = 0; i < query0 - length; i++){
        printf("%d %lld\n", 0, 1ll);
        printf("%d %lld\n", 0, 1ll);
    }

    
    for(int i = 0; i < query1; i++){
        printf("%d %d", 1, i);
        printf("%d %d", 0, i);
    }
    return 0;
}