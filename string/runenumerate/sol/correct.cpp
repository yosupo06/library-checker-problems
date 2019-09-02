#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <tuple>

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

struct RunExec {
    VV<pair<int, int>> runs;

    int n;
    V<int> a;

    V<int> rev(V<int> l) {
        reverse(l.begin(), l.end());
        return l;
    }

    V<int> sub_a(int l, int r) {
        return {a.begin() + l, a.begin() + r};
    }
    V<int> concat(V<int> l, const V<int>& r) {
        l.insert(l.end(), r.begin(), r.end());
        return l;
    }

    void run(int l, int r, int f) {
        if (l + 1 == r) return;
        int md = (l + r + f) / 2;
        run(l, md, f);
        run(md, r, f);
        auto z1 = z_algo(rev(sub_a(l, md)));
        auto z2 = z_algo(concat(sub_a(md, r), sub_a(l, r)));
        for (int i = md - 1; i >= l; i--) {
            int l1 = min(i - l, z1[md - i]);
            int l2 = min(r - md, z2[(r - l) - (md - i)]);
            int le = i - l1, ri = md + l2, peri = md - i;
            if (ri - le >= 2 * peri) runs[md - i].push_back({i - l1, md + l2});
        }
    }

    RunExec(V<int> _a) : a(_a) {
        n = int(a.size());
        runs.resize(n / 2 + 1);
        reverse(a.begin(), a.end());
        run(0, n, 0);
        for (auto& run: runs) {
            for (auto& p: run) {
                tie(p.first, p.second) =
                        make_pair(n - p.second, n - p.first);
            }
        }
        reverse(a.begin(), a.end());
        run(0, n, 1);

        set<pair<int, int>> vis;
        for (int ph = 1; ph <= n / 2; ph++) {
            auto& run = runs[ph];
            sort(run.begin(), run.end(), [&](pair<int, int> lhs, pair<int, int> rhs) {
                if (lhs.first != rhs.first) return lhs.first < rhs.first;
                return lhs.second > rhs.second;
            });
            V<pair<int, int>> res;
            for (auto p: run) {
                if (!res.empty() && p.second <= res.back().second) continue;
                res.push_back(p);
            }
            run = res;
            res.clear();
            for (auto p: run) {
                if (vis.count(p)) continue;
                vis.insert(p);
                res.push_back(p);
            }
            run = res;
        }
    }
};

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    string s;
    cin >> s;
    V<int> _s;
    for (char c : s) _s.push_back(c);
    RunExec runexec(_s);
    int m = int(runexec.runs.size());
    int n = 0;
    for (auto v : runexec.runs) n += int(v.size());

    cout << n << endl;
    for (int i = 0; i < m; i++) {
        auto v = runexec.runs[i];
        sort(v.begin(), v.end());
        for (auto p : v) {
            cout << i << " " << p.first << " " << p.second << endl;
        }
    }
    return 0;
}
