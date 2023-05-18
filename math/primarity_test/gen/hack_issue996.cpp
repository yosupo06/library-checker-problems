#include <iostream>
#include <cinttypes>
#include "random.h"
#include "../params.h"
#include "../lib/prime.hpp"

using namespace std;
using ll = long long;

// 1 base
const std::vector<ll> t1{
    341531LL,
    291831LL,
    272161LL,
    218245LL,
    212321LL,
    192001LL,
    161701LL,
    132239LL,
    49141LL,
    5329LL,
};
// 2 bases
const std::vector<ll> t2{
    1050535501LL,
    885594169LL,
    716169301LL,
    624732421LL,
    520924141LL,
    466758181LL,
    360018361LL,
    316349281LL,
    227132641LL,
    176609441LL,
    38010307LL,
    19471033LL,
};
// 3 bases
const std::vector<ll> t3{
    350269456337LL,
    273919523041LL,
    242175507817LL,
    220146059407LL,
    154639673381LL,
    109134866497LL,
    105936894253LL,
    75792980677LL,
    4759123141LL,
};
// 4 bases
const std::vector<ll> t4{
    55245642489451LL,
    47636622961201LL,
    31858317218647LL,
    21652684502221LL,
    1122004669633LL,
};
// 5 bases
const std::vector<ll> t5{
    7999252175582851LL,
    3770579582154547LL,
    3071837692357849LL,
};
// 6 bases
const std::vector<ll> t6{
    585226005592931977LL,
};

int main(int, char*[]) {
    std::vector<ll> t_all;
    std::copy(t1.begin(), t1.end(), std::back_inserter(t_all));
    std::copy(t2.begin(), t2.end(), std::back_inserter(t_all));
    std::copy(t3.begin(), t3.end(), std::back_inserter(t_all));
    std::copy(t4.begin(), t4.end(), std::back_inserter(t_all));
    std::copy(t5.begin(), t5.end(), std::back_inserter(t_all));
    std::copy(t6.begin(), t6.end(), std::back_inserter(t_all));

    int Q = t_all.size();
    printf("%d\n", Q);
    for(int i = 0; i < Q; i++) {
        printf("%lld\n", t_all[i]);
    }
}
