#include <cstdio>
#include <vector>
#include <algorithm>

template<class Int = long long>
std::vector<Int> EnumerateQuotients(Int N, bool doInsertZero){
    std::vector<Int> res;
    if(doInsertZero) res.push_back(0);
    Int f = 1;
    for( ; f*f<N; f++) res.push_back(f);
    int qp1 = res.size();
    for(Int k=1; k*f<=N; k++){
        res.push_back((k&1) ? (N/k) : (res[qp1+k/2-1]/2));
    }
    std::reverse(res.begin() + qp1, res.end());
    return res;
}

int main() {
    long long N; scanf("%lld", &N);
    std::vector<long long> ans = EnumerateQuotients(N, false);
    printf("%d\n", (int)ans.size());
    for(std::size_t i=0; i<ans.size(); i++){
        if(i != 0) printf(" ");
        printf("%lld", ans[i]);
    }
    printf("\n");
    return 0;
}
