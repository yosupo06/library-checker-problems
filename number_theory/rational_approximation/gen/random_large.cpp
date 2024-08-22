#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include "random.h"
#include "../params.h"

int main( int, char* argv[] ) {
    const long long seed = std::atoll( argv[1] );
    auto gen = Random( seed );

    const int T = MAX_T;
    std::printf( "%d\n", T );

    for( int i = 0; i < T; ++i ) {
        const int x = gen.uniform( MAX_N * 2 / 3, MAX_N );
        const int y = gen.uniform( 1ll, MAX_N );
        const int N = gen.uniform( MAX_N / 2, std::max( x, y ) - 1ll ); // avoid trivial case

        if( gen.uniform_bool() ) {
            std::printf( "%d %d %d\n", N, x, y );
        } else {
            std::printf( "%d %d %d\n", N, y, x );
        }
    }
}
