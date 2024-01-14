#include <iostream>
#include <tuple>
#include "random.h"
#include "../params.h"

/*

4 cases
case 0,1 : n = 4*5
case 2,3 : n = 3*7 ( random 1 removed )

*/

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    
    int n1 = 4;
    int n2 = 5; // size of a cycle : an odd number
    if(seed / 2 == 1){
        n1 = 3;
        n2 = 7;
    }

    int n = n1 * n2;

    vector<pair<int,int>> edges;

    if(seed % 2 == 0){
        for(int c=0; c<n; c+=n1){
            // make a clique on i \in [c, c+n1)
            for(int a=0; a<n1; a++){
                for(int b=0; b<a; b++){
                    edges.push_back({ c+a, c+b });
                }
            }
        }
        // connect cliques like a cycle
        for(int c=0; c<n; c+=n1){
            int d = (c + n1) % n;
            for(int a=0; a<n1; a++){
                for(int b=0; b<n1; b++){
                    edges.push_back({ c+a, d+b });
                }
            }
        }
    }
    else if(seed % 2 == 1){
        for(int c=0; c<n; c+=n1){
            // make a clique on i \in [c, c+n1)
            for(int a=0; a<n1; a++){
                int b = (a+1) % n1;
                edges.push_back({ c+a, c+b });
            }
        }
        // connect cliques like a cycle
        for(int c=0; c<n; c+=n1){
            for(int d=0; d<c; d+=n1){
                for(int a=0; a<n1; a++){
                    for(int b=0; b<n1; b++){
                        edges.push_back({ c+a, d+b });
                    }
                }
            }
        }
    }
    
    // permute edges
    gen.shuffle(edges.begin(), edges.end());
    int m = (int)edges.size();

    vector<int> perm(n);
    for(int i=0; i<n; i++) perm[i] = i;
    gen.shuffle(perm.begin(), perm.end());
    for(int i=0; i<m; i++){
        // flip edges
        if(gen.uniform_bool()) swap(edges[i].first, edges[i].second);
        // permute vertices
        edges[i].first = perm[edges[i].first];
        edges[i].second = perm[edges[i].second];
    }

    n = MAX_N; {
        vector<pair<int,int>> edges_filtered;
        for(auto e : edges){
            if(e.first < n && e.second < n){
                edges_filtered.push_back(e);
            }
        }
        swap(edges, edges_filtered);
        m = (int)edges.size();
    }

    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        printf("%d %d\n", edges[i].first, edges[i].second);
    }
    return 0;
}