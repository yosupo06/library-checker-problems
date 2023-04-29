#include <cstdio>
#include <vector>
#include <algorithm>

template<class Int = long long>
std::vector<Int> EnumerateQuotients(Int N, bool doInsertZero){
    std::vector<Int> res;
    for(Int i=1; ; i++){
        res.push_back(N/i);
        if(res.size() >= 2 && (res[res.size()-1] == res[res.size()-2])) break;
    }
    while(res.back() >= 2) res.push_back(res.back() - 1);
    res.push_back(0);
    std::sort(res.begin(), res.end());
    res.erase(std::unique(res.begin(), res.end()), res.end());
    if(!doInsertZero) return std::vector<Int>(res.begin() + 1, res.end());
    return res;
}

int main() {
    long long N; scanf("%lld", &N);
    std::vector<long long> ans = EnumerateQuotients(N, false);
    for(std::size_t i=0; i<ans.size(); i++){
        if(i != 0) printf(" ");
        printf("%lld", ans[i]);
    }
    printf("\n");
    return 0;
}
