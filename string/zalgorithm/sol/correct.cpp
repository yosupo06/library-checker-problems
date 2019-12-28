#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

// s[0..r[i]] == s[i..i+r[i]]
template <class S> V<int> z_algo(const S& s) {
    int n = int(s.size());
    V<int> r(n + 1);
    r[0] = 0;
    for (int i = 1, j = 0; i <= n; i++) {
        int& k = r[i];
        k = (j + r[j] <= i) ? 0 : min(j + r[j] - i, r[i - j]);
        while (i + k < n && s[k] == s[i + k]) k++;
        if (j + r[j] < i + r[i]) j = i;
    }
    r[0] = n;
    return r;
}

int main() {


    string s;
    cin >> s;
    int n = int(s.size());
    auto z = z_algo(s);

    for (int i = 0; i < n; i++) {
        cout << z[i];
        if (i + 1 != n) cout << " ";
    }
    printf("\n");

    return 0;
}
