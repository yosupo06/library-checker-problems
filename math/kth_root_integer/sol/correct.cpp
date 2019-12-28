#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

using Int = __int128_t;

Int mypow(Int a, int k) {
    Int result = 1;
    for (int i = 0; i < k; i++) {
        result *= a;
        if (result >> 64) break;
    }
    return result;
}

ull solve(ull a, int k) {
    if (k == 1) return a;
    // lw^k <= a < up^k
    ull lw = 0;
    ull up = 1LL << 40;

    while (up - lw > 1) {
        ull mid = (lw + up) / 2;
        if (mypow(mid, k) <= a) {
            lw = mid;
        } else {
            up = mid;
        }
    }
    
    return lw;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        ull a; int k;
        scanf("%ulld %d", &a, &k);
        cout << solve(a, k) << "\n";
    }
    return 0;
}
