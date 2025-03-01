// https://github.com/MikeMirzayanov/testlib/blob/master/checkers/ncmp.cpp

// The MIT License (MIT)

// Copyright (c) 2015 Mike Mirzayanov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    setName("compare ordered sequences of signed int%d numbers", 8 * int(sizeof(long long)));

    registerTestlibCmd(argc, argv);

    int n = 0;
    string firstElems;

    while (!ans.seekEof() && !ouf.seekEof()) {
        n++;
        long long j = ans.readLong();
        long long p = ouf.readLong();
        if (j != p)
            quitf(_wa, "%d%s numbers differ - expected: '%s', found: '%s'", n, englishEnding(n).c_str(),
                  vtos(j).c_str(), vtos(p).c_str());
        else if (n <= 5) {
            if (firstElems.length() > 0)
                firstElems += " ";
            firstElems += vtos(j);
        }
    }

    int extraInAnsCount = 0;

    while (!ans.seekEof()) {
        ans.readLong();
        extraInAnsCount++;
    }

    int extraInOufCount = 0;

    while (!ouf.seekEof()) {
        ouf.readLong();
        extraInOufCount++;
    }

    if (extraInAnsCount > 0)
        quitf(_wa, "Answer contains longer sequence [length = %d], but output contains %d elements",
              n + extraInAnsCount, n);

    if (extraInOufCount > 0)
        quitf(_wa, "Output contains longer sequence [length = %d], but answer contains %d elements",
              n + extraInOufCount, n);

    if (n <= 5)
        quitf(_ok, "%d number(s): \"%s\"", n, compress(firstElems).c_str());
    else
        quitf(_ok, "%d numbers", n);
}
