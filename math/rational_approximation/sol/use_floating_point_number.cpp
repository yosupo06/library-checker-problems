#include <cstdio>
#include <utility>
#include <cmath>

struct Fraction {
    long long numerator;
    long long denominator;

    operator double() const { return 1. * numerator / denominator; }
    bool is_expressible_up_to( int N ) const {
        return numerator <= N && denominator <= N;
    }
};

Fraction freshman_fma( Fraction a, int b, Fraction c ) {
    return { a.numerator * b + c.numerator, a.denominator * b + c.denominator };
}

template<class Pred>
int binary_search( const Pred& pred ) {
    int ok = 0;
    int ng = 1 << 30;
    while( std::abs( ok - ng ) > 1 ) {
        const int mid = ( ok + ng ) / 2;
        if( pred( mid ) ) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}

std::pair<Fraction, Fraction> solve( int N, Fraction f ) {
    Fraction lower { 0, 1 };
    Fraction upper { 1, 0 };
    for( ; ; ) {
        const int n1 = binary_search( [&]( int n ) { Fraction f1 = freshman_fma( upper, n, lower ); return f1.is_expressible_up_to( N ) && f1 <= f; } );
        lower = freshman_fma( upper, n1, lower );
        if( lower == f ) { upper = lower; break; }

        const int n2 = binary_search( [&]( int n ) { Fraction f2 = freshman_fma( lower, n, upper ); return f2.is_expressible_up_to( N ) && f <= f2; } );
        upper = freshman_fma( lower, n2, upper );
        if( upper == f ) { lower = upper; break; }

        if( n1 == 0 && n2 == 0 ) { break; }
    }
    return { lower, upper };
}

int main() {
    int T;
    std::scanf( "%d", &T );

    while( T-- ) {
        int N, x, y;
        std::scanf( "%d %d %d", &N, &x, &y );
        const auto [lower_max, upper_min] = solve( N, { x, y } );
        std::printf( "%lld %lld %lld %lld\n", lower_max.numerator, lower_max.denominator, upper_min.numerator, upper_min.denominator );
    }
}
