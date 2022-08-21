
#include <vector>
#include <utility>

namespace nachia{
    
struct AdjacencyList{
public:
    struct AdjacencyListRange{
        using iterator = typename std::vector<int>::const_iterator;
        iterator begi, endi;
        iterator begin() const { return begi; }
        iterator end() const { return endi; }
        int size() const { return (int)std::distance(begi, endi); }
        const int& operator[](int i) const { return begi[i]; }
    };
private:
    int mn;
    std::vector<int> E;
    std::vector<int> I;
public:
    AdjacencyList(int n, const std::vector<std::pair<int,int>>& edges, bool rev){
        mn = n;
        std::vector<int> buf(n+1, 0);
        for(auto [u,v] : edges){ ++buf[u]; if(rev) ++buf[v]; }
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        E.resize(buf[n]);
        for(int i=(int)edges.size()-1; i>=0; i--){
            auto [u,v] = edges[i];
            E[--buf[u]] = v;
            if(rev) E[--buf[v]] = u;
        }
        I = std::move(buf);
    }
    AdjacencyList(const std::vector<std::vector<int>>& edges = {}){
        int n = mn = edges.size();
        std::vector<int> buf(n+1, 0);
        for(int i=0; i<n; i++) buf[i+1] = buf[i] + edges[i].size();
        E.resize(buf[n]);
        for(int i=0; i<n; i++) for(int j=0; j<(int)edges[i].size(); j++) E[buf[i]+j] = edges[i][j];
        I = std::move(buf);
    }
    static AdjacencyList from_raw(std::vector<int> targets, std::vector<int> bounds){
        AdjacencyList res;
        res.mn = bounds.size() - 1;
        res.E = std::move(targets);
        res.I = std::move(bounds);
        return res;
    }
    AdjacencyListRange operator[](int u) const {
        return AdjacencyListRange{ E.begin() + I[u], E.begin() + I[u+1] };
    }
    int num_vertices() const { return mn; }
    int size() const { return num_vertices(); }
    int num_edges() const { return E.size(); }
    AdjacencyList reversed_edges() const {
        AdjacencyList res;
        int n = res.mn = mn;
        std::vector<int> buf(n+1, 0);
        for(int v : E) ++buf[v];
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        res.E.resize(buf[n]);
        for(int u=0; u<n; u++) for(int v : operator[](u)) res.E[--buf[v]] = u;
        res.I = std::move(buf);
        return res;
    }
};

} // namespace nachia

#include <cassert>

#include <algorithm>
#include <numeric>



namespace nachia{

namespace treetourlex_internal{

// from atcoder library <atcoder/string>
namespace atcoder {

namespace internal {

std::vector<int> sa_naive(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r) {
        if (l == r) return false;
        while (l < n && r < n) {
            if (s[l] != s[r]) return s[l] < s[r];
            l++;
            r++;
        }
        return l == n;
    });
    return sa;
}

std::vector<int> sa_doubling(const std::vector<int>& s) {
    int n = int(s.size());
    std::vector<int> sa(n), rnk = s, tmp(n);
    std::iota(sa.begin(), sa.end(), 0);
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int x, int y) {
            if (rnk[x] != rnk[y]) return rnk[x] < rnk[y];
            int rx = x + k < n ? rnk[x + k] : -1;
            int ry = y + k < n ? rnk[y + k] : -1;
            return rx < ry;
        };
        std::sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        std::swap(tmp, rnk);
    }
    return sa;
}

// SA-IS, linear-time suffix array construction
// Reference:
// G. Nong, S. Zhang, and W. H. Chan,
// Two Efficient Algorithms for Linear Time Suffix Array Construction
template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
std::vector<int> sa_is(const std::vector<int>& s, int upper) {
    int n = int(s.size());
    if (n == 0) return {};
    if (n == 1) return {0};
    if (n == 2) {
        if (s[0] < s[1]) {
            return {0, 1};
        } else {
            return {1, 0};
        }
    }
    if (n < THRESHOLD_NAIVE) {
        return sa_naive(s);
    }
    if (n < THRESHOLD_DOUBLING) {
        return sa_doubling(s);
    }

    std::vector<int> sa(n);
    std::vector<bool> ls(n);
    for (int i = n - 2; i >= 0; i--) {
        ls[i] = (s[i] == s[i + 1]) ? ls[i + 1] : (s[i] < s[i + 1]);
    }
    std::vector<int> sum_l(upper + 1), sum_s(upper + 1);
    for (int i = 0; i < n; i++) {
        if (!ls[i]) {
            sum_s[s[i]]++;
        } else {
            sum_l[s[i] + 1]++;
        }
    }
    for (int i = 0; i <= upper; i++) {
        sum_s[i] += sum_l[i];
        if (i < upper) sum_l[i + 1] += sum_s[i];
    }

    auto induce = [&](const std::vector<int>& lms) {
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper + 1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for (auto d : lms) {
            if (d == n) continue;
            sa[buf[s[d]]++] = d;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n - 1]]++] = n - 1;
        for (int i = 0; i < n; i++) {
            int v = sa[i];
            if (v >= 1 && !ls[v - 1]) {
                sa[buf[s[v - 1]]++] = v - 1;
            }
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for (int i = n - 1; i >= 0; i--) {
            int v = sa[i];
            if (v >= 1 && ls[v - 1]) {
                sa[--buf[s[v - 1] + 1]] = v - 1;
            }
        }
    };

    std::vector<int> lms_map(n + 1, -1);
    int m = 0;
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms_map[i] = m++;
        }
    }
    std::vector<int> lms;
    lms.reserve(m);
    for (int i = 1; i < n; i++) {
        if (!ls[i - 1] && ls[i]) {
            lms.push_back(i);
        }
    }

    induce(lms);

    if (m) {
        std::vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for (int v : sa) {
            if (lms_map[v] != -1) sorted_lms.push_back(v);
        }
        std::vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for (int i = 1; i < m; i++) {
            int l = sorted_lms[i - 1], r = sorted_lms[i];
            int end_l = (lms_map[l] + 1 < m) ? lms[lms_map[l] + 1] : n;
            int end_r = (lms_map[r] + 1 < m) ? lms[lms_map[r] + 1] : n;
            bool same = true;
            if (end_l - l != end_r - r) {
                same = false;
            } else {
                while (l < end_l) {
                    if (s[l] != s[r]) {
                        break;
                    }
                    l++;
                    r++;
                }
                if (l == n || s[l] != s[r]) same = false;
            }
            if (!same) rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa =
            sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for (int i = 0; i < m; i++) {
            sorted_lms[i] = lms[rec_sa[i]];
        }
        induce(sorted_lms);
    }
    return sa;
}

}  // namespace internal

std::vector<int> suffix_array(const std::vector<int>& s, int upper) {
    assert(0 <= upper);
    for (int d : s) {
        assert(0 <= d && d <= upper);
    }
    auto sa = internal::sa_is(s, upper);
    return sa;
}

// Reference:
// T. Kasai, G. Lee, H. Arimura, S. Arikawa, and K. Park,
// Linear-Time Longest-Common-Prefix Computation in Suffix Arrays and Its
// Applications
template <class T>
std::vector<int> lcp_array(const std::vector<T>& s,
                           const std::vector<int>& sa) {
    int n = int(s.size());
    assert(n >= 1);
    std::vector<int> rnk(n);
    for (int i = 0; i < n; i++) {
        rnk[sa[i]] = i;
    }
    std::vector<int> lcp(n - 1);
    int h = 0;
    for (int i = 0; i < n; i++) {
        if (h > 0) h--;
        if (rnk[i] == 0) continue;
        int j = sa[rnk[i] - 1];
        for (; j + h < n && i + h < n; h++) {
            if (s[j + h] != s[i + h]) break;
        }
        lcp[rnk[i] - 1] = h;
    }
    return lcp;
}

} // namespace atcoder
    
struct CSRArray{
public:
    struct CSRRange{
        using iterator = typename std::vector<int>::iterator;
        iterator begi, endi;
        iterator begin() const { return begi; }
        iterator end() const { return endi; }
        int size() const { return (int)::std::distance(begi, endi); }
        int& operator[](int i) const { return begi[i]; }
    };
private:
    int mn;
    std::vector<int> E;
    std::vector<int> I;
public:
    CSRArray(int n, std::vector<std::pair<int,int>> elems){
        mn = n;
        std::vector<int> buf(n+1, 0);
        for(auto [u,v] : elems) ++buf[u];
        for(int i=1; i<=n; i++) buf[i] += buf[i-1];
        E.resize(buf[n]);
        for(int i=(int)elems.size()-1; i>=0; i--){
            auto [u,v] = elems[i];
            E[--buf[u]] = v;
        }
        I = std::move(buf);
    }
    CSRArray(const std::vector<std::vector<int>>& elems = {}){
        int n = mn = elems.size();
        std::vector<int> buf(n+1, 0);
        for(int i=0; i<n; i++) buf[i+1] = buf[i] + elems[i].size();
        E.resize(buf[n]);
        for(int i=0; i<n; i++) for(int j=0; j<(int)elems[i].size(); j++) E[buf[i]+j] = elems[i][j];
        I = std::move(buf);
    }
    CSRRange operator[](int u) {
        return CSRRange{ E.begin() + I[u], E.begin() + I[u+1] };
    }
    int size() const { return mn; }
    int num_elems() const { return E.size(); }
};
    
void sort_tg_by(CSRArray& tg, std::vector<int>& by, int bound){
    std::vector<int> cnt(bound + 1);
    for(int i=0; i<(int)tg.size(); i++) for(int v : tg[i]) cnt[by[v]]++;
    for(int i=0; i<bound; i++) cnt[i+1] += cnt[i];
    std::vector<std::pair<int,int>> bucket(cnt.back());
    for(int i=0; i<(int)tg.size(); i++) for(int v : tg[i]) bucket[--cnt[by[v]]] = std::make_pair(i,v);
    std::vector<int> cnt2(tg.size());
    for(auto [i,v] : bucket) tg[i][cnt2[i]++] = v;
}


std::vector<int> coord_compress_from_arr_by(CSRArray& tg, std::vector<int>& by, int bound){
    int n = tg.size();

    std::vector<int> sorted_tg_idx;
    auto predicate_by_that = [&](int l, int r) -> bool { return by[l] == by[r]; };

    std::vector<int> sa_src;
    std::vector<int> sa_recover;
    for(int i=0; i<n; i++){
        sa_recover.push_back(i);
        for(auto a : tg[i]){
            sa_src.push_back(by[a] + 1);
            sa_recover.push_back(-1);
        }
        sa_src.push_back(0);
    }

    auto sa = atcoder::suffix_array(sa_src, bound);

    for(int i=0; i<(int)sa.size(); i++) if(sa_recover[sa[i]] != -1) sorted_tg_idx.push_back(sa_recover[sa[i]]);
    
    std::vector<int> res(n);
    for(int i=1; i<n; i++){
        res[sorted_tg_idx[i]] = res[sorted_tg_idx[i-1]];
        bool same = std::equal(tg[sorted_tg_idx[i-1]].begin(), tg[sorted_tg_idx[i-1]].end(), tg[sorted_tg_idx[i]].begin(), tg[sorted_tg_idx[i]].end(), predicate_by_that);
        if(!same) res[sorted_tg_idx[i]]++;
    }
    return res;
}

} // namespace internal



struct AHUAlgorithmLinearTime{

    int N;
    std::vector<int> compressed;
    std::vector<int> depth;
    treetourlex_internal::CSRArray children_ordered;
    int root;

    // O(N) time
    AHUAlgorithmLinearTime(const AdjacencyList& E, int new_root = 0){
        root = new_root;
        N = E.num_vertices();
        depth.assign(N, -1);
        std::vector<int> parent(N, -1);
        std::vector<int> bfs = {root};
        bfs.reserve(N);
        depth[0] = 0;
        for(int i=0; i<N; i++){
            int p = bfs[i];
            for(int e : E[p]) if(depth[e] == -1){
                depth[e] = depth[p] + 1;
                parent[e] = p;
                bfs.push_back(e);
            }
        }

        int max_depth = *max_element(depth.begin(), depth.end());
        treetourlex_internal::CSRArray from_depth; {
            std::vector<std::pair<int,int>> elems;
            for(int i=0; i<N; i++) elems.push_back(std::make_pair(depth[i], i));
            from_depth = treetourlex_internal::CSRArray(max_depth+2, elems);
        }

        compressed.assign(N, 0);
        /* children_ordered */ {
            std::vector<std::pair<int,int>> edges;
            for(int p=0; p<N; p++) for(int c : E[p]) if(depth[p] < depth[c]) edges.push_back(std::make_pair(p,c));
            children_ordered = treetourlex_internal::CSRArray(N, edges);
        }

        for(int d = max_depth; d >= 0; d--){
            auto vtxs = from_depth[d];
            treetourlex_internal::CSRArray children_ordered_part; {
                std::vector<std::pair<int,int>> elems;
                for(int i=0; i<(int)vtxs.size(); i++) for(auto p : children_ordered[vtxs[i]]) elems.push_back(std::make_pair(i,p));
                children_ordered_part = treetourlex_internal::CSRArray(vtxs.size(), elems);
            }
            treetourlex_internal::sort_tg_by(children_ordered_part, compressed, from_depth[d+1].size());
            auto compressed_part = treetourlex_internal::coord_compress_from_arr_by(children_ordered_part, compressed, from_depth[d+1].size());
            for(int i=0; i<(int)vtxs.size(); i++) for(int j=0; j<(int)children_ordered_part[i].size(); j++) children_ordered[vtxs[i]][j] = children_ordered_part[i][j];
            for(int i=0; i<(int)vtxs.size(); i++) compressed[vtxs[i]] = compressed_part[i];
        }
    }

    void secondary(){
        std::vector<int> bfs = {root};
        std::vector<int> parent(N, -1);
        std::vector<int> size(N, 1);
        bfs.reserve(N);
        for(int i=0; i<N; i++){
            int p = bfs[i];
            for(int e : children_ordered[p]){
                parent[e] = p;
                bfs.push_back(e);
            }
        }
        for(int i=N-1; i>=1; i--) size[parent[bfs[i]]] += size[bfs[i]];
        std::vector<int> pos(N, 0);
        std::vector<int> brack(N, 0);
        for(int i=0; i<N; i++){
            int p = bfs[i];
            int posv = pos[p] + 1;
            brack[pos[p] + size[p] - 1]++;
            for(int e : children_ordered[bfs[i]]){
                pos[e] = posv;
                posv += size[e];
            }
        }
        auto sa = treetourlex_internal::atcoder::suffix_array(brack, N);
        auto lcp = treetourlex_internal::atcoder::lcp_array(brack, sa);
        std::vector<int> invpos(N, 0);
        for(int i=0; i<N; i++) invpos[pos[i]] = i;
        compressed[invpos[sa[0]]] = 0;
        for(int i=1; i<N; i++){
            int prevtx = invpos[sa[i-1]];
            int vtx = invpos[sa[i]];
            compressed[vtx] = compressed[prevtx];
            if(lcp[i-1] < size[vtx]-1 || size[prevtx] != size[vtx]) compressed[vtx]++;
        }
    }
};



} // namespace nachia


#include <cstdio>

int main(){
    int N; scanf("%d", &N);
    std::vector<std::pair<int,int>> edges(N-1);
    for(int i=1; i<N; i++){
        int p; scanf("%d", &p);
        edges[i-1] = std::make_pair(i,p);
    }
    auto ahu = nachia::AHUAlgorithmLinearTime(nachia::AdjacencyList(N, edges, true));
    ahu.secondary();
    int K = *std::max_element(ahu.compressed.begin(), ahu.compressed.end()) + 1;
    printf("%d\n", K);
    for(int i=0; i<N; i++){
        if(i) printf(" ");
        printf("%d", ahu.compressed[i]);
    }
    printf("\n");
    return 0;
}
