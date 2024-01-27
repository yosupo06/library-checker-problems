
// ref. https://www.mathenachia.blog/assign-segtree-nonamortized/

#pragma once
#include <vector>
#include <algorithm>

namespace nachia {

template<class Elem>
struct RangeSetRangeProduct {
private:
    int N;
    int logN;
    std::vector<int> lazy;
    std::vector<int> nodeRank;
    std::vector<Elem> lazyTable;
    std::vector<Elem> prod;
    int tableIterator;
    int bitReverse(int x){
        int y = 0;
        for(int i=0; i<logN; i++){
            y = (y << 1) | (x & 1);
            x >>= 1;
        }
        return y;
    }
    void apply(int p, int k){
        if(p < N) lazy[p] = k;
        prod[p] = lazyTable[(k+N*2-nodeRank[p]) & (N*2-1)];
    }
    void propagate(int p){
        if(p >= N || lazy[p] == -1) return;
        apply(p*2, lazy[p]);
        apply(p*2+1, lazy[p]);
        lazy[p] = -1;
    }
    void propagateFor(int p){
        p += N;
        for(int d=logN; d>=1; d--) propagate(p>>d);
    }
    void rangeUpdateRecursion(int l, int r, int k, int i, int a, int b){
        if(b <= l || r <= a) return;
        if(l <= a && b <= r){ apply(i, k); return; }
        propagate(i);
        rangeUpdateRecursion(l, r, k, i*2, a, (a+b)/2);
        rangeUpdateRecursion(l, r, k, i*2+1, (a+b)/2, b);
        prod[i] = prod[i*2] * prod[i*2+1];
    }
    Elem rangeProductRecursion(int l, int r, int i, int a, int b){
        if(l <= a && b <= r) return prod[i];
        propagate(i);
        if(r <= (a+b)/2) return rangeProductRecursion(l, r, i*2, a, (a+b)/2);
        if((a+b)/2 <= l) return rangeProductRecursion(l, r, i*2+1, (a+b)/2, b);
        Elem lq = rangeProductRecursion(l, r, i*2, a, (a+b)/2);
        Elem rq = rangeProductRecursion(l, r, i*2+1, (a+b)/2, b);
        return lq * rq;
    }
public:
    RangeSetRangeProduct(int n, Elem filler){
        N = 1; logN = 0; while(N < n){ N *= 2; logN++; }
        tableIterator = 0;
        lazy.assign(N, -1);
        nodeRank.assign(N*2, N);
        for(int i=N-1; i>=1; i--) nodeRank[i] = nodeRank[i*2] >> 1;
        lazyTable.assign(N*2, filler);
        prod.assign(N*2, filler);
        for(int i=N-1; i>=1; i--) prod[i] = prod[i*2] * prod[i*2+1];
    }
    void assign(int l, int r, Elem x){
        int k = tableIterator++;
        if(tableIterator == N*2) tableIterator = 0;
        lazyTable[(k+N*2-N) & (N*2-1)] = x;
        for(int i=1; i<=logN; i++){
            x = x * x;
            lazyTable[(k+N*2-(N>>i)) & (N*2-1)] = x;
        }
        rangeUpdateRecursion(l, r, k, 1, 0, N);
        propagateFor(bitReverse(k&(N-1)));
    }
    // l < r
    Elem fold(int l, int r){
        return rangeProductRecursion(l, r, 1, 0, N);
    }
};

} // namespace nachia
