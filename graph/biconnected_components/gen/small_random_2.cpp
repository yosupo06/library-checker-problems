#include <cstdio>
#include <vector>
#include "random.h"
#include "../params.h"


std::vector<int> generate_bct(Random& gen, int n){
    std::vector<int> res(n*2+1, -1);
    for(int i=0; i<n; i++){
        int p = gen.uniform<int>(0, i);
        res[i*2+1] = p*2;
        res[i*2+2] = i*2+1;
    }
    return res;
}

std::vector<std::pair<int, int>> bct_to_edges(Random& gen, std::vector<int> bctparents, int n, int m){
    int bctn = bctparents.size();
    assert(2 <= n);
    assert(1 <= bctn);
    assert(bctparents[0] == -1);
    for(int i=1; i<bctn; i++) assert(0 <= bctparents[i] && bctparents[i] < i);
    while(bctn > n*2+1){ bctn--; bctparents.pop_back(); }

    std::vector<int> color(bctn, 0);
    // 0 : block
    // 1 : articulation
    for(int i=1; i<bctn; i++) color[i] = 1 - color[bctparents[i]];

    std::vector<std::vector<int>> bctadj(bctn);
    for(int i=1; i<bctn; i++){
        int p = bctparents[i];
        bctadj[i].push_back(p);
        bctadj[p].push_back(i);
    }
    
    int n_left = n;
    std::vector<int> arti_vtx(bctn, -1);
    std::vector<std::vector<int>> blocks(bctn);
    for(int i=0; i<bctn; i++) if(color[i] == 1){
        if(1 <= n_left){
            arti_vtx[i] = --n_left;
            for(int e : bctadj[i]) blocks[e].push_back(arti_vtx[i]);
        }
    }

    for(int i=0; i<(int)blocks.size(); i++){
        if(blocks[i].empty()){
            std::swap(blocks[i], blocks.back());
            blocks.pop_back();
            i--;
        }
    }

    while(n_left){
        int block_id = gen.uniform<int>(0, blocks.size()-1);
        blocks[block_id].push_back(--n_left);
    }

    for(int i=0; i<(int)blocks.size(); i++){
        if(blocks[i].size() <= 1){
            std::swap(blocks[i], blocks.back());
            blocks.pop_back();
            i--;
        }
    }

    std::vector<std::pair<int,int>> res;
    for(int edgeid=0; edgeid<m; edgeid++){
        int block_id = gen.uniform<int>(0, blocks.size()-1);
        assert(blocks[block_id].size() >= 2);
        int ui = gen.uniform<int>(0, blocks[block_id].size()-1);
        int vi = gen.uniform<int>(0, blocks[block_id].size()-2);
        if(ui <= vi) vi++;
        res.push_back({ blocks[block_id][ui], blocks[block_id][vi] });
    }
    return res;
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(std::max<int>(30, N_MIN), 100);
    int m = gen.uniform<int>(std::max<int>(100, M_MIN), 200);
    printf("%d %d\n", n, m);

    int arti_count = 3 + gen.uniform<int>(0, n / 5);
    auto edges = bct_to_edges(gen, generate_bct(gen, arti_count), n, m);
    
    auto vperm = gen.perm<int>(n);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        edges[i] = { vperm[u], vperm[v] };
    }

    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        printf("%d %d\n", u, v);
    }
    return 0;
}
