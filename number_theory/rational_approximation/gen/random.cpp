#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

int main( int, char* argv[] ) {
    const long long seed = std::atoll( argv[1] );
    auto gen = Random( seed );

    const int T = gen.uniform( 1ll, MAX_T );
    std::printf( "%d\n", T );

    for( int i = 0; i < T; ++i ) {
        const int N = gen.uniform( 1ll, MAX_N );
        const int x = gen.uniform( 1ll, MAX_N );
        const int y = gen.uniform( 1ll, MAX_N );

        std::printf( "%d %d %d\n", N, x, y );
    }
}
