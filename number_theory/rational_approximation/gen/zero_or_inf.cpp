#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

int main( int, char* argv[] ) {
    const long long seed = std::atoll( argv[1] );
    auto gen = Random( seed );

    const int T = MAX_T;
    std::printf( "%d\n", T );

    for( int i = 0; i < T; ) {
        const int x = gen.uniform( 1ll, MAX_N );
        const int y = gen.uniform( 1ll, MAX_N );
        const int m = x < y ? y / x : x / y;
        if( m == 1 ) { continue; }
        const int N = gen.uniform( 1ll, m - 1ll );

        std::printf( "%d %d %d\n", N, x, y );
        ++i;
    }
}
