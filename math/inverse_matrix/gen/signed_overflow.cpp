#include <iostream>
#include <set>
#include <limits>

#include "random.h"
#include "../params.h"

using namespace std;

int main() {
    int val = MOD/2 - 1;
    unsigned long long max_ll = numeric_limits<long long>::max();

    // Find smallest size n where n * val * val > max_ll
    int n = 0;
    for (unsigned long long res = 0; res <= max_ll; res += (long long) val * val, ++n);

    cout << n << '\n';
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << val << ((j == n - 1) ? '\n' : ' ');
        }
    }

    return 0;
}
