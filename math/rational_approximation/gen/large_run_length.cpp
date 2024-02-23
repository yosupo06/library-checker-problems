#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

struct Fraction {
    long long numerator;
    long long denominator;
};

Fraction freshman_fma( Fraction a, int b, Fraction c ) {
    return { a.numerator * b + c.numerator, a.denominator * b + c.denominator };
}

int search_max( Fraction a, Fraction b ) {
    const int m1 = b.numerator == 0 ? MAX_N : ( MAX_N - a.numerator ) / b.numerator;
    const int m2 = b.denominator == 0 ? MAX_N : ( MAX_N - a.denominator ) / b.denominator;
    return std::min( m1, m2 );
}

Fraction generate_fraction( Fraction a, Fraction b, Random& gen ) {
    const int m = search_max( a, b );
    if( m == 0 ) { return b; }

    const int max_run_length = gen.uniform_bool() ? std::min( 42, m ) : m;
    const int run_length = gen.uniform( 1, max_run_length );
    return generate_fraction( b, freshman_fma( b, run_length, a ), gen );
}

int main( int, char* argv[] ) {
    const long long seed = std::atoll( argv[1] );
    auto gen = Random( seed );

    const int T = MAX_T;
    std::printf( "%d\n", T );

    for( int i = 0; i < T; ++i ) {
        const auto f = generate_fraction( { 0, 1 }, { 1, 0 }, gen );
        const int N = gen.uniform( 1ll, std::max( f.numerator, f.denominator ) - 1 ); // avoid trivial case

        if( gen.uniform_bool() ) {
            std::printf( "%d %lld %lld\n", N, f.numerator, f.denominator );
        } else {
            std::printf( "%d %lld %lld\n", N, f.denominator, f.numerator );
        }
    }
}
