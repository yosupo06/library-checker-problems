#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

int main(){
  int n=(int)sqrt(N_MAX);
  printf("%d\n",n*n);
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      printf("%d %d\n",i,j);
    }
  }
  return 0;
}
