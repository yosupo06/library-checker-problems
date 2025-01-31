#include <vector>
#include <utility>
#include <numeric>

// enumerate (a,b) (0<=a,b , gcd(a,b) = 1) in the (a+b,a)-ascending order
// while sum a <= a_sum_lim
//   and sum b <= b_sum_lim
//   and # <= n
std::vector<std::pair<int,int>>
distinct_fractions(int n, long long a_sum_lim, long long b_sum_lim){
    std::vector<std::pair<int,int>> res;
    for(int d=1; ; d++){
        if(a_sum_lim + b_sum_lim < d) break;
        for(int a=1; a<d; a++){
            int b = d - a;
            if(a%2 == 0 && b%2 == 0) continue;
            if(std::gcd(a, b) != 1) continue;
            if(a_sum_lim < a) continue;
            if(b_sum_lim < b) continue;
            res.push_back({ a, b });
            if(int(res.size()) == n) return res;
        }
    }
    return res;
}

bool compare_fractions(const std::pair<int,int>& l, const std::pair<int,int>& r){
    return (long long)l.first * r.second < (long long)r.first * l.second;
}

void sort_fractions(std::vector<std::pair<int,int>>& a){
    std::sort(a.begin(), a.end(), compare_fractions);
}
