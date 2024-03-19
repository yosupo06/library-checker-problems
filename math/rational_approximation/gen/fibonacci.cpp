#include <cstdio>
#include <cstdlib>
#include <tuple>
#include "random.h"
#include "../params.h"

int main( int, char* argv[] ) {
    const long long seed = std::atoll( argv[1] );
    auto gen = Random( seed );

    int f0 = 0;
    int f1 = 1;
    while( f0 + f1 < MAX_N ) {
        std::tie( f0, f1 ) = std::tuple( f1, f0 + f1 );
    }

    const int T = MAX_T;
    std::printf( "%d\n", T );

    for( int i = 0; i < T; ++i ) {
        const int N = gen.uniform( f0, f1 - 1 ); // avoid trivial case
        if( gen.uniform_bool() ) {
            std::printf( "%d %d %d\n", N, f0, f1 );
        } else {
            std::printf( "%d %d %d\n", N, f1, f0 );
        }
    }
}
