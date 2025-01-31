#include <vector>
#include <utility>

std::vector<int>
typical_tree_path(int N){
    std::vector<int> res(N, -1);
    for(int i=1; i<N; i++) res[i] = i-1;
    return res;
}

std::vector<int>
typical_tree_star0(int N){
    std::vector<int> res(N, -1);
    for(int i=1; i<N; i++) res[i] = 0;
    return res;
}

std::vector<int>
typical_tree_star1(int N){
    std::vector<int> res(N, -1);
    res[1] = 0;
    for(int i=2; i<N; i++) res[i] = 1;
    return res;
}

std::vector<int>
typical_tree_binary(int N){
    std::vector<int> res(N, -1);
    for(int i=1; i<N; i++) res[i] = (i-1)/2;
    return res;
}
