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

struct UnionFind {
    UnionFind(int n = 0) : _p(n, -1) {}
    int leader(int u) {
        return _p[u] >= 0 ? _p[u] = leader(_p[u]) : u;
    }
    bool merge(int u, int v) {
        u = leader(u), v = leader(v);
        if (u == v) return false;
        if (_p[u] > _p[v]) std::swap(u, v);
        _p[v] = u;
        return true;
    }
private:
    std::vector<int> _p;
};

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX);
    inf.readSpace();
    int Q = inf.readInt(Q_MIN, Q_MAX);
    inf.readChar('\n');

    for (int i = 0; i < n; ++i) {
        inf.readInt(A_MIN, A_MAX);
        if (i + 1 != n) inf.readSpace();
    }
    inf.readChar('\n');

    UnionFind uf(n);
    for (int i = 0; i < n - 1; i++) {
        int u = inf.readInt(0, n - 1);
        inf.readSpace();
        int v = inf.readInt(0, n - 1);
        inf.readChar('\n');
        ensure(uf.merge(u, v));
    }

    for (int q = 0; q < Q; ++q) {
        int query_type = inf.readInt(0, 1);
        inf.readSpace();
        inf.readInt(0, n - 1);
        inf.readSpace();
        if (query_type == 0) {
            inf.readInt(X_MIN, X_MAX);
        } else {
            int l = inf.readInt(0, n);
            inf.readSpace();
            inf.readInt(l + 1, n);
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}