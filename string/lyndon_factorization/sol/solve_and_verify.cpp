
#include <vector>
#include <string>
#include <functional>
#include <iterator>

struct LyndonFactorization {
    std::vector<int> pos;
    LyndonFactorization() : pos({0}) {}
    int numFactors() const { return (int)pos.size() - 1; }
    int beginOf(int i) const { return pos[i]; }
    int endOf(int i) const { return pos[i+1]; }
    template<class RandomAccessIter, class Comp>
    static LyndonFactorization FromStr(
        RandomAccessIter first,
        RandomAccessIter last,
        const Comp& comp
    ){
        LyndonFactorization res;
        if(first == last) return res;
        int pos = 1;
        int sameBeg = 0;
        int prevBeg = 0;
        int prevEnd = 1;
        int len = (int)(last - first);
        while(pos <= len){
            int i = pos - prevEnd;
            if(pos == len || comp(first[prevEnd + i], first[prevBeg + i])){
                int prevLen = prevEnd - prevBeg;
                for(int t = sameBeg + prevLen; t <= prevEnd; t += prevLen){
                    res.pos.push_back(t);
                }
                sameBeg = prevEnd;
                prevBeg = prevEnd;
                prevEnd = prevEnd + 1;
                pos = prevEnd;
                continue;
            }
            if(comp(first[prevBeg + i], first[prevEnd + i])){
                prevEnd = pos + 1;
                prevBeg = sameBeg;
            }
            pos++;
            if(prevEnd - prevBeg == pos - prevEnd){
                prevBeg = prevEnd;
                prevEnd = pos;
            }
        }
        return res;
    }
    template<class RandomAccessIter>
    static LyndonFactorization FromStr(
        RandomAccessIter first,
        RandomAccessIter last
    ){
        using Ty = typename std::iterator_traits<RandomAccessIter>::value_type;
        return FromStr(first, last, std::less<Ty>());
    }
};

template<class Iter>
std::vector<int> SuffixArray(
    Iter first,
    Iter last
){
    int n = std::distance(first, last);
    if(n == 0) return {};
    if(n == 1) return {0};
    std::vector<int> sa(n), rnk(n+1), tmp(n);
    for(int i=0; i<n; i++) sa[i] = i;
    std::sort(sa.begin(), sa.end(), [&](int l, int r) -> bool { return first[l] < first[r]; });
    rnk[sa[0]] = 0;
    for(int i=0; i<n-1; i++) rnk[sa[i+1]] = rnk[sa[i]] + ((first[sa[i]] < first[sa[i+1]]) ? 1 : 0);
    rnk[n] = -1;
    int k = 1;
    while(k < n){
        auto cmpi = [n,k,&rnk](int l, int r) -> bool {
            if(rnk[l] != rnk[r]) return rnk[l] < rnk[r];
            return rnk[std::min(n,l+k)] < rnk[std::min(n,r+k)];
        };
        std::sort(sa.begin(), sa.end(), cmpi);
        tmp[sa[0]]=0;
        for(int i=0; i<n-1; i++) tmp[sa[i+1]] = tmp[sa[i]] + (cmpi(sa[i],sa[i+1]) ?1:0);
        for(int i=0; i<n; i++) rnk[i] = tmp[i];
        k *= 2;
    }
    for(int i=0; i<n; i++) sa[rnk[i]]=i;
    return sa;
}

#include <cstring>
#include <cassert>

int main() {
    static char buf[2'000'000];
    scanf("%s", buf);

    int len = strlen(buf);

    auto lyndon = LyndonFactorization::FromStr(buf, buf + len).pos;

    assert(!lyndon.empty());
    assert(lyndon.front() == 0);
    assert(lyndon.back() == len);
    int num_components = lyndon.size() - 1;
    for(int i=0; i<num_components; i++){
        assert(SuffixArray(buf + lyndon[i], buf + lyndon[i+1])[0] == 0);
    }
    for(int i=0; i+1<num_components; i++){
        bool a_lt_b = std::lexicographical_compare(
            buf + lyndon[i], buf + lyndon[i+1],
            buf + lyndon[i+1], buf + lyndon[i+2]
        );
        assert(!a_lt_b);
    }

    for(int i=0; i<(int)lyndon.size(); i++) {
        if(i) printf(" ");
        printf("%d", lyndon[i]);
    }
    printf("\n");

    return 0;
}
