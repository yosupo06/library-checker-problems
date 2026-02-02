#include <iostream>
#include <set>
#include <limits>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);

    int val = MOD - 2;
    unsigned long long max_ull = numeric_limits<unsigned long long>::max();

    // Find smallest size n where n * val * val > max_ull
    int n = 0;
    unsigned long long val2 = (unsigned long long) val * val;
    if (seed == 0) {
        unsigned long long res = 0;
        // Check if adding val2 to res will overflow
        // this test mistakenly produces the largest n that does not overflow
        while (res + val2 > res) {
            res += val2;
            ++n;
        }
    } else if (seed == 1) {
        n = max_ull / val2 + 1;
    }

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
