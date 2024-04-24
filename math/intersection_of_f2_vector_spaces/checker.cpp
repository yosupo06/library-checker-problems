#include <algorithm>
#include <vector>
#include <utility>

#include "testlib.h"
#include "binary_mat.h"

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int T = inf.readInt();

    for (int t = 0; t < T; ++t) {
        BinaryMat uni, x, y;
        size_t n = inf.readInt();
        std::vector<int> u(n);
        for (size_t i = 0; i < n; ++i) {
            u[i] = inf.readInt();
            uni.add(u[i]);
            x.add(u[i]);
        }
        size_t m = inf.readInt();
        std::vector<int> v(m);
        for (size_t i = 0; i < m; ++i) {
            v[i] = inf.readInt();
            uni.add(v[i]);
            y.add(v[i]);
        }

        size_t reslen = ouf.readInt();
        std::vector<int> res(reslen);
        for (size_t i = 0; i < reslen; ++i) {
            res[i] = ouf.readInt();
        }

        size_t correct_dim = n + m - uni.basis().size();

        if (reslen != correct_dim) {
            quitf(_wa, "invalid dimension, expected %d, got %d", static_cast<int>(correct_dim), static_cast<int>(reslen));
        }

        // res is a subset of X \cap Y
        for (int b: res) {
            if (x.is_indep(b) || y.is_indep(b)) {
                quitf(_wa, "element %d is not in the intersection", b);
            }
        }

        // res is linearly independent
        BinaryMat resmat;
        for (int b: res) {
            if (!resmat.is_indep(b)) {
                quitf(_wa, "element %d is not linearly independent", b);
            }
            resmat.add(b);
        }
    }
    quitf(_ok, "OK");
}
