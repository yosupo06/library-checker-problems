
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

        int seekBeg = 0;
        int len = (int)(last - first);

        while(seekBeg < len){
            // find a repetition of the longest lyndon prefix

            int repEndPrev = seekBeg;
            int repEnd = seekBeg + 1;
            // factor length = repEnd - repEndPrev

            while(repEnd < len && !comp(first[repEnd], first[repEndPrev])){
                if(comp(first[repEndPrev], first[repEnd])){
                    repEndPrev = seekBeg;
                    repEnd++;
                }
                else{
                    repEndPrev++;
                    repEnd++;
                }
            }

            int factorLen = repEnd - repEndPrev;
            for( ; seekBeg <= repEndPrev; seekBeg += factorLen){
                res.pos.push_back(seekBeg + factorLen);
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
