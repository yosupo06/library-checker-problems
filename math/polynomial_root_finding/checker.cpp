// https://github.com/MikeMirzayanov/testlib/blob/master/checkers/wcmp.cpp

// The MIT License (MIT)

// Copyright (c) 2015 Mike Mirzayanov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
  setName("polynomial_root_finding");
  registerTestlibCmd(argc, argv);

  int NA = ans.readInt();
  vector<int> A(NA);
  for (int i = 0; i < NA; ++i) A[i] = ans.readInt();

  int NB = ouf.readInt();
  vector<int> B(NB);
  for (int i = 0; i < NB; ++i) B[i] = ouf.readInt();

  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  if (A != B) { quitf(_wa, "the output is different as a multiset"); }
  quitf(_ok, "ok");
}
