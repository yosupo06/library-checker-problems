#include <iostream>
#include <set>
#include <limits>

#include "random.h"
#include "../params.h"

using namespace std;

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

    cout << n << ' ' << n << '\n';
    
    for (int i = 0; i < n; ++i) {
        cout << val << ((i == n - 1) ? '\n' : ' ');
    }
    
    for (int i = 0; i < n; ++i) {
        cout << val << ((i == n - 1) ? '\n' : ' ');
    }

    return 0;
}

