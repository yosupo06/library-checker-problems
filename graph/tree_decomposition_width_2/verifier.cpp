#include "testlib.h"
#include "params.h"
#include <set>
#include <utility>

using namespace std;

int main() {
	registerValidation();

	ensure(inf.readToken() == "p");
	inf.readSpace();
	ensure(inf.readToken() == "tw");
	inf.readSpace();

	int N = inf.readInt(1, N_MAX);
	inf.readSpace();
	int M = inf.readInt(0, M_MAX);
	inf.readChar('\n');

	
	set<pair<int, int>> edges;
	for (int i = 0; i < M; i++) {
		int a = inf.readInt(1, N);
		inf.readSpace();
		int b = inf.readInt(1, N);
		inf.readChar('\n');
		if (a > b) swap(a, b);
		ensure(a != b);
		ensure(!edges.count({a, b}));
		edges.insert({a, b});
	}
	inf.readEof();
	return 0;
}
