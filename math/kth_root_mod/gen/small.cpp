#include <iostream>

bool is_prime(long long a){
  for (long long div=2;div*div<=a;++div){
    if(a%div==0)return false;
  }
  return true;
}

int main() {
  int t = 2397;
  printf("%d\n", t);
  int q=0;
  for (long long p=2;p<30;++p){
    if (!is_prime(p))continue;
    for (long long k=0;k<p;++k){
      for (long long y=0;y<p;++y){
        printf("%lld %lld %lld\n", k, y, p);
        ++q;
      }
    }
  }
  return 0;
}
