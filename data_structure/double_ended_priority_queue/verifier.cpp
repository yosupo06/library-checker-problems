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

#include <iostream>
#include <cassert>

#include "params.h"

int main() {
    registerValidation();

    int N = inf.readInt(N_MIN, N_MAX);
    inf.readSpace();
    int Q = inf.readInt(Q_MIN, Q_MAX);
    inf.readChar('\n');

    for (int i = 0; i < N; ++i) {
        inf.readInt(V_MIN, V_MAX);
        if (i + 1 != N) inf.readSpace();
    }
    inf.readChar('\n');

    int pq_size = N;
    for (int q = 0; q < Q; ++q) {
        int query_type = inf.readInt(0, 2);
        if (query_type == 0) {
            ++pq_size;
            inf.readSpace();
            inf.readInt(V_MIN, V_MAX);
        } else if (query_type == 1) {
            --pq_size;
            ensure(pq_size >= 0);
        } else {
            ensure(query_type == 2);
            --pq_size;
            ensure(pq_size >= 0);
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}