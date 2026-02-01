#include <iostream>
#include <set>
#include <limits>

#include "random.h"
#include "../params.h"

using namespace std;

int main() {
    int val = MOD - 2;
    unsigned long long max_ull = numeric_limits<unsigned long long>::max();

    // Find smallest size n where n * val * val > max_ull
    unsigned long long val2 = (unsigned long long) val * val;
    int n = max_ull / val2 + 1;

    cout << n << ' ' << n << ' ' << n << '\n';
   
    for (int x = 0; x < 2; ++ x) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << val << ((j == n - 1) ? '\n' : ' ');
            }
        }
    }

    return 0;
}
