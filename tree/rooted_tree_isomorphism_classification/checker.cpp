#include <algorithm>
#include <vector>
#include "testlib.h"

using namespace std;

// check and return tecc
vector<vector<int>> read_ans(int n, InStream& stream) {
    int k = stream.readInt(1, n);
    vector<vector<int>> teccs(k);
    for (int i = 0; i < n; i++) {
        int a = stream.readInt(0, k-1);
        teccs[a].push_back(i);
    }
    return teccs;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();

    auto teccs_ans = read_ans(n, ans);
    auto teccs_ouf = read_ans(n, ouf);
    int k_ans = int(teccs_ans.size());
    int k_ouf = int(teccs_ouf.size());
    if (k_ans != k_ouf) {
        quitf(_wa, "# of tecc is differ - expected: '%d', found: '%d'", k_ans, k_ouf);
    }

    sort(teccs_ans.begin(), teccs_ans.end());
    sort(teccs_ouf.begin(), teccs_ouf.end());

    if (teccs_ans != teccs_ouf) {
        quitf(_wa, "tecc is differ");
    }
    quitf(_ok, "OK");
}
