#include <cstdio>
#include <cstdlib>
#include <vector>
#include <tuple>
#include "../params.h"

int main( int, char* argv[] ) {
    const long long seed = atoll( argv[1] );

    constexpr int small_max = 100;

    int task = 0;
    std::vector<std::tuple<int, int, int>> v;
    for( int N = 1; N <= small_max; ++N ) {
        for( int x = 1; x <= small_max; ++x ) {
            for( int y = 1; y <= small_max; ++y ) {
                if( task / MAX_T == seed ) {
                    v.emplace_back( N, x, y );
                }
                ++task;
            }
        }
    }

    std::printf( "%zu\n", v.size() );
    for( const auto [N, x, y] : v ) {
        std::printf( "%d %d %d\n", N, x, y );
    }
}
