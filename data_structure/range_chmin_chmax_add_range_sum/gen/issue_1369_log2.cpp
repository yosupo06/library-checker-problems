#include "random.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include "../params.h"

using namespace std;

using ll = long long;

vector<ll> get_fib(ll N){
    vector<ll> fib(N*2+1,1);
    for(ll i=2; i<=N*2; i++) fib[i] = fib[i-1] + fib[i-2];
    return fib;
}

vector<ll> get_hack_sequence(ll N, const vector<ll>& fib){
    vector<ll> A(fib[N*2]);
    A[0] = 1;
    for(ll n=2; n<=N; n++){
        for(ll k=fib[n*2-2]; k<fib[n*2-2]*2; k++) A[k] = A[k-fib[n*2-2]] - fib[n*2-2];
        for(ll k=fib[n*2-2]*2; k<fib[n*2]; k++) A[k] = A[k-fib[n*2-1]] - fib[n*2-1];
        for(ll k=0; k<fib[n*2]; k++) A[k] += fib[n*2];
        A[fib[n*2-2]-1] = fib[n*2-1];
        A[fib[n*2]-1] = 0;
    }
    return A;
}

vector<ll> get_hack_sequence_transitions(ll N, const vector<ll>& fib, vector<ll> A){
    vector<ll> chmax_affects;

    for(ll k=0; k<fib[N*2-1]; k++) A[k] -= fib[N*2-2];
    for(ll k=fib[N*2-1]; k<fib[N*2]; k++) A[k] += fib[N*2-1];
    for(ll k=0; k<fib[N*2]; k++) if(A[k] <= fib[N*2-1]) chmax_affects.push_back(A[k]);
    for(ll k=0; k<fib[N*2]; k++) A[k] = max(A[k], fib[N*2-1]);

    sort(chmax_affects.begin(), chmax_affects.end());
    chmax_affects.erase(unique(chmax_affects.begin(), chmax_affects.end()), chmax_affects.end());

    A[fib[N*2-1]-1] = 0;

    rotate(A.begin(), A.begin() + fib[N*2-1], A.end());
    return chmax_affects;
}

struct Query {
    ll ty, l, r, x;
};

struct Problem {
    vector<ll> initial;
    vector<Query> queries;
};

Problem get_hack_query_sequence(ll max_n, ll max_q, ll K, ll hack_interval_lg2){
    ll hack_interval = 1ll << hack_interval_lg2;
    
    auto fib = get_fib(K);
    auto hack_seq = get_hack_sequence(K, fib);
    auto tr = get_hack_sequence_transitions(K, fib, hack_seq);

    ll hack_len = hack_seq.size();
    ll hack_binsize = 1; while(hack_binsize < hack_len) hack_binsize *= 2;


    ll N = hack_len;
    ll interval_num = 1;
    while(N + hack_interval < max_n){
        interval_num += 1;
        N += hack_interval;
    }

    vector<ll> A(N, tr.back());
    for(ll u=0; u<interval_num; u++){
        for(ll v=0; v<hack_len; v++){
            A[u*hack_interval+v] = hack_seq[v];
        }
    }

    vector<Query> queries;
    auto push = [&](Query q){
        if((ll)queries.size() == max_q) return;
        queries.push_back(q);
    };

    ll cy = 0;
    while((ll)queries.size() < max_q){

        if(cy < fib[K*2-2]){
            push({ 2, 0, N, fib[K*2-1] });
            for(ll offset=0; offset<interval_num*hack_interval; offset+=hack_interval){
                push({ 2, offset + cy, offset + (cy + fib[K*2-1]) % hack_len, -fib[K*2] });
            }
        } else {
            push({ 2, 0, N, -fib[K*2-2] });
            for(ll offset=0; offset<interval_num*hack_interval; offset+=hack_interval){
                push({ 2, offset + (cy + fib[K*2-1]) % hack_len, offset + cy, fib[K*2] });
            }
        }

        for(ll t=1; t<(ll)tr.size(); t++){
            push({ 1, 0, N, tr[t] });
        }

        for(ll offset=0; offset<interval_num*hack_interval; offset+=hack_interval){
            ll zeroing_pos = (cy + fib[K*2-1] - 1) % hack_len;
            push({ 0, offset + zeroing_pos, offset + zeroing_pos + 1, 0 });
        }

        cy = (cy + fib[K*2-1]) % hack_len;
    }

    return { A, queries };
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll num_sumquery = N_AND_Q_MAX / 100;
    
    Problem problem = get_hack_query_sequence(N_AND_Q_MAX, N_AND_Q_MAX - num_sumquery, 5 + seed % 2 * 2, 15 - seed / 2 * 2);

    ll N = problem.initial.size();
    ll Q = problem.queries.size() + num_sumquery;

    vector<ll> query_type(Q);
    for(ll i : gen.choice<ll>(num_sumquery, 0, Q-1)) query_type[i] = 1;
    ll hack_query_ptr = 0;

    printf("%lld %lld\n", N, Q);

    for(ll i=0; i<N; i++){
        if(i) printf(" ");
        printf("%lld", problem.initial[i]);
    } printf("\n");

    for(ll i=0; i<Q; i++){
        if(query_type[i] == 0){
            Query q = problem.queries[hack_query_ptr++];
            printf("%lld %lld %lld %lld\n", q.ty, q.l, q.r, q.x);
        } else {
            auto [l,r] = gen.uniform_pair<ll>(0, N);
            printf("3 %lld %lld\n", l, r);
        }
    }

    return 0;
}
