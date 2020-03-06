#include <iostream>
#include <vector>
#include <set>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

bool collatz(ll x) {
    set<ll> visited;
    int count = 0;
    while (x > 1) {
        count++;
        if (count == 1000) {
            count = 0;
            if (visited.count(x)) return false;
            visited.insert(x);
        }
        if (x % 2 == 0) x /= 2;
        else x = x * 3 + 1;
    }
    return true;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    for (int i = 1; i <= b; i++) {
        if (collatz(i)) a++;
    }
    printf("%d\n", a);
    return 0;
}
