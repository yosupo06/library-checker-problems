#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

struct Fraction {
    long long numerator;
    long long denominator;

    bool is_expressible_up_to( int N ) const {
        return numerator <= N && denominator <= N;
    }
};

Fraction freshman_fma( Fraction a, int b, Fraction c ) {
    return { a.numerator * b + c.numerator, a.denominator * b + c.denominator };
}

Fraction generate_fraction( Fraction a, Fraction b, Random& gen, long long max_run_length ) {
    if( not b.is_expressible_up_to( MAX_N ) ) { return a; }

    const int run_length = gen.uniform( 1ll, max_run_length );
    return generate_fraction( b, freshman_fma( b, run_length, a ), gen, max_run_length );
}

int main( int, char* argv[] ) {
    const long long seed = std::atoll( argv[1] );
    auto gen = Random( seed );

    const int T = MAX_T;
    std::printf( "%d\n", T );

    for( int i = 0; i < T; ++i ) {
        const Fraction f = generate_fraction( { 0, 1 }, { 1, 0 }, gen, seed + 1 );
        const int N = gen.uniform( 1ll, std::max( f.numerator, f.denominator ) - 1 ); // avoid trivial case

        if( gen.uniform_bool() ) {
            std::printf( "%d %lld %lld\n", N, f.numerator, f.denominator );
        } else {
            std::printf( "%d %lld %lld\n", N, f.denominator, f.numerator );
        }
    }
}
