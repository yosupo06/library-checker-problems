#include <cinttypes>
#include <iostream>
#include "../lib/prime.hpp"

int main() {
    int q;
    scanf("%d\n", &q);
    for(int i = 0; i < q; i++) {
        u64 n;
        scanf("%" PRIu64 "\n", &n);
        if(is_prime(n)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}
