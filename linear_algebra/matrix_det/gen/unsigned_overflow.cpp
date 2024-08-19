#include <iostream>
#include <set>
#include <limits>

#include "random.h"
#include "../params.h"

using namespace std;

const int MOD = 998244353;

int main() {
    int val = MOD - 2;

    // Find smallest size n where n * val * val > numeric_limits<unsigned long long>::max()
    int n = 0;
    unsigned long long res = 0;
    long long val2 = (long long) val * val;
    while (res + val2 >= res) // Check if adding val2 to res will overflow
    {
        res += val2;
        ++n;
    }

    cout << n << '\n';
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << val << ((j == n - 1) ? '\n' : ' ');
        }
    }

    return 0;
}
