#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

/**
 * a / b, a // b : 小数, 整数としての割り算
 * sum_{i = 0..n-1} (ai + b) // m を求める
 * 
 * 線分 y = (ax + b) / m, (0 <= x <= n)は真下に何個(完全な)正方形を含むか？と同値
 */
ll sum_of_floor(ll n, ll m, ll a, ll b) {
    ll ans = 0;
    if (a >= m) {
        ans += (n - 1) * n * (a / m) / 2;
        a %= m;
    }
    if (b >= m) {
        ans += n * (b / m);
        b %= m;
    }

    /**
     * 線分の端点を、y座標が整数になるようにちょっとずらす -> 90度回転
     * y座標: (b / m, (an + b) / m) -> (0, y_max)
     * x座標: (0, n) -> (-b / a, x_max / a)
     * 
     * 端点をずらすことで答えは (n - ceil(x_max / a)) * y_max 減る
     * 
     * 90度回転する
     * (m / a) * x + (b2 / a) = y_max
     */

    ll y_max = (a * n + b) / m, x_max = (y_max * m - b);
    if (y_max == 0) return ans;
    ans += (n - (x_max + a - 1) / a) * y_max;
    ans += sum_of_floor(y_max, a, m, (a - x_max % a) % a);
    return ans;
}

int main() {

    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; i++) {
        ll n, m, a, b;
        scanf("%lld %lld %lld %lld", &n, &m, &a, &b);
        cout << sum_of_floor(n, m, a, b) << "\n";
    }
    return 0;
}
