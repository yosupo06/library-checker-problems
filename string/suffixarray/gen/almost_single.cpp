#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  string S;
  if (seed == 0) {
    // issue 1211 hack_sft
    S = string(499981, 't');
    S[7122] = 's';
    S[249980] = 'g';
    S[374980] = 's';
    S[437480] = 'w';
    S[468730] = 'o';
    S[484355] = 'q';
    S[492167] = 'v';
    S[496073] = 'k';
    S[498026] = 'h';
    S[499003] = 'p';
    S[499491] = 'd';
    S[499735] = 'z';
    S[499857] = 'g';
    S[499918] = 'a';
    S[499949] = 'l';
    S[499964] = 'z';
    S[499972] = 'z';
    S[499980] = 'p';
  } else if (seed == 1) {
    // issue 1211 hack_sft_2
    S = string(499981, 't');
    S[124000] = 's';
    S[499980] = 'p';
  } else {
    char c = 'a' + gen.uniform<int>(0, 25);
    int N = N_MAX;
    S = string(N, c);
    int K = gen.uniform<int>(1, 5);
    for (int k = 0; k < K; ++k) {
      int i = gen.uniform<int>(0, N - 1);
      S[i] = 'a' + gen.uniform<int>(0, 25);
    }
  }
  printf("%s\n", S.c_str());
  return 0;
}
