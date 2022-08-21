
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

int main(){
    int n; scanf("%d", &n);
    std::vector<int> P(n, -1);
    for(int i=1; i<n; i++) scanf("%d", &P[i]);

    std::vector<std::vector<int>> children(n);
    for(int i=1; i<n; i++) children[P[i]].push_back(i);

    std::map<std::vector<int>, int> reductor;
    std::vector<int> ans(n);
    for(int u=n-1; u>=0; u--){
        std::vector<int> res(children[u].size());
        for(int i=0; i<(int)children[u].size(); i++){
            int c = children[u][i];
            res[i] = ans[c];
        }
        std::sort(res.begin(), res.end());
        if(!reductor.count(res)) reductor.insert(make_pair(res, (int)reductor.size()));
        ans[u] = reductor[res];
    }

    printf("%u\n", (unsigned int)reductor.size());
    for(int i=0; i<n; i++){
        if(i) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
