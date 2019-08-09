// https://github.com/MikeMirzayanov/testlib/blob/master/checkers/wcmp.cpp

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

int main(int argc, char * argv[])
{
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    inf.readInt(); // l
    inf.readInt(); // r
    int m = inf.readInt();
    using P = pair<int, int>;
    set<P> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.insert({a, b});
    }
    int k_ans = ans.readInt();
    int k_ouf = ouf.readInt();

    if (k_ans != k_ouf) {
        quitf(_wa, "# of Matching is differ - expected: '%d', found '%d'", k_ans, k_ouf);
    }

    set<int> lv, rv;
    for (int i = 0; i < k_ouf; i++) {
        int c = ouf.readInt();
        int d = ouf.readInt();
        if (!edges.count({c, d})) {
            quitf(_wa, "Matching is incorrect (%d, %d)", c, d);
        }
        if (lv.count(c)) {
            quitf(_wa, "Matching is incorrect, twice left: %d", c);
        }
        lv.insert(c);
        if (rv.count(d)) {
            quitf(_wa, "Matching is incorrect, twice right: %d", d);
        }
        rv.insert(d);
    }

    if (!ouf.seekEof()) {
        quitf(_wa, "extra tokens");
    }

    quitf(_ok, "OK");
}
