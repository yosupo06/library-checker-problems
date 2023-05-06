
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

#include <cstring>

int main() {
    static char buf[2'000'000];
    scanf("%s", buf);

    int len = strlen(buf);

    auto lyndon = LyndonFactorization::FromStr(buf, buf + len).pos;

    for(int i=0; i<(int)lyndon.size(); i++) {
        if(i) printf(" ");
        printf("%d", lyndon[i]);
    }
    printf("\n");

    return 0;
}
