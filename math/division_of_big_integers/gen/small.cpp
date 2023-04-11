#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#include "../params.h"

int main() {
  vector<string> A, B;
  int lsum = 0, flag = true;
  for (int i = 0; flag; i++) {
    for (int j = 1; j <= i * 2 + 10 && flag; j++) {
      string sa = to_string(i);
      string sb = to_string(j);
      lsum += sa.size() + sb.size();
      if (lsum > SUM_OF_CHARACTER_LENGTH) {
        flag = false;
        break;
      }
      A.push_back(sa);
      B.push_back(sb);
    }
  }
  printf("%d\n", (int)A.size());
  for (int i = 0; i < (int)A.size(); i++) {
    printf("%s %s\n", A[i].c_str(), B[i].c_str());
  }
}
