#pragma once

long long Gcd(long long x, long long y){
    if(x < 0) x *= -1;
    if(y < 0) y *= -1;
    if(x < y){ long long c = x; x = y; y = c; }
    while(y != 0){
        x %= y;
        long long c = x; x = y; y = c;
    }
    return x;
}
