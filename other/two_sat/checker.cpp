#include <algorithm>
#include <vector>
#include <string>
#include "testlib.h"

using namespace std;


int n, m;
vector<pair<int, int>> conditions;

bool read_ans(InStream& stream, TResult wa) {
    // skip s
    stream.readToken("s");
    string ans_str = stream.readToken();
    if (ans_str == "UNSATISFIABLE") {
        return false;
    }
    if (ans_str != "SATISFIABLE") {
        quitf(wa, "Must print SATISFIABLE or UNSATISFIABLE");
    }

    // skip v
    stream.readToken("v");
    vector<int> val(n + 1);
    for (int i = 1; i <= n; i++) {
        val[i] = stream.readInt();

        if (val[i] != i && val[i] != -i) {
            quitf(wa, "Must print i or -i");
        }
    }

    for (auto p: conditions) {
        if (val[abs(p.first)] != p.first && val[abs(p.second)] != p.second) {
            quitf(wa, "Can't Fill Condition %d, %d", p.first, p.second);
        }
    }

    // read 0
    stream.readInt(0, 0);

    return true;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    // read input
    inf.readToken();
    inf.readToken();
    n = inf.readInt();
    m = inf.readInt();
    conditions = vector<pair<int, int>>(m);
    for (int i = 0; i < m; i++) {
        conditions[i].first = inf.readInt();
        conditions[i].second = inf.readInt();
        inf.readInt();
    }


    bool k_ans = read_ans(ans, _fail);
    bool k_ouf = read_ans(ouf, _wa);

    if (k_ans && k_ouf) {
        quitf(_ok, "OK Satisfiable");
    }
    if (!k_ans && !k_ouf) {
        quitf(_ok, "OK Unsatisfiable");
    }
    if (k_ans && !k_ouf) {
        quitf(_wa, "WA you cannot find answer");
    }
    if (!k_ans && k_ouf) {
        quitf(_fail, "What happened?");
    }
}
