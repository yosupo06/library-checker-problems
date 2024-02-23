#include <cstdio>
#include <cstdlib>
#include <numeric>
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
        if( std::gcd( x, y ) == 1 ) { continue; }
        const int N = gen.uniform( 1ll, MAX_N );

        std::printf( "%d %d %d\n", N, x, y );
        ++i;
    }
}
