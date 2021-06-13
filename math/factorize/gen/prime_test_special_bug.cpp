#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

// take numbers from https://miller-rabin.appspot.com/
vector<long long> specials = {1050535501,
                              336781006125,
                              9639812373923155,
                              350269456337,
                              55245642489451,
                              141889084524735,
                              7999252175582851,
                              55245642489451,
                              47636622961201,
                              31858317218647,
                              21652684502221,
                              1122004669633,
                              325,
                              9375,
                              28178,
                              450775,
                              9780504,
                              1795265022,
                              123635709730000,
                              9233062284813009,
                              43835965440333360,
                              761179012939631437,
                              1263739024124850375,
                              585226005592931977};


int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    
    vector<long long> list;
    for (auto x: specials) {
        for (int diff = -10; diff <= 10; diff++) {
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
        int pos = seed * q;
        printf("%lld\n", list[pos % int(buf.size())]);
    }
    return 0;
}
