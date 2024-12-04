#include <vector>
#include <utility>
#include <cstdio>

void
case_output(int n, const std::vector<int>& parent, const std::vector<std::pair<int,int>>& cd){
    printf("%d\n", n);
    for(int i=1; i<n; i++){
        if(i != 1) printf(" ");
        printf("%d", parent[i]);
    }
    printf("\n");
    for(int i=0; i<n; i++){
        if(i != 0) printf(" ");
        printf("%d", cd[i].first);
    }
    printf("\n");
    for(int i=0; i<n; i++){
        if(i != 0) printf(" ");
        printf("%d", cd[i].second);
    }
    printf("\n");
}

void
case_output_split(int n, const std::vector<int>& parent, const std::vector<int>& C, const std::vector<int>& D){
    printf("%d\n", n);
    for(int i=1; i<n; i++){
        if(i != 1) printf(" ");
        printf("%d", parent[i]);
    }
    printf("\n");
    for(int i=0; i<n; i++){
        if(i != 0) printf(" ");
        printf("%d", C[i]);
    }
    printf("\n");
    for(int i=0; i<n; i++){
        if(i != 0) printf(" ");
        printf("%d", D[i]);
    }
    printf("\n");
}
