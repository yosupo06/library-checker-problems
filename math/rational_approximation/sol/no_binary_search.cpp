#include <cstdio>
#include <utility>
#include <cmath>

struct Fraction {
    int numerator;
    int denominator;

    bool operator<( Fraction rhs ) const {
        return 1ll * numerator * rhs.denominator < 1ll * denominator * rhs.numerator;
    }
    bool is_expressible_up_to( int N ) const {
        return numerator <= N && denominator <= N;
    }
};

Fraction freshman_sum( Fraction a, Fraction b ) {
    return { a.numerator + b.numerator, a.denominator + b.denominator };
}

std::pair<Fraction, Fraction> solve( int N, Fraction f ) {
    Fraction lower { 0, 1 };
    Fraction upper { 1, 0 };
    for( ; ; ) {
        const Fraction mediant = freshman_sum( lower, upper );
        if( not mediant.is_expressible_up_to( N ) ) { break; }
        if( mediant < f ) { lower = mediant; }
        else if( f < mediant ) { upper = mediant; }
        else { lower = upper = mediant; break; }
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
        std::printf( "%d %d %d %d\n", lower_max.numerator, lower_max.denominator, upper_min.numerator, upper_min.denominator );
    }
}
