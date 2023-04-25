#include <cinttypes>
#include <iostream>
#include "../lib/util.hpp"

int main() {
    int q;
    scanf("%d\n", &q);
    for(i64 i = 0; i < q; i++) {
        i64 n;
        scanf("%" PRId64 "\n", &n);
        if(is_prime(n)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}
