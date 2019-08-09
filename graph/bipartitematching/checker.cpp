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
