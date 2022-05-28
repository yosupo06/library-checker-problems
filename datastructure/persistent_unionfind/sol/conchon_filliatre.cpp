/* reference: https://judge.yosupo.jp/submission/90982 */

#include <iostream>
#include <utility>
#include <vector>

template <class T>
struct PersistentArray {
    using Array = std::vector<T>;

    PersistentArray(const Array& data_)
        : data{data_}, d{{true, -1, T{}, -1, 0}} {}

    // returns value of latest version
    T get(int version, int index) { return d[version].get(index, d, data); }

    // returns value of latest version
    T get(int index) { return d.back().get(index, d, data); }

    // returns new version number
    int set(int version, int index, T value) {
        int new_pos = (int)d.size();
        d.push_back(d[version].set(index, value, new_pos));
        return new_pos;
    }

    // returns new version number
    int set(int index, T value) {
        int new_pos = (int)d.size();
        d.push_back(d.back().set(index, value, new_pos));
        return new_pos;
    }

    int total_versions() { return (int)d.size(); }

   private:
    struct Node;
    using Container = std::vector<Node>;
    struct Node {
        bool is_root;
        int index;
        T value;
        int parent_pos;
        int self_pos;
        // for a single persistent array, the container c should be the same
        T get(int i, Container& c, Array& a) {
            reroot(c, a);
            return a[i];
        }
        Node set(int i, T v, int new_self_pos) {
            return Node{false, i, v, self_pos, new_self_pos};
        }
        void reroot(Container& c, Array& a) {
            if (!is_root) {
                auto i = index;
                auto v = value;
                auto parent = parent_pos;
                c[parent].reroot(c, a);
                is_root = true;
                std::swap(v, a[i]);
                auto& p = c[parent];
                p.is_root = false;
                p.index = i;
                p.value = v;
                p.parent_pos = self_pos;
            }
        }
    };
    Array data;
    Container d;
};

struct PersistentDSU {
    int n;
    PersistentArray<int> parent;
    std::vector<int> versions;
    PersistentDSU(int n_)
        : n{n_}, parent(std::vector<int>(n_, -1)), versions{0} {}
    // need to update versions[version] in root() as well to keep amortization
    // no path compression in what follows:
    int root(int version, int u) { return root_(versions[version], u); }
    int root_(int internal_version, int u) {
        int p = parent.get(internal_version, u);
        if (p < 0) return u;
        return root_(internal_version, p);
    }
    bool join(int version, int u, int v) {
        int internal_version = versions[version];
        u = root_(internal_version, u);
        v = root_(internal_version, v);
        if (u != v) {
            int pu = parent.get(internal_version, u);
            int pv = parent.get(internal_version, v);
            if (pu > pv) std::swap(u, v);
            int new_version_1 = parent.set(internal_version, u, pu + pv);
            int new_version_2 = parent.set(new_version_1, v, u);
            versions.push_back(new_version_2);
            return true;
        } else {
            add_dummy_version(internal_version);
            return false;
        }
    }
    void add_sentinel_version() { versions.push_back(-1); }
    void add_dummy_version() { add_dummy_version(parent.total_versions() - 1); }
    void add_dummy_version(int internal_version) {
        versions.push_back(
            parent.set(internal_version, 0, parent.get(internal_version, 0)));
    }
};

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    // cout << setprecision(20) << fixed;
    int _tests = 1;
    // cin >> _tests;
    for (int _test = 1; _test <= _tests; ++_test) {
        // cout << "Case #" << _test << ": ";
        int n, q;
        cin >> n >> q;
        PersistentDSU dsu(n);
        for (int query = 1; query <= q; ++query) {
            int t, k, u, v;
            cin >> t >> k >> u >> v;
            ++k;
            if (t == 0) {
                dsu.join(k, u, v);
            } else {
                int ru = dsu.root(k, u);
                int rv = dsu.root(k, v);
                cout << int(ru == rv) << '\n';
                dsu.add_sentinel_version();
            }
        }
    }
}

