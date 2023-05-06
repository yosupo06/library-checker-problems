// reduced, and modified a bit

#ifndef ATCODER_STRING_HPP
#define ATCODER_STRING_HPP 1

#include <algorithm>
#include <cassert>
#include <numeric>
#include <string>
#include <vector>

namespace atcoder {

namespace internal {

std::vector<int> sa_naive(const std::vector<int>& s){
    int n = int(s.size());
    std::vector<int> sa(n);
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](int l, int r){
        return std::lexicographical_compare(
            s.begin() + l, s.end(),
            s.begin() + r, s.end()
        );
    });
    return sa;
}

template <int THRESHOLD_NAIVE = 10, int THRESHOLD_DOUBLING = 40>
std::vector<int> sa_is(const std::vector<int>& s, int upper){
    int n = int(s.size());
    if(n == 0) return {};
    if(n == 1) return {0};
    if(n == 2){
        if(s[0] < s[1]) return {0, 1}; else return {1, 0};
    }

    if(n < THRESHOLD_NAIVE) return sa_naive(s);

    std::vector<int> sa(n);
    std::vector<bool> ls(n);
    for(int i=n-2; i>=0; i--){
        ls[i] = (s[i] == s[i+1]) ? ls[i+1] : (s[i] < s[i+1]);
    }
    std::vector<int> sum_l(upper+1), sum_s(upper+1);
    for(int i=0; i<n; i++) if(!ls[i]) sum_s[s[i]]++; else sum_l[s[i]+1]++;
    for(int i=0; i<=upper; i++){
        sum_s[i] += sum_l[i];
        if(i < upper) sum_l[i+1] += sum_s[i];
    }

    auto induce = [&](const std::vector<int>& lms){
        std::fill(sa.begin(), sa.end(), -1);
        std::vector<int> buf(upper+1);
        std::copy(sum_s.begin(), sum_s.end(), buf.begin());
        for(auto d : lms) if(d != n) sa[buf[s[d]]++] = d;
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        sa[buf[s[n-1]]++] = n-1;
        for(int i=0; i<n; i++){
            int v = sa[i];
            if(v >= 1 && !ls[v-1]) sa[buf[s[v-1]]++] = v-1;
        }
        std::copy(sum_l.begin(), sum_l.end(), buf.begin());
        for(int i=n-1; i>=0; i--){
            int v = sa[i];
            if(v >= 1 && ls[v-1]) sa[--buf[s[v-1]+1]] = v-1;
        }
    };

    std::vector<int> lms_map(n+1, -1);
    int m = 0;
    for(int i=1; i<n; i++) if(!ls[i-1] && ls[i]) lms_map[i] = m++;
    std::vector<int> lms;
    lms.reserve(m);
    for(int i=1; i<n; i++) if(!ls[i-1] && ls[i]) lms.push_back(i);

    induce(lms);

    if(m){
        std::vector<int> sorted_lms;
        sorted_lms.reserve(m);
        for(int v : sa) if(lms_map[v] != -1) sorted_lms.push_back(v);
        std::vector<int> rec_s(m);
        int rec_upper = 0;
        rec_s[lms_map[sorted_lms[0]]] = 0;
        for(int i=1; i<m; i++){
            int l = sorted_lms[i-1], r = sorted_lms[i];
            int end_l = (lms_map[l]+1 < m) ? lms[lms_map[l]+1] : n;
            int end_r = (lms_map[r]+1 < m) ? lms[lms_map[r]+1] : n;
            bool same = true;
            if(end_l - l != end_r - r){
                same = false;
            } else {
                while(l < end_l){
                    if(s[l] != s[r]) break;
                    l++;
                    r++;
                }
                if(l == n || s[l] != s[r]) same = false;
            }
            if(!same) rec_upper++;
            rec_s[lms_map[sorted_lms[i]]] = rec_upper;
        }

        auto rec_sa = sa_is<THRESHOLD_NAIVE, THRESHOLD_DOUBLING>(rec_s, rec_upper);

        for(int i=0; i<m; i++) sorted_lms[i] = lms[rec_sa[i]];
        induce(sorted_lms);
    }
    return sa;
}

}  // namespace internal

std::vector<int> suffix_array(const std::vector<int>& s, int upper){
    assert(0 <= upper);
    for(int d : s) assert(0 <= d && d <= upper);
    auto sa = internal::sa_is(s, upper);
    return sa;
}

std::vector<int> suffix_array(const std::string& s){
    int n = int(s.size());
    std::vector<int> s2(n);
    for(int i=0; i<n; i++) s2[i] = s[i];
    return internal::sa_is(s2, 255);
}

std::vector<int> z_algorithm(const std::string& s){
    int n = int(s.size());
    if(n == 0) return {};
    std::vector<int> z(n);
    z[0] = 0;
    for(int i=1, j = 0; i<n; i++){
        int& k = z[i];
        k = (j + z[j] <= i) ? 0 : std::min(j + z[j] - i, z[i-j]);
        while(i+k < n && s[k] == s[i+k]) k++;
        if(j + z[j] < i + z[i]) j = i;
    }
    z[0] = n;
    return z;
}

}  // namespace atcoder

#endif  // ATCODER_STRING_HPP
