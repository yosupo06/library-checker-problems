#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    assert(a <= 1000 && b <= 1000);
    printf("%d\n", a + b);
    return 0;
}
