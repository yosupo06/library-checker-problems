#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

// take numbers from https://miller-rabin.appspot.com/
vector<long long> specials = {341531,
                              291831,
                              126401071349994536,
                              1050535501,
                              336781006125,
                              9639812373923155,
                              350269456337,
                              55245642489451,
                              141889084524735,
                              47636622961201,
                              31858317218647,
                              21652684502221,
                              1122004669633,
                              7999252175582851,
                              4130806001517,
                              149795463772692060,
                              186635894390467037,
                              3770579582154547,
                              3071837692357849,
                              585226005592931977,
                              123635709730000,
                              9233062284813009,
                              43835965440333360,
                              761179012939631437,
                              1263739024124850375,
                              325,
                              9375,
                              28178,
                              450775,
                              9780504,
                              1795265022};


int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    
    vector<long long> list;
    for (auto x: specials) {
        for (int diff = -5; diff <= 5; diff++) {
            list.push_back(x + diff);
        }
        list.push_back(2 * x);
    }

    vector<long long> buf;
    for (auto x: list) {
        if (1 <= x && x <= MAX_A) buf.push_back(x);
    }
    list = buf;

    int q = MAX_Q;
    printf("%d\n", q);
    for (int i = 0; i < q; i++) {
        int pos = seed * q + i;
        printf("%lld\n", list[pos % int(list.size())]);
    }
    return 0;
}
