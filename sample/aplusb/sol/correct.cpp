#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int a, b;
    cin >> a >> b;
    cout << a + b << endl; a
    return 0;
}
